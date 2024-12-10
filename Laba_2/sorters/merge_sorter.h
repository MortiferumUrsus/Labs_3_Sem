#ifndef MERGE_SORTER_H
#define MERGE_SORTER_H

#include "../isorter.h"
#include <iostream>

// Класс сортировщика методом слияния
template<typename T>
class MergeSorter : public ISorter<T> {
public:
    // Функция сортировки
    Sequence<T>* sort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        return merge_sorter(seq, 0, seq->get_length() - 1, cmp);
    }

private:
    Sequence<T>* merge_sorter(Sequence<T>* seq, int left, int right, int (*cmp)(const T&, const T&)) {
        if (left >= right) {
            Sequence<T>* single = new Sequence<T>(1);
            single->set(0, seq->get(left));
            return single;
        }

        int mid = left + (right - left) / 2;
        Sequence<T>* left_sorted = merge_sorter(seq, left, mid, cmp);
        Sequence<T>* right_sorted = merge_sorter(seq, mid + 1, right, cmp);

        return merge(left_sorted, right_sorted, cmp);
    }

    Sequence<T>* merge(Sequence<T>* left, Sequence<T>* right, int (*cmp)(const T&, const T&)) {
        int n1 = left->get_length();
        int n2 = right->get_length();
        Sequence<T>* merged = new Sequence<T>(n1 + n2);

        int i = 0, j = 0, k = 0;
        while (i < n1 && j < n2) {
            if (cmp(left->get(i), right->get(j)) <= 0) {
                merged->set(k++, left->get(i++));
            } else {
                merged->set(k++, right->get(j++));
            }
        }
        while (i < n1) {
            merged->set(k++, left->get(i++));
        }
        while (j < n2) {
            merged->set(k++, right->get(j++));
        }

        delete left;
        delete right;
        return merged;
    }
};

#endif // MERGE_SORTER_H