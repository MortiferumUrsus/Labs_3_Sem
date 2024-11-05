#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "load_tests.h"
#include "functional_tests.h"
#include "stl_tests.h"



void display_help() {
    std::cout << "Available commands:" << std::endl;
    std::cout << "/help - Show this help message" << std::endl;
    std::cout << "1 - Run functional test" << std::endl;
    std::cout << "2 - Run load test" << std::endl;
    std::cout << "3 - Run STL test" << std::endl;
    std::cout << "q - Quit the program" << std::endl;
    std::cout << "r - Print results of tests" << std::endl;
}

void print_results(const std::vector<std::string>& testNames, const std::vector<std::vector<double>>& results) {
    std::cout << std::fixed << std::setprecision(2);
    
    std::cout << "\nTest Results:\n";
    std::cout << std::setw(20) << "Test Name" 
              << std::setw(15) << "Creation" 
              << std::setw(15) << "Copy" 
              << std::setw(15) << "Assignment" 
              << std::setw(15) << "Dereference\n";
    std::cout << "--------------------------------------------------------------------------------------------------\n";
    
    for (size_t i = 0; i < testNames.size(); ++i) {
        std::cout << std::setw(20) << testNames[i]
                  << std::setw(15) << results[i][0]
                  << std::setw(15) << results[i][1]
                  << std::setw(15) << results[i][2]
                  << std::setw(15) << results[i][3] << std::endl;
    }
}

void start() {
    std::string command;
    bool running = true;
    std::vector<std::string> testNames = {"Load Test", "STL Test"};
    std::vector<std::vector<double>> testResults;

    while (running) {
        std::cout << "\nEnter command (/help for help): ";
        std::cin >> command;

        if (command == "/help") {
            display_help();
        } else if (command == "1") {
            run_functional_tests();
        } else if (command == "2") {
            testResults.push_back(run_load_tests());
        } else if (command == "3") {
            testResults.push_back(run_stl_tests());
        } else if (command == "q") {
            running = false;
            continue;
        } else if (command == "r") {
            print_results(testNames, testResults);
            continue;
        } else {
            std::cout << "Unknown command. Please try again." << std::endl;
        }
    }
}