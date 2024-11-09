#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "data_structure.h"
#include <string>

// Компараторы для разных полей
int compare_by_first_name(const Person& a, const Person& b) {
    return a.first_name.compare(b.first_name);
}

int compare_by_last_name(const Person& a, const Person& b) {
    return a.last_name.compare(b.last_name);
}

int compare_by_height(const Person& a, const Person& b) {
    if (a.height < b.height) return -1;
    if (a.height > b.height) return 1;
    return 0;
}

int compare_by_weight(const Person& a, const Person& b) {
    if (a.weight < b.weight) return -1;
    if (a.weight > b.weight) return 1;
    return 0;
}

int compare_by_year_of_birth(const Person& a, const Person& b) {
    return a.year_of_birth - b.year_of_birth;
}

#endif // COMPARATOR_H