#pragma once

#include "malloc_allocator.h"

using HeapMapAllocator = malloc_allocator<std::pair<void* const,size_t>>;

class heap_map
{
public:
  void Add(void* buffer, size_t size)
  {
    m_data.emplace(buffer, size);
  }

  size_t Remove(void* buffer)
  {
    m_data.erase(buffer);
    return 0;
  }

  std::map<void*,size_t,std::less<void*>,HeapMapAllocator> m_data;
};
