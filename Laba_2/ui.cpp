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
#include "sort_tests.h"
#include "pair_sequence.h"
#include <cstdlib>
#include <variant>

int (*select_comparator(int comparator_choice))(const Person&, const Person&) {
    switch (comparator_choice) {
        case 1:
            return compare_by_first_name;
        case 2:
            return compare_by_last_name;
        case 3:
            return compare_by_middle_name;
        case 4:
            return compare_by_address;
        case 5:
            return compare_by_occupation;
        case 6:
            return compare_by_gender;
        case 7:
            return compare_by_education;
        case 8:
            return compare_by_year_of_birth;
        case 9:
            return compare_by_number_of_children;
        case 10:
            return compare_by_years_of_experience;
        case 11:
            return compare_by_height;
        case 12:
            return compare_by_weight;
        case 13:
            return compare_by_income;
        case 14:
            return compare_by_married;
        case 15:
            return compare_by_has_car;
        default:
            std::cout << "Invalid comparator choice.\n";
            return nullptr;
    }
}

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
            sorter_name = "Heap Sort";
            break;
        case 6:
            sorter_name = "Merge Sort";
            break;
        case 7:
            sorter_name = "Quadratic Selection Sort";
            break;
        case 8:
            sorter_name = "Quick Sort";
            break;
        case 9:
            sorter_name = "Selection Sort";
            break;
        case 10:
            sorter_name = "Shell Sort";
            break;
        case 11:
            sorter_name = "Tree Selection Sort";
            break;
        case 12:
            sorter_name = "Batcher Sort";
            break;
        default:
            sorter_name = "Unknown Sort";
            break;
    }
    return sorter_name;
}

std::string which_comparator(int comparator_choice) {
    std::string comparator_name;
    switch (comparator_choice) {
        case 1:
            comparator_name = "First Name";
            break;
        case 2:
            comparator_name = "Last Name";
            break;
        case 3:
            comparator_name = "Middle Name";
            break;
        case 4:
            comparator_name = "Address";
            break;
        case 5:
            comparator_name = "Occupation";
            break;
        case 6:
            comparator_name = "Gender";
            break;
        case 7:
            comparator_name = "Education";
            break;
        case 8:
            comparator_name = "Year of Birth";
            break;
        case 9:
            comparator_name = "Number of Children";
            break;
        case 10:
            comparator_name = "Years of Experience";
            break;
        case 11:
            comparator_name = "Height";
            break;
        case 12:
            comparator_name = "Weight";
            break;
        case 13:
            comparator_name = "Income";
            break;
        case 14:
            comparator_name = "Married";
            break;
        case 15:
            comparator_name = "Has Car";
            break;
        default:
            comparator_name = "Unknown";
            break;
    }
    return comparator_name;
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
            case 5: std::cout << "Heap Sort"; break;
            case 6: std::cout << "Merge Sort"; break;
            case 7: std::cout << "Quadratic Selection Sort"; break;
            case 8: std::cout << "Quick Sort"; break;
            case 9: std::cout << "Selection Sort"; break;
            case 10: std::cout << "Shell Sort"; break;
            case 11: std::cout << "Tree Selection Sort"; break;
            case 12: std::cout << "Batcher Sort"; break;
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
        std::cout << "3. Set data size and generate (current: " << data_size << ")\n";
        std::cout << "4. Regenerate data\n";
        std::cout << "5. Sort data and measure time\n";
        std::cout << "6. View data\n";
        std::cout << "7. View sorted data\n";
        std::cout << "8. Start functional tests (to start need minimum data: 1000)\n";
        std::cout << "9. Start load tests\n";
        std::cout << "10. Make plot\n";
        std::cout << "11. Exit\n";
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
            std::cout << "5. Heap Sort\n";
            std::cout << "6. Merge Sort\n";
            std::cout << "7. Quadratic Selection Sort\n";
            std::cout << "8. Quick Sort\n";
            std::cout << "9. Selection Sort\n";
            std::cout << "10. Shell Sort\n";
            std::cout << "11. Tree Selection Sort\n";
            std::cout << "12. Batcher Sort\n";
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
            const std::string filename = "generated_data.csv";

            // Проверяем наличие файла и удаляем его, если он существует
            if (std::filesystem::exists(filename)) {
                std::filesystem::remove(filename);
            }
            data_file = generate_data(data_size);
            std::cout << "Data successfully generated.\n";
        } else if (choice == 4) {
            const std::string filename = "generated_data.csv";

            // Проверяем наличие файла и удаляем его, если он существует
            if (std::filesystem::exists(filename)) {
                std::filesystem::remove(filename);
            }
            data_file = generate_data(data_size);
            std::cout << "Data successfully generated.\n";
        } else if (choice == 5) {
            if (data_file.empty()) {
                std::cout << "No data file found. Generate data first.\n";
                continue;
            }
            if (data) delete data;
            std::string param = which_comparator(comparator_choice);
            using DataVariant = std::variant<bool, int, float, std::string>;
            PairSequence<std::variant<int, float, std::string, bool>>* data = load_data_by_param(data_file, param, data_size);
            if (!data) {
                std::cout << "Failed to load data.\n";
                continue;
            }
            // Создание сортировщика на основе выбора пользователя
            ISorter<PairSequence<std::variant<int, float, std::string, bool>>>* sorter = nullptr;
            switch (algorithm_choice) {
                case 1:
                    sorter = new InsertionSorter<std::variant<int, float, std::string, bool>>();
                    break;
                case 2:
                    sorter = new BinaryInsertionSorter<std::variant<int, float, std::string, bool>>();
                    break;
                case 3:
                    sorter = new ShakerSorter<std::variant<int, float, std::string, bool>>();
                    break;
                case 4:
                    sorter = new BubbleSorter<std::variant<int, float, std::string, bool>>();
                    break;
                case 5:
                    sorter = new HeapSorter<std::variant<int, float, std::string, bool>>();
                    break;
                case 6:
                    sorter = new MergeSorter<std::variant<int, float, std::string, bool>>();
                    break;
                case 7:
                    sorter = new QuadraticSelectionSorter<std::variant<int, float, std::string, bool>>();
                    break;
                case 8:
                    sorter = new QuickSorter<std::variant<int, float, std::string, bool>>();
                    break;
                case 9:
                    sorter = new SelectionSorter<std::variant<int, float, std::string, bool>>();
                    break;
                case 10:
                    sorter = new ShellSorter<std::variant<int, float, std::string, bool>>();
                    break;
                case 11:
                    sorter = new TreeSelectionSorter<std::variant<int, float, std::string, bool>>();
                    break;
                case 12:
                    sorter = new BatcherSorter<std::variant<int, float, std::string, bool>>();
                    break;
                default:
                    std::cerr << "Invalid algorithm choice.\n";
                    return;
            }


            // Выбор функции сравнения на основе выбора пользователя
            int (*comparator)(const Person&, const Person&) = select_comparator(comparator_choice);
            // Определение имени файла в зависимости от выбранного алгоритма
            std::string sorter_name;
            sorter_name = which_algorithm(algorithm_choice);

            std::string output_filename = "sorted_data_" + sorter_name + ".csv";

            std::cout << "Sorting...\n";
            auto start = std::chrono::high_resolution_clock::now();
            sorter->sort(*data, comparator);
            auto end = std::chrono::high_resolution_clock::now();

            save_data_to_file(data, output_filename);

            std::chrono::duration<double, std::milli> elapsed = end - start;
            std::cout << "Sorting completed in " << elapsed.count() << " milliseconds.\n";


            // Очистка памяти
            delete data;
            delete sorter;

        } else if (choice == 6) {
            // Вывод данных на экран
            Sequence<Person>* data = load_data_full(data_file, 20);
            print_data(data);
        } else if (choice == 7) {
            // Вывод отсортированных данных на экран
            std::string sorter_name;
            sorter_name = which_algorithm(algorithm_choice);

            std::string sort_data_file = "sorted_data_" + sorter_name + ".csv";
            std::cout << sort_data_file << "\n";
            Sequence<Person>* data = load_data_full(sort_data_file, 20);
            print_data(data);
        } else if (choice == 8) {
            if (data_size < 100){
                std::cout << "To run functional tests need data size 1000 \n";
                continue;
            } else {;
                run_functional_tests("functional_tests.csv");
            }
            continue;
        } else if (choice == 9) {
            int (*comparator)(const Person&, const Person&) = select_comparator(comparator_choice);
            std::string param = which_comparator(comparator_choice);
            run_load_tests("load_tests.csv", comparator, data_size, param);
            continue;
        } else if (choice == 10) {
            std::cout << "Run python file: 'plot.py' \n";
        } else if (choice == 11) {
            // Выход из программы
            break;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }

    // Освобождение памяти
    if (data) delete data;

}