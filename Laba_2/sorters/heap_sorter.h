#ifndef HEAP_SORTER_H
#define HEAP_SORTER_H

#include "../isorter.h"
#include <iostream>
#include "../pair_sequence.h"

template<typename T>
class HeapSorter : public ISorter<PairSequence<T>> {
public:
    void sort(PairSequence<T>& seq, int (*cmp)(const T&, const T&)) override {
        int n = seq.get_length();

        for (int i = n / 2 - 1; i >= 0; --i) {
            heapify(seq, n, i, cmp);
        }

        for (int i = n - 1; i >= 0; --i) {
            int first = seq.get_first(0);
            T second = seq.get_second(0);

            seq.set(0, seq.get_first(i), seq.get_second(i));
            seq.set(i, first, second);

            heapify(seq, i, 0, cmp);
        }
    }

private:
    void heapify(PairSequence<T>& seq, int n, int i, int (*cmp)(const T&, const T&)) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < n && cmp(seq.get_second(l), seq.get_second(largest)) > 0)
            largest = l;

        if (r < n && cmp(seq.get_second(r), seq.get_second(largest)) > 0)
            largest = r;

        if (largest != i) {
            int first = seq.get_first(i);
            T second = seq.get_second(i);

            seq.set(i, seq.get_first(largest), seq.get_second(largest));
            seq.set(largest, first, second);

            heapify(seq, n, largest, cmp);
        }
    }
};

#endif // HEAP_SORTER_H