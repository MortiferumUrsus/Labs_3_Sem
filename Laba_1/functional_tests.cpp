#include "functional_tests.h"
#include "smrt_ptr.h"
#include <cassert>
#include <iostream>
#include <vector>

void create_copy_test(){
    smrt_ptr<int> ptr1(new int(5));
    assert(ptr1.use_count() == 1);
    smrt_ptr<int> ptr2 = ptr1;
    assert(ptr1.use_count() == 2);
    assert(ptr2.use_count() == 2);
    assert(ptr2.operator->() == ptr1.operator->());
    smrt_ptr<int> ptr3;
    ptr2 = ptr3;
    assert(ptr2.use_count() == 0);
    assert(ptr3.use_count() == 0);
}

void change_value_test(){
    smrt_ptr<int> ptr1(new int(5));
    smrt_ptr<int> ptr2 = ptr1;
    assert(*ptr1 == *ptr2);
    assert(*ptr1 == 5 && *ptr2 == 5);
    *ptr2 = 10;
    assert(*ptr1 == *ptr2);
    assert(*ptr1 == 10 && *ptr2 == 10);
}

void dereference_empty_ptr_test(){
    smrt_ptr<int> ptr1; 
    try{ 
        *ptr1 = 42; 
        assert(false && "Should have thrown");
    } catch(...){
        //expected
    }
}


void use_count_empty_ptr_test(){
    smrt_ptr<int> ptr1;
    assert(ptr1.use_count() == 0);
}

void run_functional_tests() {
    // Тест разыменовывания
    dereference_empty_ptr_test();
    // Тест создания и копирования
    create_copy_test();
    // Тест смены значения
    change_value_test();
    // Тест проверки количества указателей 
    use_count_empty_ptr_test();
}

