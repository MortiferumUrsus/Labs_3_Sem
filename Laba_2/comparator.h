#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "data_structure.h"

// Строковые поля
extern int compare_by_first_name(const Person& a, const Person& b);
extern int compare_by_last_name(const Person& a, const Person& b);
extern int compare_by_middle_name(const Person& a, const Person& b);
extern int compare_by_address(const Person& a, const Person& b);
extern int compare_by_gender(const Person& a, const Person& b);
extern int compare_by_education(const Person& a, const Person& b);
extern int compare_by_occupation(const Person& a, const Person& b);
// Числовые поля
extern int compare_by_year_of_birth(const Person& a, const Person& b);
extern int compare_by_number_of_children(const Person& a, const Person& b);
extern int compare_by_years_of_experience(const Person& a, const Person& b);
// Вещественные поля
extern int compare_by_height(const Person& a, const Person& b);
extern int compare_by_weight(const Person& a, const Person& b);
extern int compare_by_income(const Person& a, const Person& b);
// Булевы поля
extern int compare_by_married(const Person& a, const Person& b);
extern int compare_by_has_car(const Person& a, const Person& b);

#endif
