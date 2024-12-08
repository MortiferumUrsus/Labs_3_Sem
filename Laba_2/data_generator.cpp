#include "data_generator.h"
#include "array_sequence.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

// Функция для чтения имен из файла
std::vector<std::string> read_names_from_file(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> names;
    std::string name;

    if (!file) {
        std::cerr << "Ошибка при открытии файла " << filename << std::endl;
        return names;
    }

    while (std::getline(file, name)) {
        if (!name.empty()) {
            names.push_back(name);
        }
    }

    return names;
}

// Функция для генерации последовательности Person
Sequence<Person>* generate_data(int size, const std::string& first_names_file, const std::string& last_names_file) {
    ArraySequence<Person>* sequence = new ArraySequence<Person>(size);
    std::ofstream outFile("generated_data.txt");

    if (!outFile) {
        std::cerr << "Ошибка при открытии файла для записи." << std::endl;
        return nullptr;
    }

    auto first_names = read_names_from_file(first_names_file);
    auto last_names = read_names_from_file(last_names_file);
    std::string genders[] = {"Combat helicopter", "Cucumber", "Male", "Female"}; 

    int num_first_names = first_names.size();
    int num_last_names = last_names.size();
    int num_genders = sizeof(genders) / sizeof(genders[0]);

    std::srand(std::time(nullptr));

    for (int i = 0; i < size; ++i) {
        Person person;
        person.first_name = first_names[std::rand() % num_first_names];
        person.last_name = last_names[std::rand() % num_last_names];
        person.year_of_birth = 1950 + std::rand() % 71; // Год от 1950 до 2020
        person.height = 150.0f + static_cast<float>(std::rand() % 51); // Рост от 150 до 200 см
        person.weight = 50.0f + static_cast<float>(std::rand() % 51); // Вес от 50 до 100 кг
        person.gender = genders[std::rand() % num_genders];

        sequence->set(i, person);

        // Записываем данные в файл
        outFile << person.first_name << " "
                << person.last_name << " "
                << person.year_of_birth << " "
                << person.height << " "
                << person.weight << " "
                << person.gender << std::endl;
    }

    outFile.close(); // Закрываем файл
    return sequence;
}