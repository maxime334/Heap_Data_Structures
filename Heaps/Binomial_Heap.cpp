#include "Binomial_Heap.hpp"
#include "Common.hpp"

namespace bnm {

// Constructor.
// Takes Entry by reference as parameter.
template <typename K, typename V>
Node<K, V>::Node(Entry<K, V> &entry) : entry{entry} {}

// Constructor.
template <typename K, typename V>
Binomial_Heap<K, V>::Binomial_Heap(bool b) : IS_MIN_HEAP(b) {}

// Merges two Binomial Trees of the same degree.
template <typename K, typename V>
void Binomial_Heap<K, V>::linkTrees(Node_Ptr<K, V> &parent,
                                    Node_Ptr<K, V> &child) {
  if (parent->degree != child->degree) {
    throw std::logic_error("The two binomial trees are not the same size!");
  }

  child->parent = parent;
  child->sibling = parent->child;
  parent->child = child;

  parent->degree += 1;
}

// Enables to compare at runtime the Entries.
// Results depend if Heap is a minimum Heap.
// If is_min_heap: returns e1 < e2.
template <typename K, typename V>
bool Binomial_Heap<K, V>::compare(const Entry<K, V> &e1,
                                  const Entry<K, V> &e2) const {
  if (IS_MIN_HEAP) {
    return e1 < e2;
  } else {
    return e1 > e2;
  }
}

// Size data member can only be read, and not changed by the end-user.
template <typename K, typename V>
short Binomial_Heap<K, V>::size() const noexcept {
  return _size;
}

// Union of two Heaps.
// Takes two Binomial_Heaps and merges them in a single Binomial_Heap.
// Destructive method.
template <typename K, typename V>
void Binomial_Heap<K, V>::merge(Binomial_Heap &h) {

  // Special case where one of the two heaps is null (empty).
  if (this->head == nullptr) {
    head = h.head;
    return;
  }
  // No merge necessary.
  if (h.head == nullptr) {
    return;
  }

  // Ptr over root list of B_H_1.
  Node_Ptr<K, V> ptr_1 = this->head;
  // Ptr over root list of B_H_2.
  Node_Ptr<K, V> ptr_2 = h.head;
  // Ptr over root list of new B_H.
  Node_Ptr<K, V> new_ptr = nullptr;
  Node_Ptr<K, V> new_head = nullptr;

  if (ptr_1->degree <= ptr_2->degree) {
    new_ptr = ptr_1;
    ptr_1 = ptr_1->sibling;
  } else {
    new_ptr = ptr_2;
    ptr_2 = ptr_2->sibling;
  }

  new_head = new_ptr;

  // Merging the two root Lists in descending order (degree).
  // new_head points to the new merged list.
  while (ptr_1 != nullptr && ptr_2 != nullptr) {
    // Go until one of the two list is empty.
    if (ptr_1->degree <= ptr_2->degree) {
      // Add to the root list of new_head.
      new_ptr->sibling = ptr_1;
      // Go to the next node in root list.
      ptr_1 = ptr_1->sibling;
    } else {
      new_ptr->sibling = ptr_2;
      ptr_2 = ptr_2->sibling;
    }
    new_ptr = new_ptr->sibling;
  }
  // Root List of Binomial Heap 1 is not empty.
  // Copy all the remaining trees inside the merged root list.
  if (ptr_1 != nullptr) {
    while (ptr_1 != nullptr) {
      new_ptr->sibling = ptr_1;
      ptr_1 = ptr_1->sibling;
      new_ptr = new_ptr->sibling;
    }
  }

  // Copy all the remaining trees inside the merged root list.
  if (ptr_2 != nullptr) {
    while (ptr_2 != nullptr) {
      new_ptr->sibling = ptr_2;
      ptr_2 = ptr_2->sibling;
      new_ptr = new_ptr->sibling;
    }
  }
  // new_ptr ptr value is reset to the beginning (head) of the merged list.
  new_ptr = new_head;
  Node_Ptr<K, V> next = new_ptr->sibling;
  Node_Ptr<K, V> prev = nullptr;

  while (next != nullptr) {
    if (next->sibling != nullptr && next->degree == next->sibling->degree &&
            new_ptr->degree == next->degree ||
        new_ptr->degree != next->degree) {
      // Increment Pointers.
      prev = new_ptr;
      new_ptr = next;
      next = next->sibling;

      // We merge two trees inside the root list.
    } else {
      // Decide which of the two Nodes stays inside the root list.
      if (compare(new_ptr->entry, next->entry)) {
        new_ptr->sibling = next->sibling;
        linkTrees(new_ptr, next);
        next = new_ptr->sibling;
      } else {
        linkTrees(next, new_ptr);
        if (prev != nullptr) {
          prev->sibling = next;
        }
        // new_head ptr must be rectified.
        else {
          new_head = next;
        }
        // Increment Trackers.
        new_ptr = next;
        next = next->sibling;
      }
    }
  }

  // This final merged heap new head.
  this->head = new_head;
}

// Inserts an Entry by reference into the Binomial_Heap.
template <typename K, typename V>
void Binomial_Heap<K, V>::insert(Entry<K, V> &entry) {
  Binomial_Heap<K, V> h(this->IS_MIN_HEAP);
  Node_Ptr<K, V> node = std::make_shared<Node<K, V>>(entry);
  h.head = node;

  merge(h);
  _size++;
}

// Deletes the Node containing the mininum/maximum Entry, and
// returns the Entry by reference.
// Error thrown if removing from empty heap.
template <typename K, typename V>
Entry<K, V> &Binomial_Heap<K, V>::deleteMin() {

  if (_size == 0) {
    throw std::out_of_range(
        "The Heap is empty!.\nCannot remove any Entry from the Heap!.");
  }

  // Finding Minimum Entry within the root list.
  Node_Ptr<K, V> ptr = head;
  Node_Ptr<K, V> prev = nullptr;
  Node_Ptr<K, V> min = head;
  Node_Ptr<K, V> prevMin = nullptr;

  // Find min/max over root list.
  while (ptr != nullptr) {
    if (compare(ptr->entry, min->entry)) {
      min = ptr;
      prevMin = prev;
    }
    prev = ptr;
    ptr = ptr->sibling;
  }

  Entry<K, V> &min_entry = min->entry;

  ptr = min->child;

  // Temp Heap.
  Binomial_Heap<K, V> temp(this->IS_MIN_HEAP);
  Node_Ptr<K, V> ptr_temp;

  // Add every child of min to a temporary Heap.
  // Added in reverse order to keep increasing
  // of degree within the root list.
  std::stack<Node_Ptr<K, V>> stk;

  // Blocking Here.

  while (ptr != nullptr) {
    stk.push(ptr);
    prev = ptr;
    ptr->parent = nullptr;
    ptr = ptr->sibling;      // Increment ptr.
    prev->sibling = nullptr; // Reset current sibling.
  }
  while (!stk.empty()) {
    Node_Ptr<K, V> node = stk.top();
    stk.pop();
    if (temp.head == nullptr) {
      temp.head = node;
      ptr_temp = temp.head;
    } else {
      ptr_temp->sibling = node;
      ptr_temp = ptr_temp->sibling;
    }
  }

  // Remove min node from the heap.

  if (min == head) {
    head = head->sibling;
  } else {
    prevMin->sibling = min->sibling;
    min->sibling = nullptr;
  }
  merge(temp);
  _size--;
  return min_entry;
}

// Returns a copy of the minimum/maximum value inside the Heap.
template <typename K, typename V> Entry<K, V> Binomial_Heap<K, V>::min() const {

  if (_size == 0) {
    throw std::out_of_range(
        "The Heap is empty!.\nCannot remove any Entry from the Heap!.");
  }

  Node_Ptr<K, V> ptr = head;
  Node_Ptr<K, V> min = head;

  while (ptr != nullptr) {
    if (compare(ptr->entry, min->entry)) {
      min = ptr;
    }
    ptr = ptr->sibling;
  }
  return min->entry;
}

template <typename K, typename V>
void Binomial_Heap<K, V>::clear_heap() noexcept {
  head = nullptr;
  _size = 0;
}

// Level-Order traversal done.
// All nodes present in the same level are traversed completely
// before traversing the next level.
template <typename K, typename V>
void Binomial_Heap<K, V>::printHeap() noexcept {
  std::cout << std::endl
            << "---------------" << std::endl; // Just for readability.

  if (_size == 0) {
    std::cout << "The Binomial_Heap is empty." << std::endl;
    std::cout << "---------------" << std::endl;
    return;
  }

  auto ptr = head;
  while (ptr != nullptr) {
    std::cout << "Tree of degree: " << ptr->degree << "." << std::endl;
    std::cout << "There are " << com::pow(2, ptr->degree)
              << " nodes in this tree." << std::endl;
    std::cout << "The level order traversal is" << std::endl;
    std::queue<Node_Ptr<K, V>> q;
    q.push(ptr);
    while (!q.empty()) {
      Node_Ptr<K, V> p = q.front();
      q.pop();
      std::cout << p->entry.key << " ";

      if (p->child != nullptr) {
        Node_Ptr<K, V> tempPtr = p->child;
        while (tempPtr != nullptr) {
          q.push(tempPtr);
          tempPtr = tempPtr->sibling;
        }
      }
    }
    ptr = ptr->sibling;
    std::cout << std::endl << std::endl;
  }

  std::cout << "---------------" << std::endl;
}

// Creates a sample binomial Heap with two nodes, and one tree.
template <typename K, typename V>
Binomial_Heap<K, V> sample_binomial(bool is_min_heap) {
  std::shared_ptr<Entry<K, V>> ptr_e1 = std::make_shared<Entry<K, V>>(10, 20);
  std::shared_ptr<Entry<K, V>> ptr_e2 = std::make_shared<Entry<K, V>>(20, 40);
  Binomial_Heap<K, V> heap(is_min_heap);
  heap.insert(*ptr_e1);
  heap.insert(*ptr_e2);
}

} // namespace bnm