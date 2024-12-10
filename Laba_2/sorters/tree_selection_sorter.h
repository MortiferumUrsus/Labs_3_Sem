#ifndef TREE_SELECTION_SORTER_H
#define TREE_SELECTION_SORTER_H

#include "../isorter.h"
#include <iostream>
#include <set>

// Класс сортировщика с использованием бинарного дерева (например, std::set)
template<typename T>
class TreeSelectionSorter : public ISorter<T> {
public:
    // Функция сортировки
    Sequence<T>* sort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        // Используем мультисет для поддержки дубликатов
        struct Compare {
            int (*cmp_func)(const T&, const T&);
            bool operator()(const T& a, const T& b) const {
                return cmp_func(a, b) < 0;
            }
        };

        Compare comp;
        comp.cmp_func = cmp;
        std::multiset<T, Compare> tree(comp);

        // Вставляем все элементы в дерево
        int n = seq->get_length();
        for (int i = 0; i < n; ++i) {
            tree.insert(seq->get(i));
        }

        // Создаем отсортированную последовательность
        Sequence<T>* sorted_seq = new ArraySequence<T>(n);
        int index = 0;
        for (const auto& elem : tree) {
            sorted_seq->set(index++, elem);
        }

        return sorted_seq;
    }
};

#endif // TREE_SELECTION_SORTER_H