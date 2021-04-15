#ifndef LRU_ALGO_HPP
#define LRU_ALGO_HPP

#include "N-way-set-associative-cache.hpp"
#include <cmath>
#include <list>
#include <set>
#include <unordered_map>
#include "dll_node.hpp"
#include "cache_algo.hpp"


using namespace std;

namespace NwaySetAssociative {

template <typename key_type, typename value_type> class LRUAlgo : public CacheAlgo<key_type, value_type> {
private:
  unordered_map<key_type, dllNode<key_type, value_type> > setData;
  dllNode<key_type, value_type> *head = nullptr, *tail = nullptr;
  int nItems;

public:
  LRUAlgo(int nItems) { this->nItems = nItems; }

  unordered_map<key_type, dllNode<key_type, value_type> > retrieveSetData() { 
    return setData; 
  }

  value_type get(key_type key) {
    dllNode<key_type, value_type> d = setData.find(key);
    if (d != setData.end()) {
      if (head == nullptr) {
        head = d;
        tail = d;
      }

      else {
        head->previous = d;
        d->next = head;
        head = d;
      }
    }
    return d.val;
  }

  void set(key_type key, value_type value) {
    dllNode<key_type, value_type> newDll(key, value);
    remove(newDll);

    if (setData.count >= nItems && tail != nullptr) {
      remove(tail);
    }

    setData.Add(key, newDll);
    if (head == nullptr) {
      head = newDll;
      tail = newDll;
    }

    else {
      head->previous = newDll;
      newDll->next = head;
      head = newDll;
    }
  } 
};
}
#endif