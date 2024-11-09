#include <iostream>
#include <string>
#include "smrt_ptr.h"
#include "sequence.h"
#include "array_sequence.h"
#include "data_structure.h"
#include "data_generator.h"
#include "isorter.h"
#include "insertion_sorter.h"
#include "binary_insertion_sorter.h"
#include "shaker_sorter.h"
#include "comparator.h"
#include <chrono>

void start() {
    int data_size = 10000; // Размер данных по умолчанию
    Sequence<Person>* data = nullptr; // Указатель на данные
    int algorithm_choice = 1; // Выбранный алгоритм сортировки
    int comparator_choice = 1; // Выбранный компаратор

    while (true) {
        // Вывод меню
        std::cout << "Menu: \n";
        std::cout << "1. Select sorting algorithm (current: ";
        switch (algorithm_choice) {
            case 1: std::cout << "Insertion Sort"; break;
            case 2: std::cout << "Binary Insertion Sort"; break;
            case 3: std::cout << "Shaker Sort"; break;
            default: std::cout << "Unknown"; break;
        }
        std::cout << ")\n";
        std::cout << "2. Select sorting criteria (current: ";
        switch (comparator_choice) {
            case 1: std::cout << "First Name"; break;
            case 2: std::cout << "Last Name"; break;
            case 3: std::cout << "Height"; break;
            case 4: std::cout << "Weight"; break;
            case 5: std::cout << "Year of Birth"; break;
            case 6: std::cout << "Gender"; break;
            default: std::cout << "Unknown"; break;
        }
        std::cout << ")\n";
        std::cout << "3. Set data size (current: " << data_size << ")\n";
        std::cout << "4. Generate data\n";
        std::cout << "5. Sort data and measure time\n";
        std::cout << "6. View data\n";
        std::cout << "7. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            // Выбор алгоритма сортировки
            std::cout << "Select sorting algorithm:\n";
            std::cout << "1. Insertion Sort\n";
            std::cout << "2. Binary Insertion Sort\n";
            std::cout << "3. Shaker Sort\n";
            std::cin >> algorithm_choice;
        } else if (choice == 2) {
            // Выбор критерия сортировки
            std::cout << "Select sorting criteria:\n";
            std::cout << "1. First Name\n";
            std::cout << "2. Last Name\n";
            std::cout << "3. Height\n";
            std::cout << "4. Weight\n";
            std::cout << "5. Year of Birth\n";
            std::cout << "6. Gender\n";
            std::cin >> comparator_choice;
        } else if (choice == 3) {
            // Установка размера данных
            std::cout << "Enter data size: ";
            std::cin >> data_size;
        } else if (choice == 4) {
            // Генерация данных
            if (data) delete data;
            data = generate_data(data_size);
            std::cout << "Data generated.\n";
        } else if (choice == 5) {
            if (!data) {
                std::cout << "No data to sort. Generate data first.\n";
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
                    comparator = compare_by_height;
                    break;
                case 4:
                    comparator = compare_by_weight;
                    break;
                case 5:
                    comparator = compare_by_year_of_birth;
                    break;
                case 6:
                    comparator = compare_by_gender;
                    break;
                default:
                    std::cout << "Invalid comparator choice.\n";
                    continue;
            }

            std::cout << "Sorting...\n";
            // Измерение времени сортировки
            auto start = std::chrono::high_resolution_clock::now();
            Sequence<Person>* sorted_data = sorter->sort(data, comparator);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> elapsed = end - start;
            std::cout << "Sorting completed in " << elapsed.count() << " milliseconds.\n";

            // Очистка памяти
            delete sorted_data;
            delete sorter;

        } else if (choice == 6) {
            // Вывод данных на экран
            if (!data) {
                std::cout << "No data to view. Generate data first.\n";
                continue;
            }
            int length = data->get_length();
            for (int i = 0; i < length; ++i) {
                Person p = data->get(i);
                std::cout << p.first_name << " " << p.last_name << ", Year: " << p.year_of_birth
                          << ", Height: " << p.height << ", Weight: " << p.weight << ", Gender: " 
                          << p.gender << "\n""\n";
                if (i >= 100) {
                    std::cout << "... (data truncated)\n";
                    break;
                }
            }
        } else if (choice == 7) {
            // Выход из программы
            break;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }

    // Освобождение памяти
    if (data) delete data;

}