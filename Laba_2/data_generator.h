#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H

#include "data_structure.h"
#include "sequence.h"
#include <vector>
#include <iostream>

// Функция для генерации данных
std::vector<std::string> read_names_from_file(const std::string& filename);
std::string generate_data(int size);
Sequence<Person>* load_data(const std::string& filename, int size);

#endif // DATA_GENERATOR_H