#ifndef HEAP_SORTER_H
#define HEAP_SORTER_H

#include "../isorter.h"
#include <iostream>

// Класс сортировщика методом пирамидальной сортировки (Heap Sort)
template<typename T>
class HeapSorter : public ISorter<T> {
public:
    // Функция сортировки
    Sequence<T>* sort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        int n = seq->get_length();
        Sequence<T>* sorted_seq = seq->clone(); // Клонирование последовательности

        // Построение кучи (перегруппировка массива)
        for (int i = n / 2 - 1; i >= 0; --i) {
            heapify(sorted_seq, n, i, cmp);
        }

        // Один за другим извлекаем элементы из кучи
        for (int i = n - 1; i >= 0; --i) {
            // Перемещаем текущий корень в конец
            T temp = sorted_seq->get(0);
            sorted_seq->set(0, sorted_seq->get(i));
            sorted_seq->set(i, temp);

            // Вызываем heapify на уменьшенной куче
            heapify(sorted_seq, i, 0, cmp);
        }

        return sorted_seq;
    }

private:
    void heapify(Sequence<T>* seq, int n, int i, int (*cmp)(const T&, const T&)) {
        int largest = i;       // Инициализируем наибольший как корень
        int l = 2 * i + 1;     // левый = 2*i + 1
        int r = 2 * i + 2;     // правый = 2*i + 2

        // Если левый дочерний элемент больше корня
        if (l < n && cmp(seq->get(l), seq->get(largest)) > 0)
            largest = l;

        // Если правый дочерний элемент больше, чем самый большой на данный момент
        if (r < n && cmp(seq->get(r), seq->get(largest)) > 0)
            largest = r;

        // Если самый большой не корень
        if (largest != i) {
            T swap = seq->get(i);
            seq->set(i, seq->get(largest));
            seq->set(largest, swap);

            // Рекурсивно вызываем heapify для поддерева
            heapify(seq, n, largest, cmp);
        }
    }
};

#endif // HEAP_SORTER_H