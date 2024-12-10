#include "tests.h"
#include "graph.h"
#include "algorithms.h"
#include <assert.h>
#include <iostream>

// Тесты для класса Graph
void test_graph() {
    Graph graph(GraphType::UNDIRECTED);
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2, 3.0);
    assert(graph.get_adjacencyList().at(1).at(2) == 3.0);
    assert(graph.get_adjacencyList().at(2).at(1) == 3.0);

    graph.remove_edge(1, 2);
    assert(graph.get_adjacencyList().at(1).find(2) == graph.get_adjacencyList().at(1).end());

    graph.remove_vertex(1);
    assert(graph.get_adjacencyList().find(1) == graph.get_adjacencyList().end());
    std::cout << "Тесты класса Graph пройдены.\n";
}

// Тесты для алгоритмов
void test_algorithms() {
    Graph graph(GraphType::UNDIRECTED);
    graph.add_edge(1, 2, 1.0);
    graph.add_edge(2, 3, 2.0);
    graph.add_edge(1, 3, 4.0);

    // Тест Дейкстры
    auto distances = GraphAlgorithms::dijkstra(graph, 1);
    assert(distances[3] == 3.0);

    // Тест DFS
    std::unordered_set<int> visited;
    GraphAlgorithms::DFS(graph, 1, visited);
    assert(visited.size() == 3);

    // Тест BFS
    visited.clear();
    GraphAlgorithms::BFS(graph, 1, visited);
    assert(visited.size() == 3);

    // Тест раскраски
    std::unordered_map<int, int> coloring;
    bool canColor = GraphAlgorithms::graph_coloring(graph, coloring, 2);
    assert(canColor);
    std::cout << "Тесты алгоритмов пройдены.\n";
}

void runtests() {
    test_graph();
    test_algorithms();
}