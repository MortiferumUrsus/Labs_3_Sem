#ifndef SELECTION_SORTER_H
#define SELECTION_SORTER_H

#include "../isorter.h"
#include "../pair_sequence.h"
#include <iostream>

// Класс сортировщика методом простого выбора
template<typename T>
class SelectionSorter : public ISorter<PairSequence<T>> {
public:
    // Функция сортировки
    void sort(PairSequence<T>& seq, int (*cmp)(const T&, const T&)) override {
        int n = seq.get_length();

        for (int i = 0; i < n - 1; ++i) {
            int min_idx = i;
            for (int j = i + 1; j < n; ++j) {
                if (cmp(seq.get_second(j), seq.get_second(min_idx)) < 0) {
                    min_idx = j;
                }
            }
            // Обмен элементов
            if (min_idx != i) {
                int first = seq.get_first(i);
                T second = seq.get_second(i);

                seq.set(i, seq.get_first(min_idx), seq.get_second(min_idx));
                seq.set(min_idx, first, second);
            }
        }
    }
};

#endif // SELECTION_SORTER_H