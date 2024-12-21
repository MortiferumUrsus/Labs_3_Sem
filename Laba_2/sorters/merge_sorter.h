#ifndef MERGE_SORTER_H
#define MERGE_SORTER_H

#include "../array_sequence.h"
#include "../isorter.h"
#include "../pair_sequence.h"
#include <iostream>

template<typename T>
class MergeSorter : public ISorter<PairSequence<T>> {
public:
    void sort(PairSequence<T>& seq, int (*cmp)(const T&, const T&)) override {
        merge_sort(seq, 0, seq.get_length() - 1, cmp);
    }

private:
    void merge_sort(PairSequence<T>& seq, int left, int right, int (*cmp)(const T&, const T&)) {
        if (left >= right) return;

        int mid = left + (right - left) / 2;
        merge_sort(seq, left, mid, cmp);
        merge_sort(seq, mid + 1, right, cmp);
        merge(seq, left, mid, right, cmp);
    }

    void merge(PairSequence<T>& seq, int left, int mid, int right, int (*cmp)(const T&, const T&)) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        // Создаём временные PairSequence для левой и правой части
        PairSequence<T> left_seq, right_seq;

        // Копируем данные из seq в временные последовательности
        for (int i = 0; i < n1; ++i) {
            left_seq.append(seq.get_first(left + i), seq.get_second(left + i));
        }
        for (int j = 0; j < n2; ++j) {
            right_seq.append(seq.get_first(mid + 1 + j), seq.get_second(mid + 1 + j));
        }

        int i = 0, j = 0, k = left;

        // Слияние двух отсортированных массивов
        while (i < n1 && j < n2) {
            if (cmp(left_seq.get_second(i), right_seq.get_second(j)) <= 0) {
                seq.set(k, left_seq.get_first(i), left_seq.get_second(i));
                ++i;
            } else {
                seq.set(k, right_seq.get_first(j), right_seq.get_second(j));
                ++j;
            }
            ++k;
        }

        // Копируем оставшиеся элементы из left_seq, если есть
        while (i < n1) {
            seq.set(k, left_seq.get_first(i), left_seq.get_second(i));
            ++i;
            ++k;
        }

        // Копируем оставшиеся элементы из right_seq, если есть
        while (j < n2) {
            seq.set(k, right_seq.get_first(j), right_seq.get_second(j));
            ++j;
            ++k;
        }
    }
};

#endif // MERGE_SORTER_H
