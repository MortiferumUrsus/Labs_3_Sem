#include <iostream>
#include "virtual_files_system.h"
#include "permissions_manager.h"
#include "virtual_directory.h"
#include "virtual_file.h"
#include "ui.h"



void print_menu() {
    std::cout << "\n--- Virtual File System ---\n";
    std::cout << "1. Set current user\n";
    std::cout << "2. Create file\n";
    std::cout << "3. Delete file\n";
    std::cout << "4. Create directory\n";
    std::cout << "5. Delete directory\n";
    std::cout << "6. Move file/directory\n";
    std::cout << "7. Rename file/directory\n";
    std::cout << "8. Change group permissions\n";
    std::cout << "9. Search for files\n";
    std::cout << "10. Display file system\n";
    std::cout << "11. Exit\n";
    std::cout << "Choose an action: ";
}

void start() {
    VirtualFileSystem vfs;

    // Setting up initial groups and users
    PermissionsManager& pm = vfs.get_permissions_manager();
    pm.add_group("admins", Permissions::ultimate());
    pm.add_group("users", Permissions(true, false, false)); // Read only

    pm.add_user("admin", { "admins" });
    pm.add_user("guest", { "users" });

    // Set current user
    std::string username;
    std::cout << "Enter username: ";
    std::cin >> username;
    vfs.set_current_user(username);

    bool running = true;
    while (running) {
        print_menu();
        int choice;
        std::cin >> choice;

        try {
            switch (choice) {
                case 1: { // Сделать юзера
                    std::cout << "Enter username: ";
                    std::cin >> username;
                    vfs.set_current_user(username);
                    std::cout << "Current user: " << username << "\n";
                    break;
                }
                case 2: { // Создать файл
                    std::string vPath, pPath;
                    std::cout << "Enter virtual path for the file (e.g., /docs/report.txt): ";
                    std::cin >> vPath;
                    std::cout << "Enter physical path to the file (e.g., C:/Users/User/Documents/report.txt): ";
                    std::cin >> pPath;
                    vfs.create_virtual_file(vPath, pPath);
                    std::cout << "File created.\n";
                    break;
                }
                case 3: { // Удалить файл
                    std::string vPath;
                    std::cout << "Enter virtual path to the file to delete: ";
                    std::cin >> vPath;
                    vfs.remove_virtual_file(vPath);
                    std::cout << "File removed from VFS.\n";
                    break;
                }
                case 4: { // Создать директорию
                    std::string vPath;
                    std::cout << "Enter virtual path for the directory (e.g., /docs): ";
                    std::cin >> vPath;
                    vfs.create_virtual_file(vPath + "/__placeholder__", ""); 
                    vfs.remove_virtual_file(vPath + "/__placeholder__");
                    std::cout << "Directory created.\n";
                    break;
                }
                case 5: { // Удалить директорию
                    std::string vPath;
                    std::cout << "Enter virtual path to the directory to delete: ";
                    std::cin >> vPath;
                    std::cout << "Directory deletion not implemented.\n";
                    break;
                }
                case 6: { // Переместить файл/директорию
                    std::string src, dest;
                    std::cout << "Enter source virtual path: ";
                    std::cin >> src;
                    std::cout << "Enter destination virtual path: ";
                    std::cin >> dest;
                    vfs.move(src, dest);
                    std::cout << "Move completed.\n";
                    break;
                }
                case 7: { // Переназвать
                    std::string path, newName;
                    std::cout << "Enter virtual path to the object: ";
                    std::cin >> path;
                    std::cout << "Enter new name: ";
                    std::cin >> newName;
                    vfs.rename(path, newName);
                    std::cout << "Rename completed.\n";
                    break;
                }
                case 8: { // Изменить уровень доступа
                    std::string groupName;
                    std::cout << "Enter group name: ";
                    std::cin >> groupName;
                    std::cout << "Set permissions (R/W/X) (e.g., RW-): ";
                    std::string permsStr;
                    std::cin >> permsStr;
                    Permissions newPerms;
                    newPerms.read = permsStr[0] == 'R' || permsStr[0] == 'r';
                    newPerms.write = permsStr[1] == 'W' || permsStr[1] == 'w';
                    newPerms.execute = permsStr[2] == 'X' || permsStr[2] == 'x';
                    pm.update_group_permissions(groupName, newPerms);
                    std::cout << "Group permissions updated.\n";
                    break;
                }
                case 9: { // Найти файл
                    std::string query;
                    std::cout << "Enter search key: ";
                    std::cin >> query;
                    ArraySequence<std::string> results = vfs.search_files(query);
                    std::cout << "Search results:\n";
                    for (int i = 0; i < results.get_length(); ++i) {
                        std::cout << "- " << results.get(i) << "\n";
                    }
                    break;
                }
                case 10: { // Показать файловую систему
                    std::cout << "File system:\n";
                    vfs.display_file_system();
                    break;
                }
                case 11: { // Выйти
                    running = false;
                    break;
                }
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }
}