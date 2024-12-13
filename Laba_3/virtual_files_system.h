#ifndef VIRTUAL_FILE_SYSTEM_H
#define VIRTUAL_FILE_SYSTEM_H

#include "virtual_directory.h"
#include "permissions_manager.h"
#include "index_manager.h"
#include <memory>
#include <string>
#include <vector>
#include <iostream>

class VirtualFileSystem {
private:
    std::shared_ptr<VirtualDirectory> root;
    PermissionsManager permissions_manager;
    IndexManager index_manager;
    Permissions current_user_perms;
    std::string current_user;

public:
    VirtualFileSystem() {
        root = std::make_shared<VirtualDirectory>("/", nullptr);
        current_user_perms = Permissions(); // По умолчанию без прав
        current_user = "";
    }

    // Установка текущего пользователя
    void set_current_user(const std::string& username) {
        current_user = username;
        try {
            current_user_perms = permissions_manager.get_permissions(username);
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << "\n";
            current_user_perms = Permissions(); // Без прав
        }
    }

    // Получение менеджера прав для настройки
    PermissionsManager& get_permissions_manager() {
        return permissions_manager;
    }

    // Создание виртуального файла путем привязки к существующему физическому файлу
    void create_virtual_file(const std::string& virtual_path, const std::string& physical_path) {
        std::vector<std::string> path_parts = split_path(virtual_path);
        if (path_parts.empty()) {
            throw std::invalid_argument("Invalid virtual path.");
        }

        // Навигация до родительского каталога
        std::shared_ptr<VirtualDirectory> current = root;
        for (size_t i = 0; i < path_parts.size() - 1; ++i) {
            if (!current->has_directory(path_parts[i])) {
                current->add_directory(path_parts[i]);
            }
            current = current->get_directory(path_parts[i]);
        }

        // Добавление виртуального файла
        std::string file_name = path_parts.back();
        current->add_file(file_name, physical_path);

        // Обновление индекса
        index_manager.index_file(virtual_path, file_name, physical_path);
    }

    // Создание виртуальной директории
    void create_virtual_directory(const std::string& virtual_path) {
        std::vector<std::string> path_parts = split_path(virtual_path);
        if (path_parts.empty()) {
            throw std::invalid_argument("Invalid virtual path.");
        }

        // Навигация до родительского каталога
        std::shared_ptr<VirtualDirectory> current = root;
        for (size_t i = 0; i < path_parts.size(); ++i) {
            if (!current->has_directory(path_parts[i])) {
                current->add_directory(path_parts[i]);
            }
            current = current->get_directory(path_parts[i]);
        }
    }

    // Удаление виртуального файла
    void remove_virtual_file(const std::string& virtual_path) {
        std::vector<std::string> path_parts = split_path(virtual_path);
        if (path_parts.empty()) {
            throw std::invalid_argument("Invalid virtual path.");
        }

        std::shared_ptr<VirtualDirectory> current = root;
        for (size_t i = 0; i < path_parts.size() - 1; ++i) {
            if (!current->has_directory(path_parts[i])) {
                throw std::invalid_argument("Path not found.");
            }
            current = current->get_directory(path_parts[i]);
        }

        std::string file_name = path_parts.back();
        current->remove_file(file_name);

        // Обновление индекса
        index_manager.remove_index(virtual_path, file_name);
    }

    // Удаление виртуальной директории
    void remove_virtual_directory(const std::string& virtual_path) {
        std::vector<std::string> path_parts = split_path(virtual_path);
        if (path_parts.empty()) {
            throw std::invalid_argument("Invalid virtual path.");
        }

        std::shared_ptr<VirtualDirectory> current = root;
        for (size_t i = 0; i < path_parts.size() - 1; ++i) {
            if (!current->has_directory(path_parts[i])) {
                throw std::invalid_argument("Path not found.");
            }
            current = current->get_directory(path_parts[i]);
        }

        std::string dir_name = path_parts.back();
        current->remove_directory(dir_name);

        // Внимание: не обновляется индекс. Необходимо реализовать рекурсивное удаление из индекса.
    }

    // Поиск файлов
    ArraySequence<std::string> search_files(const std::string& query) const {
        return index_manager.search(query);
    }

    // Перемещение виртуального файла или директории
    void move(const std::string& source_path, const std::string& dest_path) {
        std::vector<std::string> src_parts = split_path(source_path);
        std::vector<std::string> dest_parts = split_path(dest_path);

        if (src_parts.empty() || dest_parts.empty()) {
            throw std::invalid_argument("Invalid path.");
        }

        // Навигация до родительской директории источника
        std::shared_ptr<VirtualDirectory> src_parent = root;
        for (size_t i = 0; i < src_parts.size() - 1; ++i) {
            if (!src_parent->has_directory(src_parts[i])) {
                throw std::invalid_argument("Source path not found.");
            }
            src_parent = src_parent->get_directory(src_parts[i]);
        }

        std::string src_name = src_parts.back();

        // Определение, что перемещается (файл или директория)
        bool is_file = src_parent->has_file(src_name);
        bool is_directory = src_parent->has_directory(src_name);
        if (!is_file && !is_directory) {
            throw std::invalid_argument("Source not found: " + src_name);
        }

        // Навигация до родительской директории назначения
        std::shared_ptr<VirtualDirectory> dest_parent = root;
        for (size_t i = 0; i < dest_parts.size() - 1; ++i) {
            if (!dest_parent->has_directory(dest_parts[i])) {
                dest_parent->add_directory(dest_parts[i]);
            }
            dest_parent = dest_parent->get_directory(dest_parts[i]);
        }

        std::string dest_name = dest_parts.back();

        if (is_file) {
            std::shared_ptr<VirtualFile> file = src_parent->get_file(src_name);
            src_parent->remove_file(src_name);
            dest_parent->add_file(dest_name, file->get_physical_path());

            // Обновление индекса
            std::string old_virtual_path = source_path;
            std::string new_virtual_path = dest_path;
            index_manager.remove_index(old_virtual_path, file->get_name());
            index_manager.index_file(new_virtual_path, file->get_name(), file->get_physical_path());
        }
        else if (is_directory) {
            std::shared_ptr<VirtualDirectory> dir = src_parent->get_directory(src_name);
            src_parent->remove_directory(src_name);
            dest_parent->add_directory(dest_name);
            std::shared_ptr<VirtualDirectory> new_dir = dest_parent->get_directory(dest_name);
            // Копирование всех подкаталогов и файлов
            copy_directory(dir, new_dir, dest_path + "/" + dest_name);
        }
    }

    // Переименовать виртуальный файл или директорию
    void rename(const std::string& path, const std::string& new_name) {
        std::vector<std::string> path_parts = split_path(path);
        if (path_parts.empty()) {
            throw std::invalid_argument("Invalid path.");
        }

        std::shared_ptr<VirtualDirectory> parent_dir = root;
        for (size_t i = 0; i < path_parts.size() - 1; ++i) {
            if (!parent_dir->has_directory(path_parts[i])) {
                throw std::invalid_argument("Path not found.");
            }
            parent_dir = parent_dir->get_directory(path_parts[i]);
        }

        std::string old_name = path_parts.back();

        // Переименование файла
        if (parent_dir->has_file(old_name)) {
            std::shared_ptr<VirtualFile> file = parent_dir->get_file(old_name);
            parent_dir->remove_file(old_name);
            parent_dir->add_file(new_name, file->get_physical_path());

            // Обновление индекса
            std::string old_virtual_path = path;
            std::string new_virtual_path = get_parent_path(path) + "/" + new_name;
            index_manager.remove_index(old_virtual_path, old_name);
            index_manager.index_file(new_virtual_path, new_name, file->get_physical_path());
        }
        // Переименование директории
        else if (parent_dir->has_directory(old_name)) {
            std::shared_ptr<VirtualDirectory> dir = parent_dir->get_directory(old_name);
            parent_dir->remove_directory(old_name);
            parent_dir->add_directory(new_name);
            std::shared_ptr<VirtualDirectory> new_dir = parent_dir->get_directory(new_name);

            // Копирование содержимого
            copy_directory(dir, new_dir, get_parent_path(path) + "/" + new_name);
        }
        else {
            throw std::invalid_argument("Path not found: " + old_name);
        }
    }

    // Отображение файловой системы с учетом прав доступа
    void display_file_system() const {
        root->display(current_user_perms);
    }

private:
    // Вспомогательная функция для разделения пути на части
    std::vector<std::string> split_path(const std::string& path) const {
        std::vector<std::string> parts;
        std::stringstream ss(path);
        std::string item;
        while (std::getline(ss, item, '/')) {
            if (!item.empty()) {
                parts.push_back(item);
            }
        }
        return parts;
    }

    // Вспомогательная функция для получения родительского пути
    std::string get_parent_path(const std::string& path) const {
        std::vector<std::string> parts = split_path(path);
        if (parts.empty()) return "/";
        std::string parent_path = "";
        for (size_t i = 0; i < parts.size() - 1; ++i) {
            parent_path += "/" + parts[i];
        }
        return parent_path.empty() ? "/" : parent_path;
    }

    // Рекурсивное копирование директории
    void copy_directory(std::shared_ptr<VirtualDirectory> src, std::shared_ptr<VirtualDirectory> dest, const std::string& virtual_path) {
        // Копирование файлов
        ArraySequence<std::string> files = src->list_files();
        for (int i = 0; i < files.get_length(); ++i) {
            std::string file_name = files.get(i);
            std::shared_ptr<VirtualFile> file = src->get_file(file_name);
            dest->add_file(file_name, file->get_physical_path());
            index_manager.index_file(virtual_path + "/" + file_name, file_name, file->get_physical_path());
        }

        // Копирование поддиректорий
        ArraySequence<std::string> dirs = src->list_directories();
        for (int i = 0; i < dirs.get_length(); ++i) {
            std::string dir_name = dirs.get(i);
            dest->add_directory(dir_name);
            std::shared_ptr<VirtualDirectory> src_sub_dir = src->get_directory(dir_name);
            std::shared_ptr<VirtualDirectory> dest_sub_dir = dest->get_directory(dir_name);
            copy_directory(src_sub_dir, dest_sub_dir, virtual_path + "/" + dir_name);
        }
    }
};

#endif // VIRTUAL_FILE_SYSTEM_H