#ifndef QUICK_SORTER_H
#define QUICK_SORTER_H

#include "../isorter.h"
#include <iostream>

// Класс сортировщика методом быстрой сортировки (Quick Sort)
template<typename T>
class QuickSorter : public ISorter<T> {
public:
    // Функция сортировки
    Sequence<T>* sort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        Sequence<T>* sorted_seq = seq->clone(); // Клонирование последовательности
        quick_sorter(sorted_seq, 0, sorted_seq->get_length() - 1, cmp);
        return sorted_seq;
    }

private:
    void quick_sorter(Sequence<T>* seq, int low, int high, int (*cmp)(const T&, const T&)) {
        if (low < high) {
            int pi = partition(seq, low, high, cmp);
            quick_sorter(seq, low, pi - 1, cmp);
            quick_sorter(seq, pi + 1, high, cmp);
        }
    }

    int partition(Sequence<T>* seq, int low, int high, int (*cmp)(const T&, const T&)) {
        T pivot = seq->get(high); // Пивот
        int i = low - 1; // Индекс меньшего элемента

        for (int j = low; j <= high - 1; ++j) {
            if (cmp(seq->get(j), pivot) < 0) {
                i++;
                // Обмен
                T temp = seq->get(i);
                seq->set(i, seq->get(j));
                seq->set(j, temp);
            }
        }
        // Обмен с пивотом
        T temp = seq->get(i + 1);
        seq->set(i + 1, seq->get(high));
        seq->set(high, temp);
        return (i + 1);
    }
};

#endif // QUICK_SORTER_H