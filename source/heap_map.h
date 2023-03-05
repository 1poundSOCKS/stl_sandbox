#pragma once

#include "malloc_allocator.h"

using HeapMapAllocator = malloc_allocator<std::pair<void* const,size_t>>;

class heap_map
{
public:
  enum error_type { heap_error_duplicate_free };

  inline auto Allocate(size_t size) -> void*
  {
    auto buffer = malloc(size);

    if( buffer == nullptr )
    {
      throw std::bad_alloc();
    }
    else
    {
      m_data.emplace(buffer, size);
      return buffer;
    }
  }

  inline auto Free(void* buffer) -> void
  {
    auto heapBuffer = m_data.find(buffer);

    if( heapBuffer == m_data.end() )
    {
      throw heap_error_duplicate_free;
    }
    else
    {
      free(buffer);
      m_data.erase(heapBuffer);
    }
  }

  inline auto AllocationCount() const -> std::size_t
  {
    return m_data.size();
  }

private:
  std::map<void*,size_t,std::less<void*>,HeapMapAllocator> m_data;
};
