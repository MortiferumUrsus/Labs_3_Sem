#ifndef COUNTING_SORTER_H
#define COUNTING_SORTER_H

#include "../isorter.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "../array_sequence.h"

template<typename T>
class CountingSorter : public ISorter<T> {
public:
    Sequence<T>* sort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        int n = seq->get_length();
        if (n <= 1) return seq->clone();

        // Находим минимальное и максимальное значения
        T min = seq->get(0);
        T max = seq->get(0);
        for (int i = 1; i < n; ++i) {
            if (cmp(seq->get(i), min) < 0) min = seq->get(i);
            if (cmp(seq->get(i), max) > 0) max = seq->get(i);
        }

        // Создаем вектор для подсчета
        int range = cmp(max, min) + 1;
        std::vector<int> count(range, 0);

        // Подсчитываем количество каждого элемента
        for (int i = 0; i < n; ++i) {
            count[cmp(seq->get(i), min)]++;
        }

        // Вычисляем кумулятивную сумму
        for (int i = 1; i < range; ++i) {
            count[i] += count[i - 1];
        }

        // Создаем отсортированную последовательность
        Sequence<T>* sorted_seq = new ArraySequence<T>(n);
        for (int i = n - 1; i >= 0; --i) {
            int index = cmp(seq->get(i), min);
            sorted_seq->set(count[index] - 1, seq->get(i));
            count[index]--;
        }

        return sorted_seq;
    }
};

#endif // COUNTING_SORTER_H