#include "Entry.hpp"
#include "Common.hpp"

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