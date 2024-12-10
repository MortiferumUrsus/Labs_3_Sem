#ifndef BUBBLE_SORTER_H
#define BUBBLE_SORTER_H

#include "../isorter.h"
#include <iostream>

// Класс сортировщика методом пузырька
template<typename T>
class BubbleSorter : public ISorter<T> {
public:
    // Функция сортировки
    Sequence<T>* sort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        int n = seq->get_length();
        Sequence<T>* sorted_seq = seq->clone(); // Клонирование последовательности

        bool swapped;
        for (int i = 0; i < n - 1; ++i) {
            swapped = false;
            for (int j = 0; j < n - i - 1; ++j) {
                if (cmp(sorted_seq->get(j), sorted_seq->get(j + 1)) > 0) {
                    // Обмен элементов
                    T temp = sorted_seq->get(j);
                    sorted_seq->set(j, sorted_seq->get(j + 1));
                    sorted_seq->set(j + 1, temp);
                    swapped = true;
                }
            }
            // Если не было обменов, массив уже отсортирован
            if (!swapped)
                break;
        }
        return sorted_seq;
    }
};

#endif // BUBBLE_SORTER_H