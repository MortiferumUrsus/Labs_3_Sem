#include <iostream>
#include "ui.h"

int main() {
    start(); // Запуск интерфейса пользователя
    return 0;
}
/*
g++ main.cpp array_sequence.h binary_insertion_sorter.h insertion_sorter.h comparator.h data_generator.cpp data_structure.h isorter.h sequence.cpp shaker_sorter.h ui.cpp smrt_ptr.h -o sorting_program

.\sorting_program.exe
*/ 

/*
1. Надо добавить генерацию из файлов и чтение их с последующим сортированием. Делать это лучше всего 
по ключевому элементу и индексу, все остальное не отгружать 
2. Сделать тесты 
3. Добавить сортировочек и сделать графички 
4. Разобраться с наименованием. Я выбираю snake. 
*/