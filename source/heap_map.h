#pragma once

#include "mallocator.h"

using HeapMapAllocator = Mallocator<std::pair<char* const,size_t>>;

class heap_map
{
public:
  void Add(char* buffer, size_t size)
  {
    m_data.emplace(buffer, size);
  }

private:
  std::map<char*,size_t,std::less<char*>,HeapMapAllocator> m_data;
};
