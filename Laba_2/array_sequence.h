#ifndef ARRAY_SEQUENCE_H
#define ARRAY_SEQUENCE_H

#include "sequence.h"
#include <stdexcept>

// Класс последовательности на основе массива
template<typename T>
class ArraySequence : public Sequence<T> {
private:
    T* data; // Динамический массив данных
    int length; // Длина последовательности

    void is_index(int index) const {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of range in ArraySequence::set");
        }
    }


public:
    // Конструктор с заданным размером
    ArraySequence(int size) : length(size), data(new T[size]) {}

    // Конструктор копирования
    ArraySequence(const ArraySequence<T>& other) : length(other.get_length()), data(new T[other.get_length()]) {
        for (int i = 0; i < length; ++i) {
            data[i] = other.get(i);
        }
    }

    // Деструктор
    ~ArraySequence() {
        delete[] data;
    }

    // Получить элемент по индексу
    T get(int index) const override {
        is_index(index);
        return data[index];
    }

    // Установить элемент по индексу
    void set(int index, T value) override {
        is_index(index);
        data[index] = value;
    }

    // Получить длину последовательности
    int get_length() const override {
        return length;
    }

    // Клонировать последовательность
    Sequence<T>* clone() const override {
        return new ArraySequence<T>(*this);
    }
};

#endif // ARRAY_SEQUENCE_H