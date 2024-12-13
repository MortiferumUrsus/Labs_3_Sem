#ifndef ARRAY_SEQUENCE_H
#define ARRAY_SEQUENCE_H

#include "sequence.h"
#include <stdexcept>
#include <vector>

template<typename T>
class ArraySequence : public Sequence<T> {
private:
    T* data;
    int length;

    void is_index(int index) const {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of range in ArraySequence::is_index");
        }
    }

public:
    // Конструктор по умолчанию
    ArraySequence() : data(nullptr), length(0) {}

    // Конструктор с заданным размером
    ArraySequence(int size) : data(new T[size]), length(size) {}

    // Конструктор копирования
    ArraySequence(const ArraySequence<T>& other)
        : data(new T[other.length]), length(other.length) {
        for (int i = 0; i < length; ++i) {
            data[i] = other.data[i];
        }
    }

    // Деструктор
    ~ArraySequence() override {
        delete[] data;
    }

    void set(int index, T value) override {
        is_index(index);
        data[index] = value;
    }

    T get(int index) const override {
        is_index(index);
        return data[index];
    }

    int get_length() const override {
        return length;
    }

    Sequence<T>* clone() const override {
        ArraySequence<T>* new_sequence = new ArraySequence<T>(this->length);
        for (int i = 0; i < this->length; ++i) {
            new_sequence->set(i, this->get(i));
        }
        return new_sequence;
    }

    void append(const T& item) {
        T* new_data = new T[length + 1];
        for (int i = 0; i < length; ++i) {
            new_data[i] = data[i];
        }
        new_data[length] = item;
        delete[] data;
        data = new_data;
        ++length;
    }

    void clear() {
        delete[] data;
        data = nullptr;
        length = 0;
    }

    void remove_at(int index) {
        is_index(index);
        T* new_data = new T[length - 1];
        for (int i = 0, j = 0; i < length; ++i) {
            if (i != index) {
                new_data[j++] = data[i];
            }
        }
        delete[] data;
        data = new_data;
        --length;
    }

    std::vector<T> to_vector() const {
        return std::vector<T>(data, data + length);
    }
};

#endif // ARRAY_SEQUENCE_H