#ifndef SELECTION_SORTER_H
#define SELECTION_SORTER_H

#include "../isorter.h"
#include <iostream>

// Класс сортировщика методом простого выбора
template<typename T>
class SelectionSorter : public ISorter<T> {
public:
    // Функция сортировки
    Sequence<T>* sort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        int n = seq->get_length();
        Sequence<T>* sorted_seq = seq->clone(); // Клонирование последовательности

        for (int i = 0; i < n - 1; ++i) {
            int min_idx = i;
            for (int j = i + 1; j < n; ++j) {
                if (cmp(sorted_seq->get(j), sorted_seq->get(min_idx)) < 0) {
                    min_idx = j;
                }
            }
            // Обмен элементов
            if (min_idx != i) {
                T temp = sorted_seq->get(i);
                sorted_seq->set(i, sorted_seq->get(min_idx));
                sorted_seq->set(min_idx, temp);
            }
        }
        return sorted_seq;
    }
};

#endif // SELECTION_SORTER_H