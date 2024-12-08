#ifndef ISORTER_H
#define ISORTER_H

#include "sequence.h"

// Интерфейс сортировщика
template<typename T>
class ISorter {
public:
    // Виртуальная функция сортировки
    virtual Sequence<T>* sort(const Sequence<T>& seq, int (*cmp)(const T&, const T&)) = 0; /// Переделать на конст ссылку
    virtual ~ISorter() = default; // Виртуальный деструктор
};

#endif // ISORTER_H