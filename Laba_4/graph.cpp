#include "graph.h"

Graph::Graph(GraphType type) : type(type) {}

void Graph::add_vertex(int vertex) {
    adjacencyList[vertex]; // Создаст запись для вершины, если её нет
}

void Graph::remove_vertex(int vertex) {
    adjacencyList.erase(vertex);
    for (auto& pair : adjacencyList) {
        pair.second.erase(vertex);
    }
}

void Graph::add_edge(int src, int dest, double weight) {
    add_vertex(src);
    add_vertex(dest);
    adjacencyList[src][dest] = weight;
    if (type == GraphType::UNDIRECTED) {
        adjacencyList[dest][src] = weight;
    }
}

void Graph::remove_edge(int src, int dest) {
    adjacencyList[src].erase(dest);
    if (type == GraphType::UNDIRECTED) {
        adjacencyList[dest].erase(src);
    }
}

void Graph::clear() {
    adjacencyList.clear();
}

const std::unordered_map<int, std::unordered_map<int, double>>& Graph::get_adjacencyList() const {
    return adjacencyList;
}

GraphType Graph::getType() const {
    return type;
}

void Graph::print() const {
    for (const auto& [vertex, edges] : adjacencyList) {
        std::cout << vertex << ": ";
        for (const auto& [adjacent, weight] : edges) {
            std::cout << "(" << adjacent << ", weight: " << weight << ") ";
        }
        std::cout << std::endl;
    }
}