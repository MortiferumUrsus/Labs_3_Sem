#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "Graph.h"
#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>
#include <chrono>
#include <unordered_set>
#include <string>

/**
 * Пространство имен для алгоритмов графа
 */
namespace GraphAlgorithms {

    void DFS(const Graph& graph, int startVertex, std::unordered_set<int>& visited);
    void BFS(const Graph& graph, int startVertex, std::unordered_set<int>& visited);
    std::unordered_map<int, double> dijkstra(const Graph& graph, int startVertex);
    bool graph_coloring(const Graph& graph, std::unordered_map<int, int>& coloring, int numColors);

    void measure_algorithm_time(const Graph& graph, int startVertex,
                              void (*algorithm)(const Graph&, int, std::unordered_set<int>&),
                              double& elapsedTime);

    void export_times_to_csv(const std::string& filename, const std::vector<std::pair<int, double>>& data);
}

#endif // ALGORITHMS_H