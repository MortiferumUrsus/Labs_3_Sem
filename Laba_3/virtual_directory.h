#ifndef VIRTUAL_DIRECTORY_H
#define VIRTUAL_DIRECTORY_H

#include "idictionary.h"
#include "virtual_file.h"
#include <string>
#include <memory>
#include <iostream>

// Предварительное объявление, чтобы избежать циклических зависимостей
class VirtualDirectory;

class VirtualDirectory : public std::enable_shared_from_this<VirtualDirectory> {
private:
    std::string name;
    std::shared_ptr<VirtualDirectory> parent;
    IDictionary<std::string, std::shared_ptr<VirtualDirectory>> subdirectories;
    IDictionary<std::string, std::shared_ptr<VirtualFile>> files;

public:
    VirtualDirectory(const std::string& dir_name, std::shared_ptr<VirtualDirectory> parent_dir)
        : name(dir_name), parent(parent_dir) {}

    std::string get_name() const { return name; }

    // Работа с подкаталогами
    void add_directory(const std::string& dir_name) {
        if (subdirectories.contains(dir_name)) {
            throw std::invalid_argument("Directory already exists: " + dir_name);
        }
        subdirectories.insert(dir_name, std::make_shared<VirtualDirectory>(dir_name, shared_from_this()));
    }

    bool has_directory(const std::string& dir_name) const {
        return subdirectories.contains(dir_name);
    }

    std::shared_ptr<VirtualDirectory> get_directory(const std::string& dir_name) const {
        if (!subdirectories.contains(dir_name)) {
            throw std::invalid_argument("Directory not found: " + dir_name);
        }
        return subdirectories.get(dir_name);
    }

    void remove_directory(const std::string& dir_name) {
        if (!subdirectories.contains(dir_name)) {
            throw std::invalid_argument("Directory not found: " + dir_name);
        }
        subdirectories.remove(dir_name);
    }

    // Работа с файлами
    void add_file(const std::string& file_name, const std::string& physical_path) {
        if (files.contains(file_name)) {
            throw std::invalid_argument("File already exists: " + file_name);
        }
        if (physical_path.empty()) {
            throw std::invalid_argument("Physical path cannot be empty for a file.");
        }
        files.insert(file_name, std::make_shared<VirtualFile>(file_name, physical_path));
    }

    void remove_file(const std::string& file_name) {
        if (!files.contains(file_name)) {
            throw std::invalid_argument("File not found: " + file_name);
        }
        files.remove(file_name);
    }

    bool has_file(const std::string& file_name) const {
        return files.contains(file_name);
    }

    std::shared_ptr<VirtualFile> get_file(const std::string& file_name) const {
        if (!files.contains(file_name)) {
            throw std::invalid_argument("File not found: " + file_name);
        }
        return files.get(file_name);
    }

    // Получение списка файлов и подкаталогов
    ArraySequence<std::string> list_files() const {
        return files.keys();
    }

    ArraySequence<std::string> list_directories() const {
        return subdirectories.keys();
    }

    std::shared_ptr<VirtualDirectory> get_parent() const {
        return parent;
    }

    // Вывод иерархии с учетом прав доступа
    void display(const Permissions& current_perms, const std::string& prefix = "") const {
        // Вывод подкаталогов
        ArraySequence<std::string> dirs = subdirectories.keys();
        for (int i = 0; i < dirs.get_length(); ++i) {
            std::cout << prefix << "[DIR] " << dirs.get(i) << "\n";
            subdirectories.get(dirs.get(i))->display(current_perms, prefix + "  ");
        }

        // Вывод файлов, доступных текущему пользователю
        ArraySequence<std::string> fls = files.keys();
        for (int i = 0; i < fls.get_length(); ++i) {
            // Проверка прав доступа (например, только если есть права чтения)
            if (current_perms.read) {
                std::cout << prefix << "[FILE] " << fls.get(i) << "\n";
            }
        }
    }
};

#endif // VIRTUAL_DIRECTORY_H