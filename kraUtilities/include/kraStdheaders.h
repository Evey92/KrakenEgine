#pragma once


#ifndef  USING_EASTL
#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <map>

#else
#include <EASTL/array.h>

#endif

  namespace kraEngineSDK {
#ifndef  USING_EASTL
    template<typename T, typename alloc = std::allocator<T>>
    std::vector<T, alloc>;

#else
    template<typename T, typename alloc = std::allocator<T>>
    std::vector<T, alloc>;
#endif
  }