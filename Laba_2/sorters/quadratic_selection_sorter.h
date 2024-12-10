#ifndef QUADRATIC_SELECTION_SORTER_H
#define QUADRATIC_SELECTION_SORTER_H

#include "../isorter.h"
#include <iostream>

// Класс сортировщика усовершенствованным методом выбором
template<typename T>
class QuadraticSelectionSorter : public ISorter<T> {
public:
    // Функция сортировки
    Sequence<T>* sort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        int n = seq->get_length();
        Sequence<T>* sorted_seq = seq->clone(); // Клонирование последовательности

        for (int i = 0; i < n - 1; ++i) {
            int selected_idx = i;
            for (int j = i + 1; j < n; ++j) {
                if (cmp(sorted_seq->get(j), sorted_seq->get(selected_idx)) < 0) {
                    selected_idx = j;
                }
            }
            // Переместить выбранный элемент на позицию i
            if (selected_idx != i) {
                T selected = sorted_seq->get(selected_idx);
                for (int k = selected_idx; k > i; --k) {
                    sorted_seq->set(k, sorted_seq->get(k - 1));
                }
                sorted_seq->set(i, selected);
            }
        }
        return sorted_seq;
    }
};

#endif // QUADRATIC_SELECTION_SORTER_H