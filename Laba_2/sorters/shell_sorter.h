#ifndef SHELL_SORTER_H
#define SHELL_SORTER_H

#include "../isorter.h"
#include <iostream>

// Класс сортировщика методом Шелла
template<typename T>
class ShellSorter : public ISorter<T> {
public:
    // Функция сортировки
    Sequence<T>* sort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        int n = seq->get_length();
        Sequence<T>* sorted_seq = seq->clone(); // Клонирование последовательности

        // Начальный интервал
        for (int gap = n / 2; gap > 0; gap /= 2) {
            // Делим на подмассивы по текущему интервалу
            for (int i = gap; i < n; ++i) {
                T temp = sorted_seq->get(i);
                int j;
                for (j = i; j >= gap && cmp(sorted_seq->get(j - gap), temp) > 0; j -= gap) {
                    sorted_seq->set(j, sorted_seq->get(j - gap));
                }
                sorted_seq->set(j, temp);
            }
        }
        return sorted_seq;
    }
};

#endif // SHELL_SORTER_H