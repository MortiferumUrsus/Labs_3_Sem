#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include <string>
#include <fstream>
#include <iostream>

// Структура данных для сортировки
struct Person {
    // Строковые поля
    std::string first_name;    // Имя
    std::string last_name;     // Фамилия
    std::string middle_name;   // Отчество
    std::string address;       // Адрес
    std::string occupation;    // Профессия
    std::string gender;        // Пол
    std::string education;     // Образование

    // Числовые поля
    int year_of_birth;         // Год рождения
    int number_of_children;    // Количество детей
    int years_of_experience;   // Стаж работы

    // Вещественные поля
    float height;              // Рост
    float weight;              // Вес
    float income;              // Годовой доход

    // Булевы поля
    bool married;              // Состоит в браке
    bool has_car;              // Есть машина

    // Конструктор по умолчанию
    Person() 
        : first_name(""), last_name(""), middle_name(""), address(""), 
          occupation(""), gender(""), education(""), year_of_birth(0), 
          number_of_children(0), years_of_experience(0), height(0.0f), 
          weight(0.0f), income(0.0f), married(false), has_car(false) {}

    // Пользовательский конструктор
    Person(const std::string& first, const std::string& last, const std::string& middle, 
           const std::string& addr, const std::string& occ, const std::string& g, 
           const std::string& edu, int year, int children, int experience, float h, 
           float w, float inc, bool m, bool car)
        : first_name(first), last_name(last), middle_name(middle), address(addr), 
          occupation(occ), gender(g), education(edu), year_of_birth(year), 
          number_of_children(children), years_of_experience(experience), height(h), 
          weight(w), income(inc), married(m), has_car(car) {}
};


#endif // DATA_STRUCTURE_H