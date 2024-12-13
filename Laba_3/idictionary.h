#ifndef IDICTIONARY_H
#define IDICTIONARY_H

#include "array_sequence.h"
#include <stdexcept>
#include <string>
#include <sstream>

// Шаблонный класс IDictionary
template <typename K, typename V>
class IDictionary {
private:
    ArraySequence<std::pair<K, V>> data; // Хранилище данных

public:
    // Конструктор по умолчанию
    IDictionary() = default;

    // Деструктор
    ~IDictionary() = default;

    // Добавление элемента в словарь
    void insert(const K& key, const V& value) {
        for (int i = 0; i < data.get_length(); ++i) {
            if (data.get(i).first == key) {
                throw std::invalid_argument("Key already exists: " + to_string(key));
            }
        }
        data.append(std::make_pair(key, value));
    }

    // Удаление элемента по ключу
    void remove(const K& key) {
        for (int i = 0; i < data.get_length(); ++i) {
            if (data.get(i).first == key) {
                data.remove_at(i);
                return;
            }
        }
        throw std::invalid_argument("Key not found: " + to_string(key));
    }

    // Получение значения по ключу
    V get(const K& key) const {
        for (int i = 0; i < data.get_length(); ++i) {
            if (data.get(i).first == key) {
                return data.get(i).second;
            }
        }
        throw std::invalid_argument("Key not found: " + to_string(key));
    }

    // Проверка существования ключа
    bool contains(const K& key) const {
        for (int i = 0; i < data.get_length(); ++i) {
            if (data.get(i).first == key) {
                return true;
            }
        }
        return false;
    }

    // Обновление значения по ключу
    void update(const K& key, const V& value) {
        for (int i = 0; i < data.get_length(); ++i) {
            if (data.get(i).first == key) {
                data.set(i, std::make_pair(key, value));
                return;
            }
        }
        throw std::invalid_argument("Key not found: " + to_string(key));
    }

    // Получение всех ключей
    ArraySequence<K> keys() const {
        ArraySequence<K> key_list;
        for (int i = 0; i < data.get_length(); ++i) {
            key_list.append(data.get(i).first);
        }
        return key_list;
    }

    // Получение всех значений
    ArraySequence<V> values() const {
        ArraySequence<V> value_list;
        for (int i = 0; i < data.get_length(); ++i) {
            value_list.append(data.get(i).second);
        }
        return value_list;
    }

    // Получение размера словаря
    size_t size() const {
        return static_cast<size_t>(data.get_length());
    }

    // Очистка словаря
    void clear() {
        data.clear();
    }

private:
    // Вспомогательная функция для преобразования ключей в строку
    std::string to_string(const K& value) const {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }
};

#endif // IDICTIONARY_H