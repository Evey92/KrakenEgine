#pragma once

#include <cassert>
#include <memory>
#include <cmath>

#include <sstream>
#include <fstream>
#include <iostream>
#include <type_traits>

#ifdef  USING_EASTL
# include <EASTL/algorithm.h>
# include <EASTL/allocator.h>
# include <EASTL/string.h>

//EASTL Containers
# include <EASTL/array.h>
# include <EASTL/vector.h>
# include <EASTL/deque.h>
# include <EASTL/list.h>
# include <EASTL/stack.h>
# include <EASTL/queue.h>
# include <EASTL/priority_queue.h>
# include <EASTL/set.h>
# include <EASTL/map.h>

#else
# include <algorithm>
# include <string>

//STD Containers
# include <array>
# include <vector>
# include <deque>
# include <forward_list>
# include <list>
# include <stack>
# include <queue>
# include <set>
# include <map>
#endif

  namespace kraEngineSDK {

#ifdef  USING_EASTL
    template<typename T, size_t N = 1>
    using Array = eastl::array<T, N>;
    
    template<typename T, 
             typename alloc = EASTLAllocatorType,
             unsigned kDequeSubarraySize = DEQUE_DEFAULT_SUBARRAY_SIZE(T)>
    using Vector = eastl::vector<T, alloc>;

    template<typename T, typename alloc = EASTLAllocatorType>
    using Deque = eastl::deque<T, alloc>;

#else
    template<typename T, size_t N>
    using Array = std::array<T, N>;

    template< class T, class Alloc = std::allocator<T>>
    using Vector = std::vector<T, Alloc>;

    template< class T, class Alloc = std::allocator<T>>
    using Deque = std::deque<T, Alloc>;

    template<class T, class Alloc = std::allocator<T>>
    using Forward_list = std::forward_list<T, Alloc>;

    template<class T, class Alloc = std::allocator<T>>
    using List = std::list<T, Alloc>;

    template<class T, class Container = std::deque<T>>
    using Stack = std::stack<T, Container>;

    template<class T, class Container = std::deque<T>>
    using Queue = std::queue<T, Container>;

    template <class T, class Container = std::vector<T>,
              class Compare = std::less<typename Container::value_type>>
      using Priority_queue = std::priority_queue<T, Container, Compare>;

    template<class T, class compare = std::less<T>,
             class alloc = std::allocator<T>>
      using Set = std::set<T, compare, alloc>;

    template<class T, class compare = std::less<T>,
             class alloc = std::allocator<T>>
    using Multiset = std::multiset<T, compare, alloc>;

    template<class Key, class T, class Compare = std::less<Key>, 
             class Alloc = std::allocator<std::pair<const Key, T>>>
    using Map = std::map<Key, T, Compare, Alloc>;

    template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T>>>
    using Multimap = std::multimap<Key, T, Compare, Alloc>;




#endif

}