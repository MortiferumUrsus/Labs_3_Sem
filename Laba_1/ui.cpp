#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "load_tests.h"
#include "functional_tests.h"
#include "stl_tests.h"
#include "smrt_ptr.h" 


struct TestParameters {
    double creation_time;
    double copy_time;
    double assignment_time;
    double dereference_time;

    TestParameters()
        : creation_time(1.0), copy_time(1.0), assignment_time(1.0), dereference_time(1.0) {}
};

class SmartPointerManager {
public:
    void create_pointer() {
        int value;
        std::cout << "New smart ptr value: ";
        std::cin >> value;
        smrt_ptr<int> ptr(new int(value));
        smart_pointers.push_back(ptr);
        std::cout << "Smart pointer created. Current reference count: " << ptr.use_count() << "\n";
    }

    void copy_pointer() {
        if (smart_pointers.empty()) {
            std::cout << "No smart pointers to copy.\n";
            return;
        }
        list_pointers();
        size_t index;
        std::cout << "Enter index of the smart pointer to copy: ";
        std::cin >> index;
        if (index >= smart_pointers.size()) {
            std::cout << "Invalid index.\n";
            return;
        }
        smrt_ptr<int> copied_ptr = smart_pointers[index];
        smart_pointers.push_back(copied_ptr);
        std::cout << "Smart pointer copied. Current reference count: " << copied_ptr.use_count() << "\n";
    }

    void delete_pointer() {
        if (smart_pointers.empty()) {
            std::cout << "No smart pointers to delete.\n";
            return;
        }
        list_pointers();
        size_t index;
        std::cout << "Enter index of the smart pointer to delete: ";
        std::cin >> index;
        if (index >= smart_pointers.size()) {
            std::cout << "Invalid index.\n";
            return;
        }
        smart_pointers.erase(smart_pointers.begin() + index);
        std::cout << "Smart pointer deleted.\n";
    }

    void list_pointers() const {
        if (smart_pointers.empty()) {
            std::cout << "No smart pointers to display.\n";
            return;
        }
        std::cout << "List of smart pointers:\n";
        for (size_t i = 0; i < smart_pointers.size(); ++i) {
            if (smart_pointers[i].use_count() > 0 && smart_pointers[i].get()) {
                std::cout << i << ": " << *smart_pointers[i] << " (ref_count: " << smart_pointers[i].use_count() << ")\n";
            } else {
                std::cout << i << ": nullptr (ref_count: " << smart_pointers[i].use_count() << ")\n";
            }
        }
    }

private:
    std::vector<smrt_ptr<int>> smart_pointers; 
};

void display_help() {
    std::cout << "Available commands:\n";
    std::cout << "/help - Show this message\n";
    std::cout << "1 - Run functional test\n";
    std::cout << "2 - Run load test\n";
    std::cout << "3 - Run STL test\n";
    std::cout << "4 - Manage smart pointers\n";
    std::cout << "s - Configure test parameters\n";
    std::cout << "r - Show test results\n";
    std::cout << "q - Exit the program\n";
}

void manage_smart_pointers(SmartPointerManager& manager) {
    std::string command;
    bool managing = true;

    while (managing) {
        std::cout << "\n--- Smart Pointer Management ---\n";
        std::cout << "1 - Create smart pointer\n";
        std::cout << "2 - Copy smart pointer\n";
        std::cout << "3 - Delete smart pointer\n";
        std::cout << "4 - Show all smart pointers\n";
        std::cout << "b - Go back\n";
        std::cout << "Enter command: ";
        std::cin >> command;

        if (command == "1") {
            manager.create_pointer();
        }
        else if (command == "2") {
            manager.copy_pointer();
        }
        else if (command == "3") {
            manager.delete_pointer();
        }
        else if (command == "4") {
            manager.list_pointers();
        }
        else if (command == "b") {
            managing = false;
        }
        else {
            std::cout << "Unknown command. Try again.\n";
        }
    }
}

void configure_test_parameters(TestParameters& params) {
    std::cout << "Configuring test parameters:\n";
    std::cout << "Enter creation time: ";
    std::cin >> params.creation_time;
    std::cout << "Enter copy time: ";
    std::cin >> params.copy_time;
    std::cout << "Enter assignment time: ";
    std::cin >> params.assignment_time;
    std::cout << "Enter dereference time: ";
    std::cin >> params.dereference_time;
    std::cout << "Parameters updated.\n";
}

void print_results(const std::vector<std::string>& testNames, const std::vector<std::vector<double>>& results) {
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "\n--- Test Results ---\n";
    std::cout << std::setw(25) << "Test Name"
              << std::setw(15) << "Creation"
              << std::setw(15) << "Copying"
              << std::setw(15) << "Assignment"
              << std::setw(15) << "Dereferencing\n";
    std::cout << "-----------------------------------------------------------------------------\n";

    for (size_t i = 0; i < testNames.size(); ++i) {
        std::cout << std::setw(25) << testNames[i]
                  << std::setw(15) << results[i][0]
                  << std::setw(15) << results[i][1]
                  << std::setw(15) << results[i][2]
                  << std::setw(15) << results[i][3] << "\n";
    }
}

void start() {
    std::string command;
    bool running = true;
    std::vector<std::string> testNames = {"Functional Test", "Load Test", "STL Test"};
    std::vector<std::vector<double>> testResults;
    TestParameters testParams;
    SmartPointerManager ptrManager; 

    display_help();

    while (running) {
        std::cout << "\nEnter command (/help for help): ";
        std::cin >> command;

        if (command == "/help") {
            display_help();
        }
        else if (command == "1") {
            // Запустить функциональные тесты
            run_functional_tests(); 
        }
        else if (command == "2") {
            // Запустит лоады
            double creationTime = test_creation(testParams.creation_time);
            double copyTime = test_copy(testParams.copy_time);
            double assignmentTime = test_assignment(testParams.assignment_time);
            double derefTime = test_dereference(testParams.dereference_time);
            testResults.emplace_back(std::vector<double>{creationTime, copyTime, assignmentTime, derefTime});
            testNames.push_back("Load Test");
        }
        else if (command == "3") {
            // Запустить стл тесты
            std::vector<double> stlResults = run_stl_tests(); // Вернет вектор результатов
            testResults.push_back(stlResults);
            testNames.push_back("STL Test");
        }
        else if (command == "4") {
            // Посмотреть поинтеры
            manage_smart_pointers(ptrManager);
        }
        else if (command == "s") {
            // Задать параметры
            configure_test_parameters(testParams);
        }
        else if (command == "r") {
            // Результаты теста
            if (testResults.empty()) {
                std::cout << "No test results to display.\n";
            }
            else {
                print_results(testNames, testResults);
            }
        }
        else if (command == "q") {
            running = false;
        }
        else {
            std::cout << "Unknown command. Try again.\n";
        }
    }
}