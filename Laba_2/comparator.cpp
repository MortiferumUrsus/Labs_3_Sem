#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "data_structure.h"
#include <string>

// Компараторы для разных полей
// Строковые поля
int compare_by_first_name(const Person& a, const Person& b) {
    return a.first_name.compare(b.first_name);
}

int compare_by_last_name(const Person& a, const Person& b) {
    return a.last_name.compare(b.last_name);
}

int compare_by_middle_name(const Person& a, const Person& b) {
    return a.middle_name.compare(b.middle_name);
}

int compare_by_address(const Person& a, const Person& b) {
    return a.address.compare(b.address);
}

int compare_by_occupation(const Person& a, const Person& b) {
    return a.occupation.compare(b.occupation);
}

int compare_by_gender(const Person& a, const Person& b) {
    return a.gender.compare(b.gender);
}

int compare_by_education(const Person& a, const Person& b) {
    return a.education.compare(b.education);
}


// Числовые поля
int compare_by_year_of_birth(const Person& a, const Person& b) {
    return a.year_of_birth - b.year_of_birth;
}

int compare_by_number_of_children(const Person& a, const Person& b) {
    return a.number_of_children - b.number_of_children;
}

int compare_by_years_of_experience(const Person& a, const Person& b) {
    return a.years_of_experience - b.years_of_experience;
}

// Вещественные поля
int compare_by_height(const Person& a, const Person& b) {
    return (a.height < b.height) ? -1 : (a.height > b.height);
}


int compare_by_weight(const Person& a, const Person& b) {
    return (a.weight < b.weight) ? -1 : (a.weight > b.weight);
}

int compare_by_income(const Person& a, const Person& b) {
    return (a.income < b.income) ? -1 : (a.income > b.income);
}

// Булевы поля
int compare_by_married(const Person& a, const Person& b) {
    return (a.married == b.married) ? 0 : (a.married ? -1 : 1);
}

int compare_by_has_car(const Person& a, const Person& b) {
    return (a.has_car == b.has_car) ? 0 : (a.has_car ? -1 : 1);
}



#endif // COMPARATOR_H