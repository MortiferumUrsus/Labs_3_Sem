#include <iostream>
#include "ui.h"


int main() {
        start();
    return 0;
}

/*
g++ main.cpp functional_tests.cpp load_tests.cpp stl_tests.cpp smrt_ptr.h ui.cpp -o my_program

.\my_program.exe


1. Пофиксить ручной птр при 2 - x - бесконечный вывод (если пытаться из
стдин считать целое, а там что-то другое, то биг трабл)
2. В Функциональных тестах нужен тест на удаление 
3. 

Лаба сдана на:
12/15
*/
