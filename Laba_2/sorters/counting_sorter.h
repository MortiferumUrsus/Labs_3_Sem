#ifndef COUNTING_SORTER_H
#define COUNTING_SORTER_H

#include "../isorter.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "../array_sequence.h"

// Класс сортировщика сортировкой подсчетом
template<typename T>
class CountingSorter : public ISorter<T> {
public:
    Sequence<T>* sort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        int n = seq->get_length();
        if (n == 0) return seq->clone();

        // Определяем минимальные и максимальные значения по компаратору
        T min = seq->get(0);
        T max = seq->get(0);
        for (int i = 1; i < n; ++i) {
            if (cmp(seq->get(i), min) < 0) min = seq->get(i);
            if (cmp(seq->get(i), max) > 0) max = seq->get(i);
        }

        // Создаем счетчик и временный выходной массив
        std::vector<int> count(n, 0);
        std::vector<T> output(n);

        // Подсчитать количество каждого элемента
        for (int i = 0; i < n; ++i) {
            int index = 0;
            for (int j = 0; j < n; ++j) {
                if (cmp(seq->get(i), seq->get(j)) == 0) {
                    index = j;
                    break;
                }
            }
            count[index]++;
        }

        // Изменяем счетчик, чтобы он содержал позиции
        for (int i = 1; i < n; ++i) {
            count[i] += count[i - 1];
        }

        // Построить отсортированную последовательность
        for (int i = n - 1; i >= 0; --i) {
            int index = 0;
            for (int j = 0; j < n; ++j) {
                if (cmp(seq->get(i), seq->get(j)) == 0) {
                    index = j;
                    break;
                }
            }
            output[count[index] - 1] = seq->get(i);
            count[index]--;
        }

        // Создаем выходную последовательность
        Sequence<T>* sorted_seq = new ArraySequence<T>(n);
        for (int i = 0; i < n; ++i) {
            sorted_seq->set(i, output[i]);
        }

        return sorted_seq;
    }
};

#endif // COUNTING_SORTER_H