#include "data_generator.h"
#include "array_sequence.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

// Функция для чтения имен из файла
std::vector<std::string> read_values_from_file(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> values;
    std::string value;

    if (!file) {
        std::cerr << "File open error " << filename << std::endl;
        return values;
    }

    while (std::getline(file, value)) {
        if (value.length() > 2) {
            value = value.substr(0, value.length() - 2); // Убираем последние два символа
        }
        if (!value.empty()) {
            values.push_back(value);
        }
}

    return values;
}

// Функция для генерации последовательности Person
std::string generate_data(int size) {
    std::ofstream outFile("generated_data.csv");

    if (!outFile) {
        std::cerr << "File open error" << std::endl;
        return "";
    }

    // Чтение данных из файлов
    auto first_names = read_values_from_file("data_files/first_names.txt");
    auto last_names = read_values_from_file("data_files/last_names.txt");
    auto middle_names = read_values_from_file("data_files/middle_names.txt");
    auto addresses = read_values_from_file("data_files/address.txt");
    auto occupations = read_values_from_file("data_files/occupations.txt");

    std::string genders[] = {"Male", "Female"};
    std::string educations[] = {"High School", "Bachelor", "Master", "PhD"};
    int num_first_names = first_names.size();
    int num_last_names = last_names.size();
    int num_middle_names = middle_names.size();
    int num_addresses = addresses.size();
    int num_occupations = occupations.size();
    int num_genders = sizeof(genders) / sizeof(genders[0]);
    int num_educations = sizeof(educations) / sizeof(educations[0]);

    std::srand(std::time(nullptr));

    // Заголовок CSV-файла
    outFile << "First Name,Last Name,Middle Name,Address,Occupation,"
            << "Year of Birth,Height,Weight,Income,Gender,Education,"
            << "Married,Has Car,Number of Children,Years of Experience\n";

    // Генерация данных
    for (int i = 0; i < size; ++i) {
        Person person;
        person.first_name = first_names[std::rand() % num_first_names];
        person.last_name = last_names[std::rand() % num_last_names];
        person.middle_name = middle_names[std::rand() % num_middle_names];
        person.address = addresses[std::rand() % num_addresses];
        person.occupation = occupations[std::rand() % num_occupations];
        person.year_of_birth = 1950 + std::rand() % 71;
        person.height = 150.0f + static_cast<float>(std::rand() % 51);
        person.weight = 50.0f + static_cast<float>(std::rand() % 51);
        person.income = 20000.0f + static_cast<float>(std::rand() % 80001);
        person.gender = genders[std::rand() % num_genders];
        person.education = educations[std::rand() % num_educations];
        person.married = std::rand() % 2;
        person.has_car = std::rand() % 2;
        person.number_of_children = std::rand() % 5;
        person.years_of_experience = std::rand() % 41;

        // Запись в файл
        outFile << person.first_name << ","
                << person.last_name << ","
                << person.middle_name << ","
                << person.address << ","
                << person.occupation << ","
                << person.year_of_birth << ","
                << person.height << ","
                << person.weight << ","
                << person.income << ","
                << person.gender << ","
                << person.education << ","
                << (person.married ? "Yes" : "No") << ","
                << (person.has_car ? "Yes" : "No") << ","
                << person.number_of_children << ","
                << person.years_of_experience << "\n";
    }

    outFile.close();
    return "generated_data.csv";
}

bool is_digits(const std::string& str) {
    for (char c : str) {
        if (!std::isdigit(c)) return false;
    }
    return true;
}

Sequence<Person>* load_data(const std::string& filename, int size = 0) {
    ////// Проверка на вместимость в память 
    /// Сохранять только номер записи в файле и параметр, который сортируем
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "File open error: " << filename << std::endl;
        return nullptr;
    }

    ArraySequence<Person>* sequence = new ArraySequence<Person>(0);
    
    std::string line;
    std::getline(file, line); // Skip header
    int count = 0;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::istringstream stream(line);
        Person person;
        std::string value;

        try {
            std::getline(stream, person.first_name, ',');
            std::getline(stream, person.last_name, ',');
            std::getline(stream, person.middle_name, ',');
            std::getline(stream, person.address, ',');
            std::getline(stream, person.occupation, ',');

            std::getline(stream, value, ',');
            if (!value.empty() && is_digits(value)) {
                person.year_of_birth = std::stoi(value);
            } else {
                throw std::invalid_argument("Invalid year_of_birth: " + value);
            }

            std::getline(stream, value, ',');
            if (!value.empty()) {
                person.height = std::stof(value);
            } else {
                throw std::invalid_argument("Invalid height: " + value);
            }

            std::getline(stream, value, ',');
            if (!value.empty()) {
                person.weight = std::stof(value);
            } else {
                throw std::invalid_argument("Invalid weight: " + value);
            }

            std::getline(stream, value, ',');
            if (!value.empty()) {
                person.income = std::stof(value);
            } else {
                throw std::invalid_argument("Invalid income: " + value);
            }

            std::getline(stream, person.gender, ',');
            std::getline(stream, person.education, ',');

            std::getline(stream, value, ',');
            person.married = (value == "Yes");
            std::getline(stream, value, ',');
            person.has_car = (value == "Yes");

            std::getline(stream, value, ',');
            if (!value.empty() && is_digits(value)) {
                person.number_of_children = std::stoi(value);
            } else {
                throw std::invalid_argument("Invalid number_of_children: " + value);
            }

            std::getline(stream, value, ',');
            if (!value.empty() && is_digits(value)) {
                person.years_of_experience = std::stoi(value);
            } else {
                throw std::invalid_argument("Invalid years_of_experience: " + value);
            }

            sequence->append(person);

        } catch (const std::exception& e) {
            std::cerr << "Error processing line: " << line << "\n";
            std::cerr << e.what() << "\n";
        }
        count++;
        if (size != 0 && count >= size){
            file.close();
            return sequence;
        };
    }

    file.close();
    return sequence;
}