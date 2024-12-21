#ifndef TREE_SELECTION_SORTER_H
#define TREE_SELECTION_SORTER_H

#include "../isorter.h"
#include "../pair_sequence.h"
#include <set>

// Класс сортировщика с использованием бинарного дерева (std::multiset)
template<typename T>
class TreeSelectionSorter : public ISorter<PairSequence<T>> {
public:
    void sort(PairSequence<T>& seq, int (*cmp)(const T&, const T&)) override {
        // Используем std::multiset для хранения индексов и значений
        struct Compare {
            int (*cmp_func)(const T&, const T&);
            bool operator()(const std::pair<int, T>& a, const std::pair<int, T>& b) const {
                int result = cmp_func(a.second, b.second);
                // Если значения равны, сравниваем индексы для стабильности сортировки
                return result < 0 || (result == 0 && a.first < b.first);
            }
        };

        Compare comp = {cmp};
        std::multiset<std::pair<int, T>, Compare> tree(comp);

        // Вставляем пары (номер строки, значение) в дерево
        int n = seq.get_length();
        for (int i = 0; i < n; ++i) {
            tree.emplace(seq.get_first(i), seq.get_second(i));
        }

        // Перезаписываем seq в отсортированном порядке
        int index = 0;
        for (const auto& elem : tree) {
            seq.set(index++, elem.first, elem.second);
        }
    }
};

#endif // TREE_SELECTION_SORTER_H
