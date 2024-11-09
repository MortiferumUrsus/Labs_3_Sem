#ifndef SHAKER_SORTER_H
#define SHAKER_SORTER_H

#include "isorter.h"

// Класс шейкерной сортировки
template<typename T>
class ShakerSorter : public ISorter<T> {
public:
    // Функция сортировки
    Sequence<T>* sort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) override {
        Sequence<T>* sorted_seq = seq->clone();
        int left = 0;
        int right = sorted_seq->get_length() - 1;
        while (left <= right) {
            for (int i = left; i < right; ++i) {
                if (cmp(sorted_seq->get(i), sorted_seq->get(i + 1)) > 0) {
                    T temp = sorted_seq->get(i);
                    sorted_seq->set(i, sorted_seq->get(i +1));
                    sorted_seq->set(i + 1, temp);
                }
            }
            right--;
            for (int i = right; i > left; --i) {
                if (cmp(sorted_seq->get(i -1), sorted_seq->get(i)) > 0) {
                    T temp = sorted_seq->get(i);
                    sorted_seq->set(i, sorted_seq->get(i -1));
                    sorted_seq->set(i -1, temp);
                }
            }
            left++;
        }
        return sorted_seq;
    }
};

#endif // SHAKER_SORTER_H