#include "sort_tests.h"
#include "data_generator.h"
#include "isorter.h"
#include "sorters/batcher_sorter.h"
#include "sorters/binary_insertion_sorter.h"
#include "sorters/bubble_sorter.h"
#include "sorters/heap_sorter.h"
#include "sorters/insertion_sorter.h"
#include "sorters/merge_sorter.h"
#include "sorters/quadratic_selection_sorter.h"
#include "sorters/quick_sorter.h"
#include "sorters/selection_sorter.h"
#include "sorters/shaker_sorter.h"
#include "sorters/shell_sorter.h"
#include "sorters/tree_selection_sorter.h"
#include "comparator.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <future>
#include <mutex>
#include <algorithm>
#include <tuple>
#include "array_sequence.h"

// Возвращает имя сортировщика
std::string get_sorter_name(ISorter<Person>* sorter) {
    if (dynamic_cast<BatcherSorter<Person>*>(sorter)) return "Batcher Sort";
    if (dynamic_cast<BinaryInsertionSorter<Person>*>(sorter)) return "Binary Insertion Sort";
    if (dynamic_cast<BubbleSorter<Person>*>(sorter)) return "Bubble Sort";
    if (dynamic_cast<HeapSorter<Person>*>(sorter)) return "Heap Sort";
    if (dynamic_cast<InsertionSorter<Person>*>(sorter)) return "Insertion Sort";
    if (dynamic_cast<MergeSorter<Person>*>(sorter)) return "Merge Sort";
    if (dynamic_cast<QuadraticSelectionSorter<Person>*>(sorter)) return "Quadratic Selection Sort";
    if (dynamic_cast<QuickSorter<Person>*>(sorter)) return "Quick Sort";
    if (dynamic_cast<SelectionSorter<Person>*>(sorter)) return "Selection Sort";
    if (dynamic_cast<ShakerSorter<Person>*>(sorter)) return "Shaker Sort";
    if (dynamic_cast<ShellSorter<Person>*>(sorter)) return "Shell Sort";
    if (dynamic_cast<TreeSelectionSorter<Person>*>(sorter)) return "Tree Selection Sort";
    return "Unknown Sorter";
}

void run_functional_tests(const std::string& output_file) {
    std::cout << "Running functional tests...\n";
    std::ofstream csv(output_file);
    csv << "Algorithm,Criteria,Pass/Fail\n";

    int test_size = 1000;
    std::cout << "Functional tests starting with data size: " << test_size << "\n";

    Sequence<Person>* test_data = load_data("generated_data.csv", test_size);

    std::vector<ISorter<Person>*> sorters = {
        new BatcherSorter<Person>(),
        new BinaryInsertionSorter<Person>(),
        new BubbleSorter<Person>(),
        new HeapSorter<Person>(),
        new InsertionSorter<Person>(),
        new MergeSorter<Person>(),
        new QuadraticSelectionSorter<Person>(),
        new QuickSorter<Person>(),
        new SelectionSorter<Person>(),
        new ShakerSorter<Person>(),
        new ShellSorter<Person>(),
        new TreeSelectionSorter<Person>()
    };

    std::vector<std::pair<int (*)(const Person&, const Person&), std::string>> comparators = {
        {compare_by_first_name, "First Name"},
        {compare_by_last_name, "Last Name"},
        {compare_by_middle_name, "Middle Name"},
        {compare_by_address, "Address"},
        {compare_by_occupation, "Occupation"},
        {compare_by_gender, "Gender"},
        {compare_by_education, "Education"},
        {compare_by_year_of_birth, "Year of Birth"},
        {compare_by_number_of_children, "Number of Children"},
        {compare_by_years_of_experience, "Years of Experience"},
        {compare_by_height, "Height"},
        {compare_by_weight, "Weight"},
        {compare_by_income, "Income"},
        {compare_by_married, "Married"},
        {compare_by_has_car, "Has Car"}
    };

    for (auto* sorter : sorters) {
        for (const auto& comp : comparators) {
            std::cout << "Testing " << get_sorter_name(sorter) << " with criteria: " << comp.second << "\n";

            try {
                Sequence<Person>* sorted = sorter->sort(test_data, comp.first);

                bool is_sorted = true;
                for (int i = 1; i < sorted->get_length(); ++i) {
                    if (comp.first(sorted->get(i - 1), sorted->get(i)) > 0) {
                        is_sorted = false;
                        break;
                    }
                }

                csv << get_sorter_name(sorter) << "," << comp.second << "," << (is_sorted ? "Pass" : "Fail") << "\n";
                delete sorted;
            } catch (const std::exception& e) {
                csv << get_sorter_name(sorter) << "," << comp.second << ",Fail\n";
                std::cerr << "Error during testing: " << e.what() << "\n";
            }
        }
    }

    for (auto* sorter : sorters) {
        delete sorter;
    }

    delete test_data;
    csv.close();
    std::cout << "Functional tests completed. Results saved to functional_tests.csv.\n";
}


// Объявляем mutex
std::mutex csv_mutex;

void run_load_tests(const std::string& output_file, int (*comparator)(const Person&, const Person&), int data_size) {
    std::cout << "Running performance tests...\n";
    std::ofstream csv(output_file);
    csv << "Algorithm,Data Size,Time (ms)\n";

    std::vector<ISorter<Person>*> sorters = {
        new BatcherSorter<Person>(),
        new BinaryInsertionSorter<Person>(),
        new BubbleSorter<Person>(),
        new HeapSorter<Person>(),
        new InsertionSorter<Person>(),
        new MergeSorter<Person>(),
        new QuadraticSelectionSorter<Person>(),
        new QuickSorter<Person>(),
        new SelectionSorter<Person>(),
        new ShakerSorter<Person>(),
        new ShellSorter<Person>(),
        new TreeSelectionSorter<Person>()
    };

    std::vector<std::tuple<std::string, int, double>> results;

    for (auto* sorter : sorters) {
        std::vector<std::future<void>> futures;
        std::cout << "Testing " << get_sorter_name(sorter) << "\n";

        for (int size = 1; size <= data_size; size++) {
            futures.push_back(std::async(std::launch::async, [&, sorter, size]() {
                Sequence<Person>* test_data = load_data("generated_data.csv", size);

                auto start = std::chrono::high_resolution_clock::now();
                Sequence<Person>* sorted = sorter->sort(test_data, comparator);
                auto end = std::chrono::high_resolution_clock::now();

                std::chrono::duration<double, std::milli> elapsed = end - start;
                {
                    std::lock_guard<std::mutex> lock(csv_mutex);
                    results.emplace_back(get_sorter_name(sorter), size, elapsed.count());
                }

                delete sorted;
                delete test_data;
            }));
        }

        for (auto& fut : futures) {
            fut.get();
        }
    }

    // Сортировка результатов по названию алгоритма и размеру данных
    std::sort(results.begin(), results.end(), [](const auto& a, const auto& b) {
        return std::tie(std::get<0>(a), std::get<1>(a)) < std::tie(std::get<0>(b), std::get<1>(b));
    });

    // Запись отсортированных результатов в файл
    for (const auto& result : results) {
        csv << std::get<0>(result) << "," << std::get<1>(result) << "," << std::get<2>(result) << "\n";
    }

    for (auto* sorter : sorters) {
        delete sorter;
    }

    csv.close();
    std::cout << "Performance tests completed. Results saved to " << output_file << ".\n";
}