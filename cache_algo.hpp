#ifndef CACHE_ALGO_HPP
#define CACHE_ALGO_HPP 

#include "N-way-set-associative-cache.hpp"
#include <cmath>
#include <list>
#include <set>
#include <unordered_map>
#include "dll_node.hpp"

namespace NwaySetAssociative {

template <typename key_type, typename value_type> class CacheAlgo {
public:
  unordered_map<key_type, dllNode<key_type, value_type> > retrieveSetData();
  value_type get(key_type key);
  void set(key_type key, value_type value);
  void remove(NwaySetAssociative::dllNode<key_type,value_type> d);
  void removedllNode(NwaySetAssociative::dllNode<key_type,value_type> d);
  NwaySetAssociative::dllNode<key_type,value_type> getHeadNode();
  bool contains(key_type key);
};
}

#endif