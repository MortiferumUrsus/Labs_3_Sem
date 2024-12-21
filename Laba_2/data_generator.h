#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H

#include "data_structure.h"
#include "sequence.h"
#include "pair_sequence.h"
#include <vector>
#include <string>
#include <iostream>

// Функция для генерации данных
std::vector<std::string> read_values_from_file(const std::string& filename);
std::string generate_data(int size);
Sequence<Person>* load_data_full(const std::string& filename, int size);
bool is_digits(const std::string& str);
template<typename T>
PairSequence<T> load_data_by_param(const std::string& filename, const std::string& param_name, int num_rows = 0);
template<typename T>
void save_data_to_file(Sequence<T>* sequence, const std::string& filename);
template<typename T>
void save_sorted_data(const PairSequence<T>* sequence, const std::string& input_file, const std::string& output_file);

#endif // DATA_GENERATOR_H