#ifndef QUADRATIC_SELECTION_SORTER_H
#define QUADRATIC_SELECTION_SORTER_H

#include "../isorter.h"
#include "../pair_sequence.h"
#include <iostream>

template<typename T>
class QuadraticSelectionSorter : public ISorter<PairSequence<T>> {
public:
    // Функция сортировки
    void sort(PairSequence<T>& seq, int (*cmp)(const T&, const T&)) override {
        int n = seq.get_length();

        for (int i = 0; i < n - 1; ++i) {
            int selected_idx = i;
            for (int j = i + 1; j < n; ++j) {
                if (cmp(seq.get_second(j), seq.get_second(selected_idx)) < 0) {
                    selected_idx = j;
                }
            }
            if (selected_idx != i) {
                int first = seq.get_first(selected_idx);
                T selected = seq.get_second(selected_idx);

                for (int k = selected_idx; k > i; --k) {
                    seq.set(k, seq.get_first(k - 1), seq.get_second(k - 1));
                }
                seq.set(i, first, selected);
            }
        }
    }
};

#endif // QUADRATIC_SELECTION_SORTER_H