#ifndef BINARY_INSERTION_SORTER_H
#define BINARY_INSERTION_SORTER_H

#include "../isorter.h"
#include "../pair_sequence.h"

// Класс сортировщика методом двоичных вставок
template<typename T>
class BinaryInsertionSorter : public ISorter<T> {
public:
    // Функция сортировки
    void sort(PairSequence<T>& seq, int (*cmp)(const T&, const T&)) override {
        int n = seq.get_length();

        for (int i = 1; i < n; ++i) {
            int key_first = seq.get_first(i);
            T key_second = seq.get_second(i);
            int left = 0;
            int right = i - 1;

            // Бинарный поиск позиции для вставки
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (cmp(key_second, seq.get_second(mid)) < 0) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }

            // Сдвиг элементов для вставки ключа
            for (int j = i - 1; j >= left; --j) {
                seq.set(j + 1, seq.get_first(j), seq.get_second(j));
            }

            seq.set(left, key_first, key_second);
        }
    }
};

#endif // BINARY_INSERTION_SORTER_H
