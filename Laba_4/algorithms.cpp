#include "algorithms.h"
#include <fstream>

namespace GraphAlgorithms {

    void DFS(const Graph& graph, int startVertex, std::unordered_set<int>& visited) {
        visited.insert(startVertex);
        const auto& adjacencyList = graph.get_adjacencyList();
        if (adjacencyList.find(startVertex) != adjacencyList.end()) {
            for (const auto& [adjacent, weight] : adjacencyList.at(startVertex)) {
                if (visited.find(adjacent) == visited.end()) {
                    DFS(graph, adjacent, visited);
                }
            }
        }
    }

    void BFS(const Graph& graph, int startVertex, std::unordered_set<int>& visited) {
        std::queue<int> queue;
        queue.push(startVertex);
        visited.insert(startVertex);

        const auto& adjacencyList = graph.get_adjacencyList();

        while (!queue.empty()) {
            int vertex = queue.front();
            queue.pop();

            if (adjacencyList.find(vertex) != adjacencyList.end()) {
                for (const auto& [adjacent, weight] : adjacencyList.at(vertex)) {
                    if (visited.find(adjacent) == visited.end()) {
                        visited.insert(adjacent);
                        queue.push(adjacent);
                    }
                }
            }
        }
    }

    std::unordered_map<int, double> dijkstra(const Graph& graph, int startVertex) {
        std::unordered_map<int, double> distances;
        const auto& adjacencyList = graph.get_adjacencyList();

        for (const auto& [vertex, _] : adjacencyList) {
            distances[vertex] = std::numeric_limits<double>::infinity();
        }
        distances[startVertex] = 0.0;

        auto compare = [&distances](int left, int right) {
            return distances[left] > distances[right];
        };
        std::priority_queue<int, std::vector<int>, decltype(compare)> queue(compare);
        queue.push(startVertex);

        while (!queue.empty()) {
            int current = queue.top();
            queue.pop();

            if (adjacencyList.find(current) != adjacencyList.end()) {
                for (const auto& [adjacent, weight] : adjacencyList.at(current)) {
                    double newDist = distances[current] + weight;
                    if (newDist < distances[adjacent]) {
                        distances[adjacent] = newDist;
                        queue.push(adjacent);
                    }
                }
            }
        }

        return distances;
    }

    bool isSafe(int vertex, const Graph& graph, std::unordered_map<int, int>& coloring, int color) {
        const auto& adjacencyList = graph.get_adjacencyList();
        if (adjacencyList.find(vertex) != adjacencyList.end()) {
            for (const auto& [adjacent, _] : adjacencyList.at(vertex)) {
                if (coloring.find(adjacent) != coloring.end() && coloring[adjacent] == color) {
                    return false;
                }
            }
        }
        return true;
    }

    bool graph_coloringUtil(const Graph& graph, std::vector<int>& vertices, int m,
                           std::unordered_map<int, int>& coloring, int index) {
        if (index == vertices.size()) {
            return true;
        }
        int vertex = vertices[index];
        for (int color = 1; color <= m; ++color) {
            if (isSafe(vertex, graph, coloring, color)) {
                coloring[vertex] = color;
                if (graph_coloringUtil(graph, vertices, m, coloring, index + 1)) {
                    return true;
                }
                coloring.erase(vertex);
            }
        }
        return false;
    }

    bool graph_coloring(const Graph& graph, std::unordered_map<int, int>& coloring, int numColors) {
        std::vector<int> vertices;
        for (const auto& [vertex, _] : graph.get_adjacencyList()) {
            vertices.push_back(vertex);
        }
        return graph_coloringUtil(graph, vertices, numColors, coloring, 0);
    }

    void measure_algorithm_time(const Graph& graph, int startVertex,
                              void (*algorithm)(const Graph&, int, std::unordered_set<int>&),
                              double& elapsedTime) {
        auto start = std::chrono::high_resolution_clock::now();

        std::unordered_set<int> visited;
        algorithm(graph, startVertex, visited);

        auto end = std::chrono::high_resolution_clock::now();
        elapsedTime = std::chrono::duration<double, std::milli>(end - start).count();
    }

    void export_times_to_csv(const std::string& filename, const std::vector<std::pair<int, double>>& data) {
        std::ofstream file(filename);
        file << "InputSize,Time(ms)\n";
        for (const auto& [size, time] : data) {
            file << size << "," << time << "\n";
        }
        file.close();
    }

}