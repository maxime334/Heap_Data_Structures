#include "Common.hpp"
#include "Entry.hpp"
#include <stdexcept>

namespace bnm {

template <typename K, typename V> struct Node {
  Entry<K, V> &entry;
  int degree{0};
  std::shared_ptr<Node> parent{nullptr};
  std::shared_ptr<Node> sibling{nullptr};
  std::shared_ptr<Node> child{nullptr};

  /*
    Constructor, which takes an entry by reference and stores it.
  */
  Node(Entry<K, V> &);
};

// Alias for shared pointer to Nodes.
template <typename K, typename V> using Node_Ptr = std::shared_ptr<Node<K, V>>;

// Binomial_Heap<Key_Type, Value_Type>.
template <typename K, typename V> class Binomial_Heap {
  Node_Ptr<K, V> head{nullptr};
  short _size{0};

  void linkTrees(Node_Ptr<K, V> &, Node_Ptr<K, V> &);
  bool compare(const Entry<K, V> &, const Entry<K, V> &) const;

public:
  /*
    Is is a minimum heap, so the root always contain the minimum element.
  */
  const bool IS_MIN_HEAP;

  /*
    Creates a binomial heap.
    If true then it is a minimum binomial heap.
  */
  explicit Binomial_Heap(const bool);
  /*
    Returns size of the heap.
  */
  short size() const noexcept;
  /*
    Merges two heaps together.
  */
  void merge(Binomial_Heap<K, V> &);
  /*
    Inserts an entry be reference inside the heap.
  */
  void insert(Entry<K, V> &);
  /*
    Deletes and returns the minimum element out of the heap.
  */
  Entry<K, V> &deleteMin();
  /*
    Returns a copy of the min element inside the heap.
  */
  Entry<K, V> min() const;
  /*
    Clears every element inside the heap.
  */
  void clear_heap() noexcept;
  /*
    Print the heap and its elements.
  */
  void printHeap() noexcept;
};
} // namespace bnm