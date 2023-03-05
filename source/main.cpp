#include "pch.h"

#pragma comment(lib,"gtest.lib")
#pragma comment(lib,"gtest_main.lib")

#include "heap_map.h"

heap_map g_memoryController;

std::mutex g_heapMutex;

void* operator new(size_t size)
{
  try
  {
    std::lock_guard<std::mutex> guard(g_heapMutex);
    printf("new: malloc %i bytes\n", static_cast<int>(size));
    auto buffer = g_memoryController.Allocate(size);
    printf("new: heap map size=%i\n", static_cast<int>(g_memoryController.AllocationCount()));
    return buffer;
  }
  catch(const std::exception& e)
  {
    ::printf("error: %s\n", e.what());
    return nullptr;
  }
  catch( heap_map::error_type )
  {
    ::printf("heap map error\n");
    return nullptr;
  }
}

void* operator new[](size_t size)
{
  try
  {
    std::lock_guard<std::mutex> guard(g_heapMutex);
    printf("new[]: malloc %i bytes\n", static_cast<int>(size));
    auto buffer = g_memoryController.Allocate(size);
    printf("new: heap map size=%i\n", static_cast<int>(g_memoryController.AllocationCount()));
    return buffer;
  }
  catch(const std::exception& e)
  {
    ::printf("error: %s\n", e.what());
    return nullptr;
  }
  catch( heap_map::error_type )
  {
    ::printf("heap map error\n");
    return nullptr;
  }
}

void operator delete(void* buffer)
{
  try
  {
    std::lock_guard<std::mutex> guard(g_heapMutex);
    printf("delete\n");
    g_memoryController.Free(buffer);
    printf("delete: heap map size=%i\n", static_cast<int>(g_memoryController.AllocationCount()));
  }
  catch(const std::exception& e)
  {
    ::printf("error: %s\n", e.what());
  }
  catch( heap_map::error_type )
  {
    ::printf("heap map error\n");
  }
}

void operator delete[](void* buffer)
{
  try
  {
    std::lock_guard<std::mutex> guard(g_heapMutex);
    printf("delete[]\n");
    g_memoryController.Free(buffer);
    printf("delete: heap map size=%i\n", static_cast<int>(g_memoryController.AllocationCount()));
  }
  catch(const std::exception& e)
  {
    ::printf("error: %s\n", e.what());
  }
  catch( heap_map::error_type )
  {
    ::printf("heap map error\n");
  }
}

int main(int argc, char* argv[])
{
  try
  {
    auto buffer = g_memoryController.Allocate(1024);

    std::list<int> integerList;

    for( int i = 0; i < 100; ++i )
    {
      integerList.push_back(i);
    }

    g_memoryController.Free(buffer);
  }
  catch( heap_map::error_type )
  {
    std::cerr << "heap map error\n";
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << "\n";
  }

  return 0;
}
