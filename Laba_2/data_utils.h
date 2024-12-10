#ifndef DATA_UTILS_H
#define DATA_UTILS_H

#include "sequence.h"
#include "array_sequence.h"
#include <fstream>
#include <string>
#include <iostream>

template<typename T>
void save_data_to_file(Sequence<T>* sequence, const std::string& filename) {
    std::ofstream outFile(filename);

    if (!outFile) {
        throw std::runtime_error("Error opening file for saving data: " + filename);
    }

    // Заголовок файла
    outFile << "First Name,Last Name,Middle Name,Address,Occupation,"
            << "Year of Birth,Height,Weight,Income,Gender,Education,"
            << "Married,Has Car,Number of Children,Years of Experience\n";

    // Запись данных
    for (int i = 0; i < sequence->get_length(); ++i) {
        const Person& person = sequence->get(i);

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
                << person.married << ","
                << person.has_car << ","
                << person.number_of_children << ","
                << person.years_of_experience << std::endl;
    }

    outFile.close();
    std::cout << "Data successfully saved to " << filename << "\n";
}

#endif