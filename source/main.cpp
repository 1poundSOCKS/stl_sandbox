#include "pch.h"

#pragma comment(lib,"gtest.lib")
#pragma comment(lib,"gtest_main.lib")

#include "heap_map.h"

int main(int argc, char* argv[])
{
  char* buffer = new char[1024];
  heap_map heapMap;
  heapMap.Add(buffer,1024);

  std::list<int, Mallocator<int>> myList;
  myList.emplace_back(1);
  myList.emplace_back(2);
  myList.emplace_back(3);

  return 0;
}
