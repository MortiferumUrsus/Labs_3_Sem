#ifndef BATCHER_SORTER_H
#define BATCHER_SORTER_H

#include "../isorter.h"
#include "../pair_sequence.h"
#include <iostream>

template<typename T>
class BatcherSorter : public ISorter<PairSequence<T>> {
public:
    void sort(PairSequence<T>& seq, int (*cmp)(const T&, const T&)) override {
        int n = seq.get_length();
        int m = 1;
        while (m < n) m <<= 1;

        // Расширение последовательности до степени двойки
        for (int i = n; i < m; ++i) {
            seq.append(seq.get_length(), T());
        }

        bitonic_sort(seq, 0, m, true, cmp);

        // Удаление лишних элементов
        while (seq.get_length() > n) {
            seq.erase(seq.get_length() - 1);
        }
    }

private:
    void bitonic_sort(PairSequence<T>& seq, int low, int cnt, bool dir, int (*cmp)(const T&, const T&)) {
        if (cnt > 1) {
            int k = cnt / 2;
            bitonic_sort(seq, low, k, true, cmp);
            bitonic_sort(seq, low + k, k, false, cmp);
            bitonic_merge(seq, low, cnt, dir, cmp);
        }
    }

    void bitonic_merge(PairSequence<T>& seq, int low, int cnt, bool dir, int (*cmp)(const T&, const T&)) {
        if (cnt > 1) {
            int k = cnt / 2;
            for (int i = low; i < low + k; ++i) {
                compare_and_swap(seq, i, i + k, dir, cmp);
            }
            bitonic_merge(seq, low, k, dir, cmp);
            bitonic_merge(seq, low + k, k, dir, cmp);
        }
    }

    void compare_and_swap(PairSequence<T>& seq, int i, int j, bool dir, int (*cmp)(const T&, const T&)) {
        if (dir == (cmp(seq.get_second(i), seq.get_second(j)) > 0)) {
            // Меняем местами оба элемента пары
            int temp_first = seq.get_first(i);
            T temp_second = seq.get_second(i);

            seq.set(i, seq.get_first(j), seq.get_second(j));
            seq.set(j, temp_first, temp_second);
        }
    }
};

#endif // BATCHER_SORTER_H
