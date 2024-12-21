#ifndef SHAKER_SORTER_H
#define SHAKER_SORTER_H

#include "../isorter.h"
#include "../pair_sequence.h"

// Класс шейкерной сортировки
template<typename T>
class ShakerSorter : public ISorter<PairSequence<T>> {
public:
    // Функция сортировки
    void sort(PairSequence<T>& seq, int (*cmp)(const T&, const T&)) override {
        int left = 0;
        int right = seq.get_length() - 1;
        while (left <= right) {
            for (int i = left; i < right; ++i) {
                if (cmp(seq.get_second(i), seq.get_second(i + 1)) > 0) {
                    int first = seq.get_first(i);
                    T second = seq.get_second(i);

                    seq.set(i, seq.get_second(i+1), seq.get_second(i +1));
                    seq.set(i + 1, first, second);
                }
            }
            right--;
            for (int i = right; i > left; --i) {
                if (cmp(seq.get(i -1), seq.get(i)) > 0) {
                    int first = seq.get_first(i);
                    T second = seq.get_second(i);

                    seq.set(i, seq.get_first(i -1), seq.get_second(i -1));
                    seq.set(i -1, first, second);
                }
            }
            left++;
        }
    }
};

#endif // SHAKER_SORTER_H