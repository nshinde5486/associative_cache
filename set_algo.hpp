#ifndef SET_ALGO_HPP
#define SET_ALGO_HPP

#include "N-way-set-associative-cache.hpp"
#include <cmath>
#include <list>
#include <set>
#include <unordered_map>
#include "dll_node.hpp"
#include "cache_algo.hpp"
#include <string>
#include "lru-algo.hpp"
#include "mru-algo.hpp"


namespace NwaySetAssociative {

template <typename key_type, typename value_type> class Set {
private:
  int nItems;

public:
  CacheAlgo<key_type, value_type> cAlgo;

  Set(int nItems, CacheOptAlgo custalgo) {
    this->nItems = nItems;

    if (custalgo == LRU) {
      cAlgo = LRUAlgo<key_type, value_type>(nItems);
    }

    else if (custalgo == MRU) {
      cAlgo = MRUAlgo<key_type, value_type>(nItems);
    }
  }

  /*Set(int nItems, CacheOptAlgo algorithm) {
    this->nItems = nItems;
    cAlgo = algorithm;
  }*/

  value_type get(key_type key) { return cAlgo.get(key); }

  void add(key_type newKey, value_type newValue) {
    cAlgo.set(newKey, newValue);
  }

  bool contains(key_type key) { return cAlgo.contains(key); }
};
}
#endif