#include "common.h"
#include <fstream>
#include <iterator>
#include <sstream>

/// Parses a string that contains natural numers separated by spaces
/// @param line string to be parsed
/// @return vector with the natural numbers that the string contained
std::vector<Distance> ParseLine(std::string line) {
  std::vector<Distance> row;
  std::stringstream ss(line);
  Distance distance;
  while (ss >> distance) {
    row.push_back(distance);
  }
  return row;
}

// TODO: change the type of the exceptions
std::unique_ptr<Graph> GraphFromFile(const char *file_name) {
  std::unique_ptr<Graph> graph(new Graph());
  std::ifstream graph_file;
  graph_file.open(file_name);
  if (!graph_file.is_open()) {
    throw std::invalid_argument("Error while opening file");
  }
  std::string line;
  std::vector<Distance> matrix_row;
  while (std::getline(graph_file, line)) {
    matrix_row = ParseLine(line);
    if (matrix_row.size() == 0 ||
        (graph->size() > 0 && matrix_row.size() != (*graph)[0].size())) {
      throw std::invalid_argument("Matrix format error");
    }
    graph->push_back(std::move(matrix_row));
  }
  if (graph->size() == 1 && (*graph)[0].size() != 1) {
    throw std::invalid_argument("Matrix format error");
  }
  if (graph_file.bad()) {
    throw std::invalid_argument("Error while reading file");
  }
  graph_file.close();
  return graph;
}

std::ostream &operator<<(std::ostream &os, const Graph &graph) {
  std::ostream_iterator<Distance> oi(os, " ");
  for (const auto &v : graph) {
    std::copy(v.begin(), v.end(), oi);
    os << '\n';
  }
  return os;
}
