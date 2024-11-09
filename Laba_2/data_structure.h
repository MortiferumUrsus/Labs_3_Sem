#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include <string>

// Структура данных для сортировки
struct Person {
    std::string first_name; // Имя
    std::string last_name;  // Фамилия
    int year_of_birth;      // Год рождения
    float height;           // Рост
    float weight;           // Вес
    std::string gender;     // Гендер
};

#endif // DATA_STRUCTURE_H