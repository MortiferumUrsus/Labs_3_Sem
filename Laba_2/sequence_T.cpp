#include <iostream>
#include <stdexcept> // Для std::out_of_range

// Шаблонный класс Sequence
template <typename T>
class Sequence {
private:
    T* data;           // Указатель на массив данных
    size_t capacity;   // Вместимость массива
    size_t length;     // Текущее количество элементов

    // Метод для увеличения емкости массива
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
    Sequence() : data(nullptr), capacity(0), length(0) {}

    // Конструктор копирования
    Sequence(const Sequence& other) : data(nullptr), capacity(other.capacity), length(other.length) {
        if (capacity > 0) {
            data = new T[capacity];
            for (size_t i = 0; i < length; ++i) {
                data[i] = other.data[i];
            }
        }
    }

    // Оператор присваивания
    Sequence& operator=(const Sequence& other) {
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
    ~Sequence() {
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
};