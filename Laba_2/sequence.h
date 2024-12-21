#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <cstddef>   

// Абстрактный класс последовательности
template<typename T>
class Sequence {
public:
    virtual T get(int index) const = 0; // Получить элемент по индексу
    virtual void set(int index, T value) = 0; // Установить элемент по индексу
    virtual int get_length() const = 0; // Получить длину последовательности
    virtual Sequence<T>* clone() const = 0; // Клонировать последовательность
    virtual ~Sequence() = default; // Виртуальный деструктор
    void erase(size_t pos);
    void push_back(const T& value);
};

#endif // SEQUENCE_H