#ifndef BATCHER_SORTER_H
#define BATCHER_SORTER_H

#include "../isorter.h"
#include <iostream>
#include <vector>
#include "../array_sequence.h"

template<typename T>
class BatcherSorter : public ISorter<T> {
public:
    Sequence<T>* sort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        int n = seq->get_length();
        int m = 1;
        while (m < n) m <<= 1;
        Sequence<T>* extended_seq = extend_sequence(seq, m, T());
        bitonic_sort(extended_seq, 0, m, true, cmp);
        return trim_sequence(extended_seq, n);
    }

private:
    Sequence<T>* extend_sequence(Sequence<T>* seq, int size, const T& fill) {
        Sequence<T>* new_seq = new ArraySequence<T>(size);
        int n = seq->get_length();
        for (int i = 0; i < n; ++i) {
            new_seq->set(i, seq->get(i));
        }
        for (int i = n; i < size; ++i) {
            new_seq->set(i, fill);
        }
        return new_seq;  // Не удаляем исходную последовательность
    }

    Sequence<T>* trim_sequence(Sequence<T>* seq, int size) {
        Sequence<T>* new_seq = new ArraySequence<T>(size);
        for (int i = 0; i < size; ++i) {
            new_seq->set(i, seq->get(i));
        }
        delete seq;  // Удаляем расширенную последовательность
        return new_seq;
    }

    void bitonic_sort(Sequence<T>* seq, int low, int cnt, bool dir, int (*cmp)(const T&, const T&)) {
        if (cnt > 1) {
            int k = cnt / 2;
            bitonic_sort(seq, low, k, true, cmp);
            bitonic_sort(seq, low + k, k, false, cmp);
            bitonic_merge(seq, low, cnt, dir, cmp);
        }
    }

    void bitonic_merge(Sequence<T>* seq, int low, int cnt, bool dir, int (*cmp)(const T&, const T&)) {
        if (cnt > 1) {
            int k = cnt / 2;
            for (int i = low; i < low + k; ++i) {
                compare_and_swap(seq, i, i + k, dir, cmp);
            }
            bitonic_merge(seq, low, k, dir, cmp);
            bitonic_merge(seq, low + k, k, dir, cmp);
        }
    }

    void compare_and_swap(Sequence<T>* seq, int i, int j, bool dir, int (*cmp)(const T&, const T&)) {
        if (dir == (cmp(seq->get(i), seq->get(j)) > 0)) {
            T temp = seq->get(i);
            seq->set(i, seq->get(j));
            seq->set(j, temp);
        }
    }
};

#endif // BATCHER_SORTER_H