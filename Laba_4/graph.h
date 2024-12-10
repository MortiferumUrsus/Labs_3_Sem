#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <map>
#include <set>

/**
 * Перечисление для типа графа
 */
enum class GraphType {
    DIRECTED,
    UNDIRECTED
};

/**
 * Класс графа
 */
class Graph {
public:
    Graph(GraphType type = GraphType::UNDIRECTED);

    void add_vertex(int vertex);
    void remove_vertex(int vertex);
    void add_edge(int src, int dest, double weight = 1.0);
    void remove_edge(int src, int dest);
    void clear();

    const std::unordered_map<int, std::unordered_map<int, double>>& get_adjacencyList() const;
    GraphType getType() const;
    void print() const;

private:
    GraphType type;
    std::unordered_map<int, std::unordered_map<int, double>> adjacencyList;
};

#endif // GRAPH_H