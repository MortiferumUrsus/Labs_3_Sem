#include "UI.h"
#include "Graph.h"
#include "Algorithms.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <unordered_set>
#include <string>

/**
 * Function to generate a random graph
 */
Graph generate_random_graph(int numVertices, int numEdges, GraphType type) {
    Graph graph(type);
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < numVertices; ++i) {
        graph.add_vertex(i);
    }
    for (int i = 0; i < numEdges; ++i) {
        int src = rand() % numVertices;
        int dest = rand() % numVertices;
        double weight = static_cast<double>(rand()) / RAND_MAX * 10.0; // Weight from 0 to 10
        graph.add_edge(src, dest, weight);
    }
    return graph;
}

/**
 * User interface function
 */
void start_ui() {
    Graph graph;
    bool running = true;
    while (running) {
        std::cout << "Choose an action:\n";
        std::cout << "1. Create a new graph\n";
        std::cout << "2. Add a vertex\n";
        std::cout << "3. Add an edge\n";
        std::cout << "4. Remove a vertex\n";
        std::cout << "5. Remove an edge\n";
        std::cout << "6. Display the graph\n";
        std::cout << "7. Execute an algorithm\n";
        std::cout << "8. Compare algorithms by time\n";
        std::cout << "9. Export data to CSV\n";
        std::cout << "0. Exit\n";
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1: {
                std::cout << "Graph type (0 - undirected, 1 - directed): ";
                int type;
                std::cin >> type;
                graph = Graph(static_cast<GraphType>(type));
                std::cout << "Graph created.\n";
                break;
            }
            case 2: {
                std::cout << "Enter vertex number: ";
                int vertex;
                std::cin >> vertex;
                graph.add_vertex(vertex);
                std::cout << "Vertex added.\n";
                break;
            }
            case 3: {
                std::cout << "Enter source vertex, destination vertex, and weight: ";
                int src, dest;
                double weight;
                std::cin >> src >> dest >> weight;
                graph.add_edge(src, dest, weight);
                std::cout << "Edge added.\n";
                break;
            }
            case 4: {
                std::cout << "Enter vertex number: ";
                int vertex;
                std::cin >> vertex;
                graph.remove_vertex(vertex);
                std::cout << "Vertex removed.\n";
                break;
            }
            case 5: {
                std::cout << "Enter source vertex and destination vertex: ";
                int src, dest;
                std::cin >> src >> dest;
                graph.remove_edge(src, dest);
                std::cout << "Edge removed.\n";
                break;
            }
            case 6: {
                graph.print();
                break;
            }
            case 7: {
                std::cout << "Choose an algorithm:\n";
                std::cout << "1. Depth-First Search (DFS)\n";
                std::cout << "2. Breadth-First Search (BFS)\n";
                std::cout << "3. Dijkstra's Algorithm\n";
                std::cout << "4. Graph Coloring\n";
                int algChoice;
                std::cin >> algChoice;
                switch (algChoice) {
                    case 1: {
                        std::cout << "Enter starting vertex: ";
                        int start;
                        std::cin >> start;
                        std::unordered_set<int> visited;
                        GraphAlgorithms::DFS(graph, start, visited);
                        std::cout << "Visited vertices: ";
                        for (int v : visited) {
                            std::cout << v << " ";
                        }
                        std::cout << std::endl;
                        break;
                    }
                    case 2: {
                        std::cout << "Enter starting vertex: ";
                        int start;
                        std::cin >> start;
                        std::unordered_set<int> visited;
                        GraphAlgorithms::BFS(graph, start, visited);
                        std::cout << "Visited vertices: ";
                        for (int v : visited) {
                            std::cout << v << " ";
                        }
                        std::cout << std::endl;
                        break;
                    }
                    case 3: {
                        std::cout << "Enter starting vertex: ";
                        int start;
                        std::cin >> start;
                        auto distances = GraphAlgorithms::dijkstra(graph, start);
                        std::cout << "Shortest paths:\n";
                        for (const auto& [vertex, distance] : distances) {
                            std::cout << "Vertex " << vertex << ": " << distance << std::endl;
                        }
                        break;
                    }
                    case 4: {
                        std::cout << "Enter number of colors: ";
                        int numColors;
                        std::cin >> numColors;
                        std::unordered_map<int, int> coloring;
                        if (GraphAlgorithms::graph_coloring(graph, coloring, numColors)) {
                            std::cout << "Coloring successfully completed:\n";
                            for (const auto& [vertex, color] : coloring) {
                                std::cout << "Vertex " << vertex << ": color " << color << std::endl;
                            }
                        } else {
                            std::cout << "Failed to color the graph with the given number of colors.\n";
                        }
                        break;
                    }
                    default:
                        std::cout << "Invalid choice.\n";
                        break;
                }
                break;
            }
            case 8: {
                std::cout << "Enter starting vertex: ";
                int start;
                std::cin >> start;
                double dfsTime = 0.0, bfsTime = 0.0;
                GraphAlgorithms::measure_algorithm_time(graph, start, GraphAlgorithms::DFS, dfsTime);
                GraphAlgorithms::measure_algorithm_time(graph, start, GraphAlgorithms::BFS, bfsTime);
                std::cout << "DFS execution time: " << dfsTime << " ms\n";
                std::cout << "BFS execution time: " << bfsTime << " ms\n";
                break;
            }
            case 9: {
                std::cout << "Enter filename for export: ";
                std::string filename;
                std::cin >> filename;
                // Data for export can be added here
                std::vector<std::pair<int, double>> data = {
                    {10, 0.5}, {20, 1.2}, {30, 2.5}
                };
                GraphAlgorithms::export_times_to_csv(filename, data);
                std::cout << "Data exported to " << filename << std::endl;
                break;
            }
            case 0:
                running = false;
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}