#ifndef PAIR_SEQUENCE_H
#define PAIR_SEQUENCE_H

#include "array_sequence.h"
#include <string>
#include <stdexcept>

template <typename T>
class PairSequence {
private:
    ArraySequence<int> first_elements;   // Номера строк
    ArraySequence<T> second_elements;   // Параметры произвольного типа

public:
    // Конструктор по умолчанию
    PairSequence() : first_elements(), second_elements() {}

    // Добавление пары
    void append(int first, const T& second) {
        first_elements.append(first);
        second_elements.append(second);
    }

    // Получение размера
    int get_length() const {
        return first_elements.get_length();
    }

    // Получение первого элемента пары
    int get_first(int index) const {
        if (index < 0 || index >= first_elements.get_length()) {
            throw std::out_of_range("Index out of range");
        }
        return first_elements.get(index);
    }

    // Получение второго элемента пары
    T get_second(int index) const {
        if (index < 0 || index >= second_elements.get_length()) {
            throw std::out_of_range("Index out of range");
        }
        return second_elements.get(index);
    }

    // Установка пары по индексу
    void set(int index, int first, const T& second) {
        if (index < 0 || index >= get_length()) {
            throw std::out_of_range("Index out of range");
        }
        first_elements.set(index, first);
        second_elements.set(index, second);
    }

    // Установка первого элемента пары
    void set_first(int index, int first) {
        if (index < 0 || index >= first_elements.get_length()) {
            throw std::out_of_range("Index out of range");
        }
        first_elements.set(index, first);
    }

    // Установка второго элемента пары
    void set_second(int index, const T& second) {
        if (index < 0 || index >= second_elements.get_length()) {
            throw std::out_of_range("Index out of range");
        }
        second_elements.set(index, second);
    }

    // Удаление элемента по индексу
    void erase(int index) {
        if (index < 0 || index >= get_length()) {
            throw std::out_of_range("Index out of range");
        }
        first_elements.erase(index);
        second_elements.erase(index);
    }
};

#endif // PAIR_SEQUENCE_H
