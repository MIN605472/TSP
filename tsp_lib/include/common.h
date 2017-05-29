#pragma once
#include <memory>
#include <vector>

typedef unsigned int Distance;
typedef std::vector<std::vector<Distance>> Graph;
typedef std::size_t Vertex;

/// Creates a graph that is read from a file. The file must contain an adjacency
/// matrix and the distances must be positive.
/// @param file_name name of the file containing the graph
/// @return std::unique_ptr to the graph that has been read from the file
/// @throws std::invalid_argument when there is an error reading the file or the
/// graph in the file has the wrong format
std::unique_ptr<Graph> GraphFromFile(const char *file_name);
