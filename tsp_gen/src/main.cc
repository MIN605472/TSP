#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "common.h"

/// Generates a random complete directed graph
/// @param num_vertices number of vertices that the graph must have
/// @param min minimum distance that should be between two vertices
/// @param max maximum distance that should be between tow vertices
/// @return random complete directed graph
Graph GenGraph(Vertex num_vertices, Distance min, Distance max) {
  Graph graph(num_vertices, std::vector<Distance>(num_vertices, 0));
  std::random_device rd;
  std::default_random_engine gen(rd());
  std::uniform_int_distribution<Distance> dis(min, max);
  for (std::size_t row = 0; row < num_vertices; ++row) {
    for (std::size_t col = row + 1; col < num_vertices; ++col) {
      auto roll = dis(gen);
      graph[row][col] = roll;
      graph[col][row] = roll;
    }
  }
  return graph;
}

/// Writes the graph specified to a file
/// @param graph graph to write
/// @param name name of the file
void WriteToFile(const Graph &graph, const std::string &name) {
  std::ofstream of(name, std::ios_base::trunc | std::ios_base::out);
  of << graph;
  of.close();
}

/// Generates random complete directed graphs that can have a hamiltonian path
/// and writes them to a file. argv[1] should be >= 3; it generates graphs that
/// have 3, 4, 5 ... argv[1] - 1, argv[1] vertices.
int main(int argc, char *argv[]) {
  auto max_num_vertices = atoi(argv[1]);
  for (Vertex i = 3; i <= max_num_vertices; ++i) {
    auto graph = GenGraph(i, 1, 100);
    auto file_name = std::to_string(graph.size()) + ".tsp";
    WriteToFile(graph, file_name);
  }
}
