#include <iostream>
#include <string>
#include "smrt_ptr.h"
#include "sequence.h"
#include "array_sequence.h"
#include "data_structure.h"
#include "data_generator.h"
#include "isorter.h"
#include "comparator.h"
#include <chrono>
#include <filesystem>
#include "data_utils.h"
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
#include "sort_tests.h"


std::string which_algorithm(int algorithm_choice) {
    std::string sorter_name;
    switch (algorithm_choice) {
        case 1:
            sorter_name = "Insertion Sort";
            break;
        case 2:
            sorter_name = "Binary Insertion Sort";
            break;
        case 3:
            sorter_name = "Shaker Sort";
            break;
        case 4:
            sorter_name = "Bubble Sort";
            break;
        case 5:
            sorter_name = "Counting Sort";
            break;
        case 6:
            sorter_name = "Heap Sort";
            break;
        case 7:
            sorter_name = "Merge Sort";
            break;
        case 8:
            sorter_name = "Quadratic Selection Sort";
            break;
        case 9:
            sorter_name = "Quick Sort";
            break;
        case 10:
            sorter_name = "Selection Sort";
            break;
        case 11:
            sorter_name = "Shell Sort";
            break;
        case 12:
            sorter_name = "Tree Selection Sort";
            break;
        case 13:
            sorter_name = "Batcher Sort";
            break;
        default:
            sorter_name = "Unknown Sort";
            break;
    }
    return sorter_name;
}

void print_data(Sequence<Person>* data){
    int length = data->get_length();
    std::cout << "------------------------------------\n";
    for (int i = 0; i < length; ++i) {
        Person p = data->get(i);
        std::cout << "First Name: " << p.first_name << "\n"
                << "Last Name: " << p.last_name << "\n"
                << "Middle Name: " << p.middle_name << "\n"
                << "Address: " << p.address << "\n"
                << "Occupation: " << p.occupation << "\n"
                << "Year of Birth: " << p.year_of_birth << "\n"
                << "Height: " << p.height << "\n"
                << "Weight: " << p.weight << "\n"
                << "Income: " << p.income << "\n"
                << "Gender: " << p.gender << "\n"
                << "Education: " << p.education << "\n"
                << "Married: " << (p.married ? "Yes" : "No") << "\n"
                << "Has Car: " << (p.has_car ? "Yes" : "No") << "\n"
                << "Number of Children: " << p.number_of_children << "\n"
                << "Years of Experience: " << p.years_of_experience << "\n"
                << "------------------------------------\n";
        if (i >= 10) {
            std::cout << "... (data truncated)\n";
            break;
        }
    }
}

void start() {
    int data_size = 10000; // Размер данных по умолчанию
    Sequence<Person>* data = nullptr; // Указатель на данные
    int algorithm_choice = 1; // Выбранный алгоритм сортировки
    int comparator_choice = 1; // Выбранный компаратор
    std::string data_file = "generated_data.csv"; // Файл с данными пользователей

    while (true) {
        // Вывод меню
        std::cout << "Menu: \n";
        std::cout << "1. Select sorting algorithm (current: ";
        switch (algorithm_choice) {
            case 1: std::cout << "Insertion Sort"; break;
            case 2: std::cout << "Binary Insertion Sort"; break;
            case 3: std::cout << "Shaker Sort"; break;
            case 4: std::cout << "Bubble Sort"; break;
            case 5: std::cout << "Counting Sort"; break;
            case 6: std::cout << "Heap Sort"; break;
            case 7: std::cout << "Merge Sort"; break;
            case 8: std::cout << "Quadratic Selection Sort"; break;
            case 9: std::cout << "Quick Sort"; break;
            case 10: std::cout << "Selection Sort"; break;
            case 11: std::cout << "Shell Sort"; break;
            case 12: std::cout << "Tree Selection Sort"; break;
            case 13: std::cout << "Batcher Sort"; break;
            default: std::cout << "Unknown"; break;
        }
        std::cout << ")\n";
        std::cout << "2. Select sorting criteria (current: ";
        switch (comparator_choice) {
            case 1: std::cout << "First Name"; break;
            case 2: std::cout << "Last Name"; break;
            case 3: std::cout << "Middle name"; break;
            case 4: std::cout << "Address"; break;
            case 5: std::cout << "Occupation"; break;
            case 6: std::cout << "Gender"; break;
            case 7: std::cout << "Education"; break;
            case 8: std::cout << "Year of Birth"; break;
            case 9: std::cout << "Number of children"; break;
            case 10: std::cout << "Years of experience"; break;
            case 11: std::cout << "Height"; break;
            case 12: std::cout << "Weight"; break;
            case 13: std::cout << "Income"; break;
            case 14: std::cout << "Married"; break;
            case 15: std::cout << "Has_car"; break;
            default: std::cout << "Unknown"; break;
        }
        std::cout << ")\n";
        std::cout << "3. Set data size (current: " << data_size << ")\n";
        std::cout << "4. Generate data\n";
        std::cout << "5. Sort data and measure time\n";
        std::cout << "6. View data\n";
        std::cout << "7. View sorted data\n";
        std::cout << "8. Start functional tests\n";
        std::cout << "9. Start load tests\n";
        std::cout << "10. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            // Выбор алгоритма сортировки
            std::cout << "Select sorting algorithm:\n";
            std::cout << "1. Insertion Sort\n";
            std::cout << "2. Binary Insertion Sort\n";
            std::cout << "3. Shaker Sort\n";
            std::cout << "4. Bubble Sort\n";
            std::cout << "5. Counting Sort\n";
            std::cout << "6. Heap Sort\n";
            std::cout << "7. Merge Sort\n";
            std::cout << "8. Quadratic Selection Sort\n";
            std::cout << "9. Quick Sort\n";
            std::cout << "10. Selection Sort\n";
            std::cout << "11. Shell Sort\n";
            std::cout << "12. Tree Selection Sort\n";
            std::cout << "13. Batcher Sort\n";
            std::cout << "Choose an option: ";
            std::cin >> algorithm_choice;
        } else if (choice == 2) {
            // Выбор критерия сортировки
            std::cout << "Select sorting criteria:\n";
            std::cout << "1. First Name\n";
            std::cout << "2. Last Name\n";
            std::cout << "3. Middle name\n";
            std::cout << "4. Address\n";
            std::cout << "5. Occupation\n";
            std::cout << "6. Gender\n";
            std::cout << "7. Education\n"; 
            std::cout << "8. Year of Birth\n"; 
            std::cout << "9. Number of children\n"; 
            std::cout << "10. Years of experience\n";
            std::cout << "11. Height\n"; 
            std::cout << "12. Weight\n"; 
            std::cout << "13. Income\n"; 
            std::cout << "14. Married\n";
            std::cout << "15. Has_car\n";
            std::cout << "Choose an option: ";
            std::cin >> comparator_choice;
        } else if (choice == 3) {
            // Установка размера данных
            std::cout << "Enter data size: ";
            std::cin >> data_size;
        } else if (choice == 4) {
            const std::string filename = "generated_data.csv";

            // Проверяем наличие файла и удаляем его, если он существует
            if (std::filesystem::exists(filename)) {
                std::filesystem::remove(filename);
            }
            data_file = generate_data(data_size);
        } else if (choice == 5) {
            if (data_file.empty()) {
                std::cout << "No data file found. Generate data first.\n";
                continue;
            }
            if (data) delete data;
            data = load_data(data_file, data_size);
            if (!data) {
                std::cout << "Failed to load data.\n";
                continue;
            }
            // Создание сортировщика на основе выбора пользователя
            ISorter<Person>* sorter = nullptr;
            switch (algorithm_choice) {
                case 1:
                    sorter = new InsertionSorter<Person>();
                    break;
                case 2:
                    sorter = new BinaryInsertionSorter<Person>();
                    break;
                case 3:
                    sorter = new ShakerSorter<Person>();
                    break;
                case 4:
                    sorter = new BubbleSorter<Person>();
                    break;
                case 5:
                    sorter = new CountingSorter<Person>();
                    break;
                case 6:
                    sorter = new HeapSorter<Person>();
                    break;
                case 7:
                    sorter = new MergeSorter<Person>();
                    break;
                case 8:
                    sorter = new QuadraticSelectionSorter<Person>();
                    break;
                case 9:
                    sorter = new QuickSorter<Person>();
                    break;
                case 10:
                    sorter = new SelectionSorter<Person>();
                    break;
                case 11:
                    sorter = new ShellSorter<Person>();
                    break;
                case 12:
                    sorter = new TreeSelectionSorter<Person>();
                    break;
                case 13:
                    sorter = new BatcherSorter<Person>();
                    break;
                default:
                    std::cout << "Invalid algorithm choice.\n";
                    continue;
            }

            // Выбор функции сравнения на основе выбора пользователя
            int (*comparator)(const Person&, const Person&) = nullptr;
            switch (comparator_choice) {
                case 1:
                    comparator = compare_by_first_name;
                    break;
                case 2:
                    comparator = compare_by_last_name;
                    break;
                case 3:
                    comparator = compare_by_middle_name;
                    break;
                case 4:
                    comparator = compare_by_address;
                    break;
                case 5:
                    comparator = compare_by_occupation;
                    break;
                case 6:
                    comparator = compare_by_gender;
                    break;
                case 7:
                    comparator = compare_by_education;
                    break;
                case 8:
                    comparator = compare_by_year_of_birth;
                    break;
                case 9:
                    comparator = compare_by_number_of_children;
                    break;
                case 10:
                    comparator = compare_by_years_of_experience;
                    break;
                case 11:
                    comparator = compare_by_height;
                    break;
                case 12:
                    comparator = compare_by_weight;
                    break;
                case 13:
                    comparator = compare_by_income;
                    break;
                case 14:
                    comparator = compare_by_married;
                    break;
                case 15:
                    comparator = compare_by_has_car;
                    break;
                default:
                    std::cout << "Invalid comparator choice.\n";
                    continue;
            }
            // Определение имени файла в зависимости от выбранного алгоритма
            std::string sorter_name;
            sorter_name = which_algorithm(algorithm_choice);

            std::string output_filename = "sorted_data_" + sorter_name + ".csv";

            std::cout << "Sorting...\n";
            auto start = std::chrono::high_resolution_clock::now();
            Sequence<Person>* sorted_data = sorter->sort(data, comparator);
            auto end = std::chrono::high_resolution_clock::now();

            save_data_to_file(sorted_data, output_filename);

            std::chrono::duration<double, std::milli> elapsed = end - start;
            std::cout << "Sorting completed in " << elapsed.count() << " milliseconds.\n";


            // Очистка памяти
            delete sorted_data;
            delete sorter;

        } else if (choice == 6) {
            // Вывод данных на экран
            Sequence<Person>* data = load_data(data_file, data_size);
            print_data(data);
        } else if (choice == 7) {
            // Вывод отсортированных данных на экран
            std::string sorter_name;
            sorter_name = which_algorithm(algorithm_choice);

            std::string sort_data_file = "sorted_data_" + sorter_name + ".csv";
            std::cout << sort_data_file << "\n";
            Sequence<Person>* data = load_data(sort_data_file, data_size);
            print_data(data);
        } else if (choice == 8) {
            std::cout << "Running functional tests...\n";
            run_functional_tests("functional_tests.csv");
            std::cout << "Functional tests completed. Results saved to functional_tests.csv.\n";
        } else if (choice == 9) {
            std::cout << "Running performance tests...\n";
            run_performance_tests("performance_tests.csv");
            std::cout << "Performance tests completed. Results saved to performance_tests.csv.\n";
        } else if (choice == 10) {
            // Выход из программы
            break;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }

    // Освобождение памяти
    if (data) delete data;

}