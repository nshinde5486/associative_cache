#ifndef MRU_ALGO_HPP
#define MRU_ALGO_HPP

#include "N-way-set-associative-cache.hpp"
#include <cmath>
#include <list>
#include <set>
#include <unordered_map>
#include "dll_node.hpp"
#include "cache_algo.hpp"


using namespace std;

namespace NwaySetAssociative {

template <typename key_type, typename value_type> class MRUAlgo : public CacheAlgo<key_type, value_type> {
private:
  unordered_map<key_type, dllNode<key_type, value_type> > setData;
  int nItems;
  dllNode<key_type, value_type> *head = nullptr, *tail = nullptr;

public:
  MRUAlgo(int nItems) { this->nItems = nItems; }

  unordered_map<key_type, dllNode<key_type, value_type> > retrieveSetData() { 
    return setData; 
  }

  value_type get(key_type key) {
    dllNode<key_type, value_type> dNode = setData.find(key);
    if (dNode != setData.end()) {
      if (head == nullptr) {
        head = dNode;
        tail = dNode;
      }

      else {
        head->previous = dNode;
        dNode->next = head;
        head = dNode;
      }
    }
    return d.val;
  }

  void set(key_type key, value_type value) {
    dllNode<key_type, value_type> newDll(key, value);
    remove(newDll);

    if (setData.count >= nItems && head != nullptr) {
      remove(head);
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

  void remove(dllNode<key_type, value_type> d) {
    dllNode<key_type, value_type> node = d;
    setData.find(d.key, node);
    setData.remove(d.key);
    removedllNode(node);
  }

  void removedllNode(dllNode<key_type, value_type> dNode) {
    if (dNode == nullptr)
      return;
    if (dNode.previous != nullptr)
      dNode.previous.next = dNode.next;
    if (dNode.next != nullptr)
      dNode.next.previous = dNode.previous;
    if (dNode == tail)
      tail = d.previous;
    if (dNode == head)
      head = dNode.next;
  }

  dllNode<key_type, value_type> getHeadNode() { 
    return head; 
  }

  dllNode<key_type, value_type> getTailNode() { 
    return tail; 
  }

  bool contains(key_type key) { 
    return setData.containsKey(key); 
  }
};
}
#endif