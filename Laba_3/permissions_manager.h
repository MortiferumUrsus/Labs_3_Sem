#ifndef PERMISSIONS_MANAGER_H
#define PERMISSIONS_MANAGER_H

#include <string>
#include <vector>
#include <iostream>
#include "idictionary.h"

// Структура для представления прав доступа
struct Permissions {
    bool read;
    bool write;
    bool execute;

    Permissions(bool r = false, bool w = false, bool e = false)
        : read(r), write(w), execute(e) {}

    // Ультимативные права
    static Permissions ultimate() {
        return Permissions(true, true, true);
    }

    // Вывод прав в строковом виде
    std::string to_string() const {
        std::string perms;
        perms += (read ? "R" : "-");
        perms += (write ? "W" : "-");
        perms += (execute ? "X" : "-");
        return perms;
    }
};

// Структуры пользователя и группы
struct User {
    std::string username;
    std::vector<std::string> groups;
};

struct Group {
    std::string group_name;
    Permissions permissions;
};

// Класс PermissionsManager
class PermissionsManager {
private:
    IDictionary<std::string, Group> groups;
    IDictionary<std::string, User> users;

public:
    // Конструктор по умолчанию
    PermissionsManager() = default;

    // Деструктор
    ~PermissionsManager() = default;

    // Добавление группы
    void add_group(const std::string& group_name, const Permissions& perms) {
        if (groups.contains(group_name)) {
            throw std::invalid_argument("Group already exists: " + group_name);
        }
        groups.insert(group_name, Group{ group_name, perms });
    }

    // Добавление пользователя
    void add_user(const std::string& username, const std::vector<std::string>& user_groups) {
        if (users.contains(username)) {
            throw std::invalid_argument("User already exists: " + username);
        }
        // Проверка существования групп
        for (const auto& group : user_groups) {
            if (!groups.contains(group)) {
                throw std::invalid_argument("Group does not exist: " + group);
            }
        }
        users.insert(username, User{ username, user_groups });
    }

    // Получение прав пользователя
    Permissions get_permissions(const std::string& username) const {
        if (!users.contains(username)) {
            throw std::invalid_argument("User does not exist: " + username);
        }

        User user = users.get(username);
        Permissions effective_perms;

        for (const auto& group_name : user.groups) {
            if (groups.contains(group_name)) {
                Group group = groups.get(group_name);
                effective_perms.read = effective_perms.read || group.permissions.read;
                effective_perms.write = effective_perms.write || group.permissions.write;
                effective_perms.execute = effective_perms.execute || group.permissions.execute;
            }
        }

        return effective_perms;
    }

    // Обновление прав группы
    void update_group_permissions(const std::string& group_name, const Permissions& new_perms) {
        if (!groups.contains(group_name)) {
            throw std::invalid_argument("Group does not exist: " + group_name);
        }
        groups.update(group_name, Group{ group_name, new_perms });
    }

    // Вывод всех групп
    void list_groups() const {
        ArraySequence<std::string> group_names = groups.keys();
        std::cout << "Groups:\n";
        for (int i = 0; i < group_names.get_length(); ++i) {
            std::cout << "- " << group_names.get(i) << "\n";
        }
    }

    // Вывод всех пользователей
    void list_users() const {
        ArraySequence<std::string> user_names = users.keys();
        std::cout << "Users:\n";
        for (int i = 0; i < user_names.get_length(); ++i) {
            std::cout << "- " << user_names.get(i) << "\n";
        }
    }
};

#endif // PERMISSIONS_MANAGER_H