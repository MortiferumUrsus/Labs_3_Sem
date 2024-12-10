#include <algorithm>
#include <vector>
#include "../isorter.h"

// Пример использования стандартной сортировки
template<typename T>
void standard_sort(Sequence<T>* seq, int (*cmp)(const T&, const T&)) {
    // Клонируем оригинальную последовательность
    Sequence<T>* sorted_seq = seq->clone();
    
    // Преобразуем Sequence в стандартный вектор
    std::vector<T> v;
    for (int i = 0; i < sorted_seq->get_length(); ++i) {
        v.push_back(sorted_seq->get(i));
    }

    // Сортировка с помощью стандартной библиотеки
    std::sort(v.begin(), v.end(), cmp);

    return sorted_seq;
}