#ifndef DLL_NODE_HPP
#define DLL_NODE_HPP

#include "N-way-set-associative-cache.hpp"
#include <cmath>
#include <list>
#include <set>
#include <unordered_map>

using namespace std;

namespace NwaySetAssociative {
template <typename key_type, typename value_type> class dllNode {
public:
  key_type key;
  value_type val;
  dllNode *previous;
  dllNode *next;
  dllNode(key_type key, value_type val) {
    this->key = key;
    this->val = val;
  }
};
}
#endif