#include "sort_tests.h"
#include "data_generator.h"
#include "isorter.h"
#include "sorters/batcher_sorter.h"
#include "sorters/binary_insertion_sorter.h"
#include "sorters/bubble_sorter.h"
#include "sorters/counting_sorter.h"
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
#include <fstream>
#include <chrono>
#include <vector>
#include <string>
#include "array_sequence.h"

// Возвращает имя сортировщика
std::string get_sorter_name(ISorter<Person>* sorter) {
    if (dynamic_cast<BatcherSorter<Person>*>(sorter)) return "Batcher Sort";
    if (dynamic_cast<BinaryInsertionSorter<Person>*>(sorter)) return "Binary Insertion Sort";
    if (dynamic_cast<BubbleSorter<Person>*>(sorter)) return "Bubble Sort";
    if (dynamic_cast<CountingSorter<Person>*>(sorter)) return "Counting Sort";
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
    std::ofstream csv(output_file);
    csv << "Algorithm,Criteria,Pass/Fail\n";

    // Тестовые данные
    int test_size = 100000;
    Sequence<Person>* test_data = load_data("generated_data.csv", test_size);

    // Список алгоритмов сортировки
    std::vector<ISorter<Person>*> sorters = {
        new BatcherSorter<Person>(),
        new BinaryInsertionSorter<Person>(),
        new BubbleSorter<Person>(),
        new CountingSorter<Person>(),
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

    // Список компараторов
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
            try {
                Sequence<Person>* sorted = sorter->sort(test_data, comp.first);

                // Проверяем, правильно ли отсортированы данные
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
            }
        }
    }

    for (auto* sorter : sorters) {
        delete sorter;
    }

    delete test_data;
    csv.close();
}

void run_performance_tests(const std::string& output_file) {
    std::ofstream csv(output_file);
    csv << "Algorithm,Data Size,Time (ms)\n";

    // Список алгоритмов сортировки
    std::vector<ISorter<Person>*> sorters = {
        new BatcherSorter<Person>(),
        new BinaryInsertionSorter<Person>(),
        new BubbleSorter<Person>(),
        new CountingSorter<Person>(),
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

    // Наборы данных разного размера
    std::vector<int> data_sizes = {1000, 10000, 100000, 1000000};

    for (auto* sorter : sorters) {
        for (int size : data_sizes) {
            Sequence<Person>* test_data = load_data("generated_data.csv", size);

            auto start = std::chrono::high_resolution_clock::now();
            Sequence<Person>* sorted = sorter->sort(test_data, compare_by_first_name);
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double, std::milli> elapsed = end - start;
            csv << get_sorter_name(sorter) << "," << size << "," << elapsed.count() << "\n";

            delete sorted;
            delete test_data;
        }
    }

    for (auto* sorter : sorters) {
        delete sorter;
    }

    csv.close();
}
