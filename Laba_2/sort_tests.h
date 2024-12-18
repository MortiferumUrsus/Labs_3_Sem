#ifndef SORT_TESTS_H
#define SORT_TESTS_H

#include "sequence.h"
#include "isorter.h"
#include "comparator.h"
#include <string>

// Функция для запуска функциональных тестов
void run_functional_tests(const std::string& output_file);

// Функция для запуска нагрузочных тестов
void run_load_tests(const std::string& output_file, int (*comparator)(const Person&, const Person&), int data_size);

#endif // SORT_TESTS_H
