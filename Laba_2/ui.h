#ifndef UI_H
#define UI_H

#include <string>
#include "sequence.h"
#include "data_structure.h"

std::string which_algorithm(int algorithm_choice);
void print_data(Sequence<Person>* data);
void start();

#endif // UI_H

