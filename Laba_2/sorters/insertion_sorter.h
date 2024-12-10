#ifndef INSERTION_SORTER_H
#define INSERTION_SORTER_H

#include "../isorter.h"
#include <iostream>


// Класс сортировщика методом простых вставок
template<typename T>
class InsertionSorter : public ISorter<T> {
public:
    // Функция сортировки
    Sequence<T>* sort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        int n = seq->get_length();
        Sequence<T>* sorted_seq = seq->clone(); // Клонирование последовательности
        
        for (int i = 1; i < n; ++i) {
            T key = sorted_seq->get(i);
            int j = i - 1;
            while (j >= 0 && cmp(sorted_seq->get(j), key) > 0) {
                sorted_seq->set(j + 1, sorted_seq->get(j));
                j = j - 1;
            }
            sorted_seq->set(j + 1, key);
        }
        return sorted_seq;
    }
};

#endif // INSERTION_SORTER_H
