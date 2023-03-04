#include "pch.h"

#pragma comment(lib,"gtest.lib")
#pragma comment(lib,"gtest_main.lib")

#include "heap_map.h"

heap_map g_heapMap;

std::mutex g_heapMutex;

void* operator new(size_t size)
{
  std::lock_guard<std::mutex> guard(g_heapMutex);
  printf("new: malloc %i bytes\n", static_cast<int>(size));
  auto buffer = malloc(size);
  g_heapMap.Add(buffer, size);
  printf("new: heap map size=%i\n", static_cast<int>(g_heapMap.m_data.size()));
  return buffer;
}

void* operator new[](size_t size)
{
  std::lock_guard<std::mutex> guard(g_heapMutex);
  printf("new[]: malloc %i bytes\n", static_cast<int>(size));
  auto buffer = malloc(size);
  g_heapMap.Add(buffer, size);
  printf("new: heap map size=%i\n", static_cast<int>(g_heapMap.m_data.size()));
  return buffer;
}

void operator delete(void* buffer)
{
  std::lock_guard<std::mutex> guard(g_heapMutex);
  printf("delete\n");
  free(buffer);
  g_heapMap.Remove(buffer);
  printf("delete: heap map size=%i\n", static_cast<int>(g_heapMap.m_data.size()));
}

void operator delete[](void* buffer)
{
  std::lock_guard<std::mutex> guard(g_heapMutex);
  printf("delete[]\n");
  free(buffer);
  g_heapMap.Remove(buffer);
  printf("delete: heap map size=%i\n", static_cast<int>(g_heapMap.m_data.size()));
}

int main(int argc, char* argv[])
{
  char* buffer = new char[1024];

  g_heapMap.Add(buffer,1024);

  std::list<int> integerList;

  for( int i = 0; i < 100; ++i )
  {
    integerList.push_back(i);
  }

  delete [] buffer;

  return 0;
}
