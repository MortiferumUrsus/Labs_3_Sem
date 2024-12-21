#ifndef SHELL_SORTER_H
#define SHELL_SORTER_H

#include "../isorter.h"
#include "../pair_sequence.h"
#include <iostream>

// Класс сортировщика методом Шелла
template<typename T>
class ShellSorter : public ISorter<PairSequence<T>> {
public:
    // Функция сортировки
    void sort(PairSequence<T>& seq, int (*cmp)(const T&, const T&)) override {
        int n = seq.get_length();

        // Начальный интервал
        for (int gap = n / 2; gap > 0; gap /= 2) {
            // Делим на подмассивы по текущему интервалу
            for (int i = gap; i < n; ++i) {
                int first = seq.get_first(i);
                T second = seq.get_second(i);

                int j;
                for (j = i; j >= gap && cmp(seq.get_second(j - gap), second) > 0; j -= gap) {
                    seq.set(j, seq.get_first(j - gap), seq.get_second(j - gap));
                }
                seq.set(j, first, second);
            }
        }
    }
};

#endif // SHELL_SORTER_H