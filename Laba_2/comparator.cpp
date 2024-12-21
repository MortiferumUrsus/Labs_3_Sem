#ifndef COMPARATOR_H
#define COMPARATOR_H

#include <variant>
#include <string>

int compare_variants(const std::variant<int, float, std::string, bool>& a, 
                     const std::variant<int, float, std::string, bool>& b) {
    // Сравниваем по типу данных
    if (a.index() != b.index()) {
        return a.index() - b.index();
    }

    // Сравниваем значения
    if (std::holds_alternative<int>(a)) {
        return std::get<int>(a) - std::get<int>(b);
    }
    if (std::holds_alternative<float>(a)) {
        return (std::get<float>(a) < std::get<float>(b)) ? -1 : 1;
    }
    if (std::holds_alternative<std::string>(a)) {
        return std::get<std::string>(a).compare(std::get<std::string>(b));
    }
    if (std::holds_alternative<bool>(a)) {
        return std::get<bool>(a) - std::get<bool>(b);
    }
    return 0;
}

#endif // COMPARATOR_H
