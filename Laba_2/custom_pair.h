#ifndef CUSTOM_PAIR_H
#define CUSTOM_PAIR_H

#include <string>

class CustomPair {
private:
    int first;
    std::string second;

public:
    // Конструкторы
    CustomPair() : first(0), second("") {}
    CustomPair(int first, const std::string& second) : first(first), second(second) {}

    // Методы доступа
    int get_first() const {
        return first;
    }

    void set_first(int value) {
        first = value;
    }

    const std::string& get_second() const {
        return second;
    }

    void set_second(const std::string& value) {
        second = value;
    }

    // Операторы сравнения для сортировки
    bool operator==(const CustomPair& other) const {
        return first == other.first && second == other.second;
    }

    bool operator<(const CustomPair& other) const {
        return first < other.first || (first == other.first && second < other.second);
    }

    bool operator>(const CustomPair& other) const {
        return first > other.first || (first == other.first && second > other.second);
    }
};

#endif // CUSTOM_PAIR_H
