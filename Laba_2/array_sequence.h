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

    void is_index(int index) const { // Добавлен const
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of range in ArraySequence::is_index");
        }
    }

public:
    ArraySequence() : length(0), data(nullptr) {}

    // Конструктор с заданным размером
    explicit ArraySequence(int size) : data(new T[size]), length(size) {}

    // Конструктор копирования
    ArraySequence(const ArraySequence<T>& other) 
        : data(new T[other.get_length()]), length(other.get_length()) {
        for (int i = 0; i < length; ++i) {
            data[i] = other.data[i]; // Прямой доступ
        }
    }

    // Деструктор
    ~ArraySequence() override {
        delete[] data;
    }

    void set(int index, T value) override {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of bounds");
        }
        data[index] = value;
    }

    T get(int index) const override {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    int get_length() const override {
        return length;
    }

    // Клонировать последовательность
    Sequence<T>* clone() const override {
        ArraySequence<T>* new_sequence = new ArraySequence<T>(this->get_length());
        for (int i = 0; i < this->get_length(); ++i) {
            new_sequence->set(i, this->get(i));
        }
        return new_sequence;
}


    void append(const T& item) {
        // Создаем новый массив с увеличенным размером
        T* new_data = new T[length + 1];
        for (int i = 0; i < length; ++i) {
            new_data[i] = data[i];
        }

        // Добавляем новый элемент
        new_data[length] = item;

        // Освобождаем старый массив и заменяем его новым
        delete[] data;
        data = new_data;
        ++length;
    }

};

#endif // ARRAY_SEQUENCE_H
