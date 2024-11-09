#ifndef BINARY_INSERTION_SORTER_H
#define BINARY_INSERTION_SORTER_H

#include "isorter.h"

// Класс сортировщика методом двоичных вставок
template<typename T>
class BinaryInsertionSorter : public ISorter<T> {
public:
    // Функция сортировки
    Sequence<T>* sort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        int n = seq->get_length();
        Sequence<T>* sorted_seq = seq->clone();

        for (int i = 1; i < n; ++i) {
            T key = sorted_seq->get(i);
            int left = 0;
            int right = i - 1;

            // Бинарный поиск позиции для вставки
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (cmp(key, sorted_seq->get(mid)) < 0) {
                    right = mid -1;
                }
                else {
                    left = mid + 1;
                }
            }
            // Сдвиг элементов для вставки ключа
            for (int j = i - 1; j >= left; --j) {
                sorted_seq->set(j + 1, sorted_seq->get(j));
            }
            sorted_seq->set(left, key);
        }
        return sorted_seq;
    }
};

#endif // BINARY_INSERTION_SORTER_H