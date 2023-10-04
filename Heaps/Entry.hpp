#include "Common.hpp"
#pragma once

template <typename K, typename V> class Entry {
public:
  K key;
  V value;
  int index{0};

public:
  /*
    Creates an entry w/ a null value.
  */
  explicit Entry();
  /*
    Creates an entry w/ a Key and a Value.
  */
  explicit Entry(K, V);

  //---Operator_Overloading---//

  // Stream insertion overloading.
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
