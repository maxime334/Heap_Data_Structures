#include "Bin_Heap.hpp"
#include "Common.hpp"

namespace bin {

// Constructor.
template <typename K, typename V>
BinHeap<K, V>::BinHeap(bool b) : isMinHeap(b) {}

// Returns number of Entries within the Heap.
template <typename K, typename V> int BinHeap<K, V>::size() const noexcept {
  return storage.size();
}
// Returns left child index.
template <typename K, typename V>
int BinHeap<K, V>::left(const int j) const noexcept {
  return 2 * j + 1;
}
// Returns right child index.
template <typename K, typename V>
int BinHeap<K, V>::right(const int j) const noexcept {
  return 2 * j + 2;
}
// Returns parent index.
template <typename K, typename V>
int BinHeap<K, V>::parent(const int j) const noexcept {
  return (j - 1) / 2;
}
// Does Node has a left child.
template <typename K, typename V>
bool BinHeap<K, V>::hasLeft(const int j) const noexcept {
  return left(j) < size();
}
// Does Node has a right child.
template <typename K, typename V>
bool BinHeap<K, V>::hasRight(const int j) const noexcept {
  return right(j) < this->size();
}
template <typename K, typename V>
bool BinHeap<K, V>::isRoot(const int j) const noexcept {
  return j == 0;
}
// Return a copy of Entry at index i.
template <typename K, typename V> Entry<K, V> BinHeap<K, V>::pos(int i) const {
  return **(storage.begin() + i);
}
// Const function which returns a copy of the root Node.
template <typename K, typename V> Entry<K, V> BinHeap<K, V>::min() const {
  if (size() == 0) {
    throw std::out_of_range(
        "The Heap is empty!\nCannot remove the min/max element.");
  }
  return pos(0);
}
// Swap Entries within the Vector.
// Positions and indices swapped only.
template <typename K, typename V>
void BinHeap<K, V>::swap(Entry<K, V> &a, Entry<K, V> &b) {
  // Indices are swapped.
  int indexA = a.index;
  int indexB = b.index;
  a.index = indexB;
  b.index = indexA;
  // Positions swapped within the Vector.
  storage[indexA] = &b;
  storage[indexB] = &a;
}
// MinHeap: True if a < b.
// MaxHeap: True if a > b.
template <typename K, typename V>
bool BinHeap<K, V>::compare(const Entry<K, V> &a, const Entry<K, V> &b) const {
  if (isMinHeap) {
    return a < b;
  } else {
    return a > b;
  }
}
// Insert by reference within the Heap.
template <typename K, typename V> void BinHeap<K, V>::insert(Entry<K, V> &e) {
  int lastNodeIndex = size();
  Entry<K, V> *ptr = &e;
  e.index = lastNodeIndex;
  // Copy of pointer is made in insertion.
  storage.push_back(ptr);
  upheap(lastNodeIndex);
}
template <typename K, typename V> void BinHeap<K, V>::upheap(int i) {
  while (i > 0) {
    int p = parent(i);
    Entry<K, V> &parent = *(storage[p]);
    Entry<K, V> &entry = *(storage[i]);

    if (compare(entry, parent)) {
      swap(entry, parent);
      i = p;
    } else {
      break;
    }
  }
}
template <typename K, typename V> void BinHeap<K, V>::downheap(int i) {
  while (hasLeft(i)) {
    int leftIndex = left(i);
    Entry<K, V> &entry = *(storage[i]);
    Entry<K, V> &leftE = *(storage[leftIndex]);
    if (hasRight(i)) {
      int rightIndex = right(i);
      Entry<K, V> &rightE = *(storage[rightIndex]);

      // For min heap, entry would be both less than left
      // and right child.
      if (compare(entry, leftE) && compare(entry, rightE)) {
        return;
      }
      // For min heap, entry would be greater than right, and right
      // would be smaller than the left.
      // Take smallest of the trinode, which here is right child.
      else if (compare(rightE, entry) && compare(rightE, leftE)) {
        swap(rightE, entry);
        i = right(i);
        continue;
      }
    }
    // For min heap, smallest node is left child.
    if (compare(leftE, entry)) {
      swap(leftE, entry);
      i = left(i);
      continue;
    } else {
      break;
    }
  }
}
// Check if downheap or upheap is necessary, and make the
// necessary moves.
template <typename K, typename V> void BinHeap<K, V>::bubble(int i) {
  Entry<K, V> &e = *(storage[i]);
  int parentIndex = parent(i);
  Entry<K, V> &p = *(storage[parentIndex]);

  // MinHeap: e < p
  // MaxHeap: e > p
  if (i > 0 && compare(e, p)) {
    upheap(i);
  } else {
    downheap(i);
  }
}
// Removes the root Node from the Heap, and downheaps.
// Throws std::out_of_range if Heap is empty.
template <typename K, typename V> Entry<K, V> &BinHeap<K, V>::removeMin() {
  if (size() == 0) {
    throw std::out_of_range(
        "The Heap is empty!\nCannot remove the min/max element.");
  }
  if (size() == 1) {
    Entry<K, V> &min = *(storage[0]);
    return min;
  } else {
    Entry<K, V> &min = *(storage[0]);
    Entry<K, V> &back = *(storage.back());
    swap(min, back);
    storage.pop_back();
    downheap(0);
    return min;
  }
}
// Must restore heap-order property after we replace the Key.
template <typename K, typename V>
void BinHeap<K, V>::replaceKey(Entry<K, V> &e, K key) {
  e.key = key;
  int index = e.index;
  bubble(index);
}
// Replace value of a Node within the Heap.
template <typename K, typename V>
void BinHeap<K, V>::replaceValue(Entry<K, V> &e, V value) noexcept {
  e.setValue(value);
}
// Does the Heap respect Heap-Order property.
// Depends if it Max or Min Heap.
// Can be rebuilt with createHeap() if isHeap() is false.
template <typename K, typename V> bool BinHeap<K, V>::isHeap() {
  for (auto i : storage) {
    // Vector of pointers so dereferencing needed.
    Entry<K, V> &e = *(i);
    int index = e.index;
    if (index != 0) {
      int parentIndex = parent(index);
      Entry<K, V> &p = *(storage[parentIndex]);
      // For min heap, parent is greater than child.
      if (compare(e, p)) {
        return false;
      }
    }
    if (hasLeft(index)) {
      int leftIndex = left(index);
      Entry<K, V> &l = *(storage[leftIndex]);
      // For min heap, entry is greater than left child.
      if (compare(l, e)) {
        return false;
      }
    }
    if (hasRight(index)) {
      int rightIndex = right(index);
      Entry<K, V> &r = *(storage[rightIndex]);
      // For min heap, entry is greater than right child.
      if (compare(r, e)) {
        return false;
      }
    }
  }
  return true;
}
// Changes from Min Heap to Max Heap, or vice-versa.
template <typename K, typename V> void BinHeap<K, V>::toggle() {
  isMinHeap = !isMinHeap;
  createHeap();
}
// True returned if it is a Minimum Heap.
// Else false returned and it is a Maximum Heap.
template <typename K, typename V> bool BinHeap<K, V>::state() const noexcept {
  return isMinHeap;
}
// Removes a Specified Entry from the Heap.
// Will make the necessary changes so Heap still
// follows Heap-Order property.
template <typename K, typename V> void BinHeap<K, V>::remove(Entry<K, V> &e) {
  int lastNodeIndex = size() - 1;
  int index = e.index;
  Entry<K, V> &lastNode = *(storage[lastNodeIndex]);
  swap(e, lastNode);
  storage.pop_back();
  lastNodeIndex = lastNode.index;
  bubble(lastNodeIndex);
}
// Restructure the Heap. Used if some Nodes have been modified
// outside the Heap.
template <typename K, typename V> void BinHeap<K, V>::createHeap() {
  int n = size();
  for (int i = (n / 2) - 1; i >= 0; i--) {
    downheap(i);
  }
}
template <typename K, typename V> Entry<K, V> BinHeap<K, V>::operator[](int i) {
  return *(storage[i]);
}
// Clears the Heap. Won't destroy the references inside the Heap.
template <typename K, typename V> void BinHeap<K, V>::clearHeap() noexcept {
  storage.clear();
}

//----Iterator----//
template <typename K, typename V>
typename BinHeap<K, V>::Iterator BinHeap<K, V>::begin() noexcept {
  Entry<K, V> **ptr = (&storage.front());
  return Iterator(ptr);
}
template <typename K, typename V>
typename BinHeap<K, V>::Iterator BinHeap<K, V>::end() noexcept {
  Entry<K, V> **ptr = (&storage.back() + 1);
  return Iterator(ptr);
}
template <typename K, typename V>
BinHeap<K, V>::Iterator::Iterator(Entry<K, V> **p) {
  ptr = p;
}
template <typename K, typename V>
Entry<K, V> BinHeap<K, V>::Iterator::operator*() {
  // Double dereference needed as we are pointing to
  // a pointer.
  Entry<K, V> e = **ptr;
  return e;
}
template <typename K, typename V>
typename BinHeap<K, V>::Iterator BinHeap<K, V>::Iterator::operator++() {
  ptr++;
  return *this;
}
template <typename K, typename V>
typename BinHeap<K, V>::Iterator BinHeap<K, V>::Iterator::operator++(int) {
  BinHeap<K, V>::Iterator t = (*this);
  ++(*this);
  return t;
}
} // namespace bin