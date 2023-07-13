#include "Heaps/Common.hpp"
#include "Heaps/Bin_Heap.hpp"

int main()
{
    BinHeap<int, int> heap(true);
    Entry<int, int> e1(20, 20);
    Entry<int, int> e2(10, 20);
    Entry<int, int> e3(15, 20);
    Entry<int, int> e4(5, 20);
    Entry<int, int> e5(3, 20);
    Entry<int, int> e6(8, 40);
    Entry<int, int> e7(18, 35);

    heap.insert(e1);
    heap.insert(e2);
    heap.insert(e3);
    heap.insert(e4);
    heap.insert(e5);

    heap.replaceKey(e5, 100);
    heap.insert(e6);
    heap.insert(e7);

    heap.toggle();
    heap.remove(e5); // Remove 15
    heap.toggle();
    heap.toggle();

    for (auto i : heap)
    {
        std::cout << i << std::endl;
    }

    return 0;
}
