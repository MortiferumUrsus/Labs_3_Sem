#include "load_tests.h"
#include "functional_tests.h"
#include "stl_tests.h"
#include <iostream>


int main() {
    std::cout << "-------------- functional tests ------------------" << std::endl;
    run_functional_tests();

    std::cout << "---------------- load tests --------------------" << std::endl;
    run_load_tests();
    
    std::cout << "----------------- stl tests --------------------" << std::endl;
    run_stl_tests();

    return 0; /// Создать GUI
}