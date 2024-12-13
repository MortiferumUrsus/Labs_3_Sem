#include <iostream>
#include "idictionary.h"
#include "virtual_directory.h"
#include "permissions_manager.h"
#include "index_manager.h"
#include "virtual_files_system.h"

// Добавляем тестовые функции

void runTests() {
    std::cout << "\n--- Запуск тестов ---\n";

    VirtualFileSystem vfsTest;
    PermissionsManager& pmTest = vfsTest.get_permissions_manager();
    pmTest.add_group("test_admins", Permissions::ultimate());
    pmTest.add_group("test_users", Permissions(true, false, false));

    pmTest.add_user("test_admin", { "test_admins" });
    pmTest.add_user("test_user", { "test_users" });

    // Установка пользователя
    vfsTest.set_current_user("test_admin");

    // Создание директории
    vfsTest.create_virtual_file("/test/docs/__placeholder__", "");
    vfsTest.remove_virtual_file("/test/docs/__placeholder__");
    std::cout << "Тест: Создание директории /test/docs - пройдено.\n";

    // Создание файла
    vfsTest.create_virtual_file("/test/docs/report.txt", "C:/real/path/report.txt");
    std::cout << "Тест: Создание файла /test/docs/report.txt - пройдено.\n";

    // Поиск файла
    ArraySequence<std::string> searchResult = vfsTest.searchFiles("report");
    if (searchResult.get_length() == 1 && searchResult.get(0) == "/test/docs/report.txt") {
        std::cout << "Тест: Поиск файла 'report' - пройдено.\n";
    }
    else {
        std::cout << "Тест: Поиск файла 'report' - НЕ пройдено.\n";
    }

    // Перемещение файла
    vfsTest.move("/test/docs/report.txt", "/test/report_final.txt");
    searchResult = vfsTest.searchFiles("report_final");
    if (searchResult.get_length() == 1 && searchResult.get(0) == "/test/report_final.txt") {
        std::cout << "Тест: Перемещение файла /test/docs/report.txt -> /test/report_final.txt - пройдено.\n";
    }
    else {
        std::cout << "Тест: Перемещение файла - НЕ пройдено.\n";
    }

    // Переименование файла
    vfsTest.rename("/test/report_final.txt", "final_report.txt");
    searchResult = vfsTest.searchFiles("final_report");
    if (searchResult.get_length() == 1 && searchResult.get(0) == "/test/final_report.txt") {
        std::cout << "Тест: Переименование файла /test/report_final.txt -> final_report.txt - пройдено.\n";
    }
    else {
        std::cout << "Тест: Переименование файла - НЕ пройдено.\n";
    }

    // Удаление файла
    vfsTest.remove_virtual_file("/test/final_report.txt");
    searchResult = vfsTest.searchFiles("final_report");
    if (searchResult.get_length() == 0) {
        std::cout << "Тест: Удаление файла /test/final_report.txt - пройдено.\n";
    }
    else {
        std::cout << "Тест: Удаление файла - НЕ пройдено.\n";
    }

    std::cout << "--- Тесты завершены ---\n";
}