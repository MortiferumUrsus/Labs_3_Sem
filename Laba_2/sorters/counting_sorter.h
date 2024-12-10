#ifndef COUNTING_SORTER_H
#define COUNTING_SORTER_H

#include "../isorter.h"
#include <iostream>
#include <vector>
#include <algorithm>

// Класс сортировщика сортировкой подсчетом
template<typename T>
class CountingSorter : public ISorter<T> {
public:
    // Предполагается, что T – целочисленный тип
    Sequence<T>* sort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        int n = seq->get_length();
        if (n == 0) return seq->clone();

        // Найти диапазон значений
        T min = seq->get(0);
        T max = seq->get(0);
        for (int i = 1; i < n; ++i) {
            if (seq->get(i) < min) min = seq->get(i);
            if (seq->get(i) > max) max = seq->get(i);
        }

        int range = max - min + 1;
        std::vector<int> count(range, 0);

        // Подсчитать количество каждого элемента
        for (int i = 0; i < n; ++i) {
            count[seq->get(i) - min]++;
        }

        // Изменить счетчик, чтобы он содержал позиции
        for (int i = 1; i < range; ++i) {
            count[i] += count[i - 1];
        }

        // Создать выходную последовательность
        Sequence<T>* sorted_seq = seq->clone();
        Sequence<T>* output = new ArraySequence<T>;

        // Построить отсортированную последовательность
        for (int i = n - 1; i >= 0; --i) {
            T element = seq->get(i);
            output->set(count[element - min] - 1, element);
            count[element - min]--;
        }

        delete sorted_seq;
        return output;
    }
};

#endif // COUNTING_SORTER_H