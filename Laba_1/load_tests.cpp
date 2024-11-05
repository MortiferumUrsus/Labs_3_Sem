#include "smrt_ptr.h"
#include <chrono>
#include <vector>
#include <iostream>


// Структура для тестирования
struct TestObject {
    int data[100]; // Размер объекта можно менять для тестирования
};

// Функция для измерения времени создания smrt_ptr
template <typename T>
double test_creation(int iterations) {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    for(int i = 0; i < iterations; ++i){
        smrt_ptr<T> ptr(new T());
    }
    auto end = high_resolution_clock::now();
    duration<double> duration_sec = end - start;
    return duration_sec.count();
}

// Функция для измерения времени копирования smrt_ptr
template <typename T>
double test_copy(int iterations) {
    using namespace std::chrono;
    smrt_ptr<T> original(new T());
    auto start = high_resolution_clock::now();
    for(int i = 0; i < iterations; ++i){
        smrt_ptr<T> copy = original;
    }
    auto end = high_resolution_clock::now();
    duration<double> duration_sec = end - start;
    return duration_sec.count();
}

// Функция для измерения времени присваивания smrt_ptr
template <typename T>
double test_assignment(int iterations) {
    using namespace std::chrono;
    smrt_ptr<T> target;
    smrt_ptr<T> source(new T());
    auto start = high_resolution_clock::now();
    for(int i = 0; i < iterations; ++i){
        target = source;
    }
    auto end = high_resolution_clock::now();
    duration<double> duration_sec = end - start;
    return duration_sec.count();
}

// Функция для измерения времени разыменования smrt_ptr
template <typename T>
double test_dereference(int iterations) {
    using namespace std::chrono;
    smrt_ptr<T> ptr(new T());
    auto start = high_resolution_clock::now();
    for(int i = 0; i < iterations; ++i){
        volatile int value = (*ptr).data[0]; // volatile предотвращает оптимизацию
    }
    auto end = high_resolution_clock::now();
    duration<double> duration_sec = end - start;
    return duration_sec.count();
}

std::vector<double> run_load_tests() {
    const int iterations = 1000000; // Количество итераций для тестов
    std::vector<double> results;

    // Тест создания
    double creation_time = test_creation<TestObject>(iterations);
    results.push_back(creation_time);

    // Тест копирования
    double copy_time = test_copy<TestObject>(iterations);
    results.push_back(copy_time);

    // Тест присваивания
    double assignment_time = test_assignment<TestObject>(iterations);
    results.push_back(assignment_time);

    // Тест разыменования
    double dereference_time = test_dereference<TestObject>(iterations);
    results.push_back(dereference_time);

    return results;
}