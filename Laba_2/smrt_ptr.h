#ifndef SMRT_PTR_H
#define SMRT_PTR_H

#include <cstddef>

// Класс умного указателя
template <typename T>
class smrt_ptr {
private:
    T* ptr; // Указатель на объект
    std::size_t* ref_count; // Счетчик ссылок

    void copy_from(const smrt_ptr<T>& other) {
        ptr = other.ptr;
        ref_count = other.ref_count;
        if (ref_count) {
            ++(*ref_count);
        }
    }

    void release() {
        if (ref_count && --(*ref_count) == 0) { 
            delete ptr;
            delete ref_count;
        }
        ptr = nullptr;
        ref_count = nullptr;
    }

public:
    // Конструктор по умолчанию
    smrt_ptr() : ptr(nullptr), ref_count(nullptr) {}

    // Конструктор от сырого указателя
    explicit smrt_ptr(T* raw_ptr) : ptr(raw_ptr), ref_count(nullptr) {
        if (raw_ptr) {
            ref_count = new std::size_t(1);
        }
    } 

    // Копирующий конструктор
    smrt_ptr(const smrt_ptr<T>& other) {
        copy_from(other);
    }

    // Оператор присваивания
    smrt_ptr<T>& operator=(const smrt_ptr<T>& other) {
        if (this != &other) {
            release();          
            copy_from(other);  
        }
        return *this;
    }

    // Деструктор
    ~smrt_ptr() {
        release();
    }

    // Перегрузка оператора разыменования
    T& operator*() { 
        if (use_count() == 0 || !ptr){
            throw "You can't deference empty pointer";
        }
        return *ptr;
    }

    const T& operator*() const { 
        if (use_count() == 0 || !ptr){
            throw "You can't deference empty pointer";
        }
        return *ptr;
    }

    // Перегрузка оператора ->
    T* operator->() {
        return ptr;
    }

    const T* operator->() const {
        return ptr;
    }

    // Метод для получения текущего счетчика ссылок
    std::size_t use_count() const {
        return ref_count ? *ref_count : 0;
    }

    // Метод для получения сырого указателя
    T* get() const {
        return ptr;
    }
};

#endif // SMRT_PTR_H