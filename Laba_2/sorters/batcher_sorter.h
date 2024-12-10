#ifndef BATCHER_SORTER_H
#define BATCHER_SORTER_H

#include "../isorter.h"
#include <iostream>
#include <vector>
#include "../array_sequence.h"

// Класс сортировщика с использованием схемы Бэтчера (Batcher's Bitonic Sort)
template<typename T>
class BatcherSorter : public ISorter<T> {
public:
    // Функция сортировки
    Sequence<T>* sort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        int n = seq->get_length();
        // На схеме Бэтчера требуется, чтобы размер был степенью двойки
        int m = 1;
        while (m < n) m <<= 1;
        Sequence<T>* extended_seq = extend_sequence(seq, m, T());
        bitonic_sort(extended_seq, 0, m, true, cmp); 
        // Обрезаем до исходного размера 
        Sequence<T>* sorted_seq = new ArraySequence<T>(n);
        for (int i = 0; i < n; ++i) {
            sorted_seq->set(i, extended_seq->get(i));
        }
        delete extended_seq;
        return sorted_seq;
    }

private:
    Sequence<T>* extend_sequence(Sequence<T>* seq, int size, const T& fill) {
        Sequence<T>* new_seq = new ArraySequence<T>(size);
        int n = seq->get_length();
        for (int i = 0; i < size; ++i) {
            if (i < n)
                new_seq->set(i, seq->get(i));
            else
                new_seq->set(i, fill);
        }
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
            int k = greatest_power_of_two_less_than(cnt); 
            for (int i = low; i < low + cnt - k; ++i) {
                compare_and_swap(seq, i, i + k, dir, cmp);
            }
            bitonic_merge(seq, low, k, dir, cmp);
            bitonic_merge(seq, low + k, cnt - k, dir, cmp);
        }
    }

    void compare_and_swap(Sequence<T>* seq, int i, int j, bool dir, int (*cmp)(const T&, const T&)) {
        if (dir == (cmp(seq->get(i), seq->get(j)) > 0)) {
            T temp = seq->get(i);
            seq->set(i, seq->get(j));
            seq->set(j, temp);
        }
    }

    int greatest_power_of_two_less_than(int n) {
        int k = 1;
        while (k > 0 && k < n) k = k << 1;
        return k >> 1;
    }
};

#endif // BATCHER_SORTER_H