#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <cstddef>      // Для size_t
#include <stdexcept>    // Для std::out_of_range
#include <iterator>     // Для std::iterator
#include <algorithm>    // Для std::copy

// Шаблонный класс sequence
template <typename T>
class sequence {
private:
    T* data;           // Указатель на массив данных
    size_t capacity;   // Вместимость массива
    size_t length;     // Текущее количество элементов

    // Метод для увеличения емкости массива до новой вместимости
    void resize(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < length; ++i) {
            new_data[i] = data[i]; // Копирование элементов
        }
        delete[] data; // Освобождение старой памяти
        data = new_data;
        capacity = new_capacity;
    }

public:
    // Конструктор по умолчанию
    sequence() : data(nullptr), capacity(0), length(0) {}

    // Конструктор копирования
    sequence(const sequence& other) : data(nullptr), capacity(other.capacity), length(other.length) {
        if (capacity > 0) {
            data = new T[capacity];
            for (size_t i = 0; i < length; ++i) {
                data[i] = other.data[i];
            }
        }
    }

    // Оператор присваивания
    sequence& operator=(const sequence& other) {
        if (this != &other) { // Проверка на самоприсваивание
            delete[] data; // Освобождение текущих данных

            capacity = other.capacity;
            length = other.length;
            if (capacity > 0) {
                data = new T[capacity];
                for (size_t i = 0; i < length; ++i) {
                    data[i] = other.data[i];
                }
            } else {
                data = nullptr;
            }
        }
        return *this;
    }

    // Деструктор
    ~sequence() {
        delete[] data;
    }

    // Метод добавления элемента в конец последовательности
    void push_back(const T& value) {
        if (length == capacity) {
            // Увеличиваем емкость. Если сначала пусто, устанавливаем начальную емкость, например, 1
            size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
            resize(new_capacity);
        }
        data[length++] = value;
    }

    // Метод удаления последнего элемента
    void pop_back() {
        if (length == 0) {
            throw std::out_of_range("Delete from empty");
        }
        --length;
    }

    // Метод получения размера последовательности
    size_t size() const {
        return length;
    }

    // Новый метод: возвращает длину последовательности
    size_t get_length() const {
        return length;
    }

    // Новый метод: создаёт и возвращает копию (клон) текущей последовательности
    sequence<T> clone() const {
        return sequence<T>(*this);
    }

    // Новый метод: возвращает элемент по индексу
    T get(int index) const {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Новый метод: устанавливает элемент по индексу
    void set(int index, const T& value) {
        if (index < 0 || index >= length) {
            throw std::out_of_range("Index out of range");
        }
        data[index] = value;
    }

    // Перегрузка оператора доступа по индексу с проверкой границ
    T& operator[](size_t index) {
        if (index >= length) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Константная версия перегрузки оператора доступа по индексу
    const T& operator[](size_t index) const {
        if (index >= length) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Метод очистки последовательности
    void clear() {
        delete[] data;
        data = nullptr;
        capacity = 0;
        length = 0;
    }

    // Вставка элемента на позицию pos
    void insert(size_t pos, const T& value) {
        if (pos > length) {
            throw std::out_of_range("Index out of range");
        }
        if (length == capacity) {
            size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
            resize(new_capacity);
        }
        // Сдвиг элементов вправо
        for (size_t i = length; i > pos; --i) {
            data[i] = data[i - 1];
        }
        data[pos] = value;
        ++length;
    }

    // Удаление элемента на позиции pos
    void erase(size_t pos) {
        if (pos >= length) {
            throw std::out_of_range("Index out of range");
        }
        // Сдвиг элементов влево
        for (size_t i = pos; i < length - 1; ++i) {
            data[i] = data[i + 1];
        }
        --length;
    }

    // Проверка, пуста ли последовательность
    bool empty() const {
        return length == 0;
    }

    // Получение первого элемента
    T& front() {
        if (empty()) {
            throw std::out_of_range("Empty");
        }
        return data[0];
    }

    const T& front() const {
        if (empty()) {
            throw std::out_of_range("Empty");
        }
        return data[0];
    }

    // Получение последнего элемента
    T& back() {
        if (empty()) {
            throw std::out_of_range("Empty");
        }
        return data[length - 1];
    }

    const T& back() const {
        if (empty()) {
            throw std::out_of_range("Последовательность пуста.");
        }
        return data[length - 1];
    }

    // Определение итератора
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        iterator(pointer ptr) : ptr_(ptr) {}

        reference operator*() const { return *ptr_; }
        pointer operator->() { return ptr_; }

        // Префиксный инкремент
        iterator& operator++() { ptr_++; return *this; }

        // Постфиксный инкремент
        iterator operator++(int) { 
            iterator tmp = *this; 
            ++(*this); 
            return tmp; 
        }

        bool operator==(const iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const iterator& other) const { return ptr_ != other.ptr_; }

    private:
        pointer ptr_;
    };

    // Определение константного итератора
    class const_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = const T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        const_iterator(pointer ptr) : ptr_(ptr) {}

        reference operator*() const { return *ptr_; }
        pointer operator->() const { return ptr_; }

        // Префиксный инкремент
        const_iterator& operator++() { ptr_++; return *this; }

        // Постфиксный инкремент
        const_iterator operator++(int) { 
            const_iterator tmp = *this; 
            ++(*this); 
            return tmp; 
        }

        bool operator==(const const_iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const const_iterator& other) const { return ptr_ != other.ptr_; }

    private:
        pointer ptr_;
    };

    // Метод для получения итератора на начало последовательности
    iterator begin() {
        return iterator(data);
    }

    // Метод для получения итератора на конец последовательности
    iterator end() {
        return iterator(data + length);
    }

    // Метод для получения константного итератора на начало
    const_iterator begin() const {
        return const_iterator(data);
    }

    // Метод для получения константного итератора на конец
    const_iterator end() const {
        return const_iterator(data + length);
    }

    // Метод для получения константного итератора на начало (для C++11)
    const_iterator cbegin() const {
        return const_iterator(data);
    }

    // Метод для получения константного итератора на конец (для C++11)
    const_iterator cend() const {
        return const_iterator(data + length);
    }
};

#endif // sequence_H