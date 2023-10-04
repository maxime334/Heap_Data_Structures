#include "Common.hpp"
#include "Entry.hpp"
#include <stdexcept>
#pragma once

namespace bin {

template <typename K, typename V> class BinHeap {

private:
  /*
    Vector made of pointers to Entries.
  */
  std::vector<Entry<K, V> *> storage;
  bool isMinHeap;

public:
  explicit BinHeap(bool);
  int size() const noexcept;
  Entry<K, V> min() const;
  void insert(Entry<K, V> &);
  Entry<K, V> &removeMin();
  Entry<K, V> operator[](int);
  void replaceKey(Entry<K, V> &, K);
  void replaceValue(Entry<K, V> &, V) noexcept;
  bool state() const noexcept;
  void toggle();
  bool isHeap();
  void remove(Entry<K, V> &);
  void createHeap();
  void clearHeap() noexcept;

  struct Iterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;

    explicit Iterator(Entry<K, V> **);
    Entry<K, V> operator*();
    Iterator operator++();
    Iterator operator++(int);
    friend bool operator==(const Iterator &a, const Iterator &b) {
      return a.ptr = b.ptr;
    }
    friend bool operator!=(const Iterator &a, const Iterator &b) {
      return a.ptr != b.ptr;
    }

  private:
    Entry<K, V> **ptr;
  };

  Iterator begin() noexcept;
  Iterator end() noexcept;

private:
  int left(const int) const noexcept;
  int right(const int) const noexcept;
  int parent(const int) const noexcept;
  bool hasLeft(const int) const noexcept;
  bool hasRight(const int) const noexcept;
  bool isRoot(const int) const noexcept;
  Entry<K, V> pos(int) const;
  void swap(Entry<K, V> &, Entry<K, V> &);
  bool compare(const Entry<K, V> &, const Entry<K, V> &) const;
  void upheap(int);
  void downheap(int);
  void bubble(int);
};

} // namespace bin
