#ifndef QUICK_SORTER_H
#define QUICK_SORTER_H

#include "../isorter.h"
#include "../pair_sequence.h"
#include <iostream>

// Класс сортировщика методом быстрой сортировки (Quick Sort)
template<typename T>
class QuickSorter : public ISorter<PairSequence<T>> {
public:
    // Функция сортировки
    void sort(PairSequence<T>& seq, int (*cmp)(const T&, const T&)) override {
        quick_sorter(seq, 0, seq.get_length() - 1, cmp);
    }

private:
    void quick_sorter(PairSequence<T>& seq, int low, int high, int (*cmp)(const T&, const T&)) {
        if (low < high) {
            int pivot_index = partition(seq, low, high, cmp);
            quick_sorter(seq, low, pivot_index - 1, cmp);
            quick_sorter(seq, pivot_index + 1, high, cmp);
        }
    }

    int partition(PairSequence<T>& seq, int low, int high, int (*cmp)(const T&, const T&)) {
        // Используем средний элемент как пивот для улучшения стабильности
        int pivot_index = low + (high - low) / 2;

        // Перемещаем пивот в конец
        swap(seq, pivot_index, high);

        // Берём пивот
        T pivot_value = seq.get_second(high);
        int i = low - 1; // Индекс меньшего элемента

        for (int j = low; j < high; ++j) {
            if (cmp(seq.get_second(j), pivot_value) <= 0) {
                ++i;
                swap(seq, i, j); // Обмен местами текущего элемента с элементом seq[i]
            }
        }

        // Помещаем пивот на правильное место
        swap(seq, i + 1, high);

        return i + 1; // Возвращаем индекс пивота
    }

    // Вспомогательная функция для обмена пар местами
    void swap(PairSequence<T>& seq, int index1, int index2) {
        int temp_first = seq.get_first(index1);
        T temp_second = seq.get_second(index1);

        seq.set(index1, seq.get_first(index2), seq.get_second(index2));
        seq.set(index2, temp_first, temp_second);
    }
};

#endif // QUICK_SORTER_H
