#ifndef BUBBLE_SORTER_H
#define BUBBLE_SORTER_H

#include "../isorter.h"
#include <iostream>
#include "../pair_sequence.h"

// Класс сортировщика методом пузырька
template<typename T>
class BubbleSorter : public ISorter<T> {
public:
    // Функция сортировки
    void sort (PairSequence<T>& seq, int (*cmp)(const T&, const T&)) override {
        int n = seq.get_length();

        bool swapped;
        for (int i = 0; i < n - 1; ++i) {
            swapped = false;
            for (int j = 0; j < n - i - 1; ++j) {
                if (cmp(seq.get_second(j), seq.get_second(j + 1)) > 0) {
                    // Обмен элементов
                    int first = seq.get_first(i);
                    T second = seq.get_second(i);

                    seq.set(j, seq.get_first(j + 1), seq.get_second(j + 1));
                    seq.set(j + 1, first, second);
                    swapped = true;
                }
            }
            // Если не было обменов, массив уже отсортирован
            if (!swapped)
                break;
        }
    }
};

#endif // BUBBLE_SORTER_H