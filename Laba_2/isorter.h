#ifndef ISORTER_H
#define ISORTER_H

#include "pair_sequence.h"

// Интерфейс сортировщика
template<typename T>
class ISorter {
public:
    // Виртуальная функция сортировки
    virtual void sort(PairSequence<T>& seq, int (*cmp)(const T&, const T&)) = 0; // Поменял, чтобы менялась сама последовательность
    virtual ~ISorter() = default; // Виртуальный деструктор
};

#endif // ISORTER_H