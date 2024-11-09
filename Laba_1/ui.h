#ifndef UI_H
#define UI_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "smrt_ptr.h"

struct TestParameters {
    double creation_time;
    double copy_time;
    double assignment_time;
    double dereference_time;

    TestParameters();
};

class SmartPointerManager {
public:
    void create_pointer();
    void copy_pointer();
    void delete_pointer();
    void list_pointers() const;

private:
    std::vector<smrt_ptr<int>> smart_pointers; 
};

void display_help();
void manage_smart_pointers(SmartPointerManager& manager);
void configure_test_parameters(TestParameters& params);
void print_results(const std::vector<std::string>& testNames, const std::vector<std::vector<double>>& results);
void start();

#endif