#include "Common.hpp"
#pragma once

template <typename K, typename V> class Entry {
public:
  K key;
  V value;
  int index{0};

public:
  explicit Entry();
  explicit Entry(K, V);

  //---Operator_Overloading---//

  friend std::ostream &operator<<(std::ostream &os, const Entry<K, V> &e) {
    os << "Entry has key: " << e.key << " and has value: " << e.value;
    return os;
  }
  friend bool operator==(const Entry<K, V> &a, const Entry<K, V> &b) {
    if (a.key == b.key) {
      return true;
    }
    return false;
  }
  friend bool operator<(const Entry<K, V> &a, const Entry<K, V> &b) {
    if (a.key < b.key) {
      return true;
    }
    return false;
  }
  friend bool operator>(const Entry<K, V> &a, const Entry<K, V> &b) {
    if (a < b || a == b) {
      return false;
    }
    return true;
  }
  friend bool operator<=(const Entry<K, V> &a, const Entry<K, V> &b) {
    if (a < b || a == b) {
      return true;
    }
    return false;
  }
  friend bool operator>=(const Entry<K, V> &a, const Entry<K, V> &b) {
    if (a > b || a == b) {
      return true;
    }
    return false;
  }
};
//--Constructors--//

// Default.
template <typename K, typename V> Entry<K, V>::Entry() {
  K k;
  V v;
  this->key = k;
  this->value = v;
}
// Parameterized.
template <typename K, typename V>
Entry<K, V>::Entry(K key, V value) : key(key), value(value) {}
