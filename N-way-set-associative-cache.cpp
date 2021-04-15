#include "N-way-set-associative-cache.hpp"
#include "dll_node.hpp"
#include <cmath>
#include <functional>
#include <list>
#include <set>
#include <vector>
#include <unordered_map>
#include "lru-algo.hpp"
#include "mru-algo.hpp"
#include "set_algo.hpp"


namespace NwaySetAssociative {

template <typename key_type, typename value_type> class associativeCache {

public:
  int cacheSize, nSets, nItems;
  vector<Set<key_type, value_type> > cache;

  associativeCache(int cacheSize, int nItems, CacheOptAlgo algo) {
    auto dummy = this;
    dummy->cacheSize = cacheSize;
    dummy->nItems = nItems;
    dummy->nSets = dummy->cacheSize / dummy->nItems;

    for (int iter = 0; iter < dummy->nSets; iter++) {
      cache.push_back(Set<key_type, value_type>(nItems, algo));
    }
  }

  int generateHashCode(key_type key)
  {
      return key % nSets;
  }

  list<set<key_type, value_type> > getCache() { 
    return cache; 
  }

  int retrieveSetLocation(key_type key) { 
    return abs(generateHashCode(key)); 
  }

  value_type get(key_type key) { 
    return cache[retrieveSetLocation(key)].get(key); 
  }

  void put(key_type key, value_type value) {
    cache[retrieveSetLocation(key)].add(key, value);
  }

  bool contains(key_type key) { 
    return cache[retrieveSetLocation(key)].contains(key); 
  }
};

// testing
int main() {
  /*MRU cache optimization*/
  associativeCache<char, int> *cacheMru = new associativeCache<char, int> (16, 8, MRU);
  cacheMru->put('Z', 100);
  cacheMru->put('Y', 101);
  cacheMru->put('X', 102);
  cacheMru->put('W', 103);
  int value = cacheMru->get('R');
  printf("Recieved the value %d for key R\n", value);
  value = cacheMru->get('V');
  printf("Recieved the value %d for key V\n", value);
  
  /*LRU cache optimization */
  associativeCache<char, int> *cacheLru = new associativeCache<char, int> (24, 4, LRU);
  cacheLru->put('A', 200);
  cacheLru->put('B', 201);
  cacheLru->put('C', 202);
  cacheLru->put('D', 203);
  int val = cacheMru->get('R');
  printf("Recieved the value %d for key R\n", val);
  val = cacheMru->get('V');
  printf("Recieved the value %d for key V\n", val);
  return 0;
}
}