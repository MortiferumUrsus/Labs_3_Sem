#include "data_generator.h"
#include "array_sequence.h"
#include <cstdlib>
#include <ctime>
#include <string>

// Функция для генерации последовательности Person
Sequence<Person>* generate_data(int size) {
    ArraySequence<Person>* sequence = new ArraySequence<Person>(size);

    std::string first_names[] = {"Donald", "Joe", "Jane", "Alice", "Bob", "Mike"};
    std::string last_names[] = {"Tramp", "Biden", "Smith", "Johnson", "Williams", "Black ", "Jones"};
    std::string genders[] = {"Combat helicopter", "Cucumber", "Male", "Female"}; 

    int num_first_names = sizeof(first_names)/sizeof(first_names[0]);
    int num_last_names = sizeof(last_names)/sizeof(last_names[0]);
    int num_genders = sizeof(genders)/sizeof(genders[0]);

    std::srand(std::time(nullptr));

    for (int i = 0; i < size; ++i) {
        Person person;
        person.first_name = first_names[std::rand() % num_first_names];
        person.last_name = last_names[std::rand() % num_last_names];
        person.year_of_birth = 1950 + std::rand() % 71; // Год от 1950 до 2020
        person.height = 150.0f + static_cast<float>(std::rand() % 51); // Рост от 150 до 200 см
        person.weight = 50.0f + static_cast<float>(std::rand() % 51); // Вес от 50 до 100 кг
        person.gender = genders[std::rand() % num_genders];

        sequence->set(i, person);
    }

    return sequence;
}