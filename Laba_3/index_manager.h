#ifndef INDEX_MANAGER_H
#define INDEX_MANAGER_H

#include "idictionary.h"
#include <string>
#include <vector>
#include <sstream>

// Индексный менеджер
class IndexManager {
private:
    IDictionary<std::string, ArraySequence<std::string>> index; // Ключ - слово, значение - пути к файлам

public:
    // Конструктор по умолчанию
    IndexManager() = default;

    // Деструктор
    ~IndexManager() = default;

    // Индексация файла
    void index_file(const std::string& virtual_path, const std::string& file_name, const std::string& physical_path) {
        // Простая индексация по имени файла
        std::vector<std::string> words = split_words(file_name);
        for (const auto& word : words) {
            if (!index.contains(word)) {
                index.insert(word, ArraySequence<std::string>());
            }
            ArraySequence<std::string> paths = index.get(word);
            paths.append(virtual_path);
            index.update(word, paths);
        }
    }

    // Удаление индексации файла
    void remove_index(const std::string& virtual_path, const std::string& file_name) {
        std::vector<std::string> words = split_words(file_name);
        for (const auto& word : words) {
            if (index.contains(word)) {
                ArraySequence<std::string> paths = index.get(word);
                // Удаление пути из списка
                ArraySequence<std::string> updated_paths;
                for (int i = 0; i < paths.get_length(); ++i) {
                    if (paths.get(i) != virtual_path) {
                        updated_paths.append(paths.get(i));
                    }
                }
                if (updated_paths.get_length() > 0) {
                    index.update(word, updated_paths);
                }
                else {
                    index.remove(word);
                }
            }
        }
    }

    // Поиск файлов по запросу
    ArraySequence<std::string> search(const std::string& query) const {
        if (index.contains(query)) {
            return index.get(query);
        }
        return ArraySequence<std::string>(); // Пустой результат
    }

private:
    // Вспомогательная функция для разбиения строки на слова
    std::vector<std::string> split_words(const std::string& text) const {
        std::vector<std::string> words;
        std::stringstream ss(text);
        std::string word;
        while (ss >> word) {
            words.push_back(word);
        }
        return words;
    }
};

#endif // INDEX_MANAGER_H