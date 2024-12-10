#ifndef SORT_TESTS_H
#define SORT_TESTS_H

#include "sequence.h"
#include "isorter.h"
#include "comparator.h"
#include <string>

// Функция для запуска функциональных тестов
void run_functional_tests(const std::string& output_file);

// Функция для запуска нагрузочных тестов
void run_performance_tests(const std::string& output_file);

#endif // SORT_TESTS_H
