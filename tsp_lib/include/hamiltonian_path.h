#include <ostream>
#include "common.h"

/// This class represents a hamiltonian path
class HamiltonianPath {
 public:
  /// Creates a new empty hamiltonian path
  /// @param graph the graph that this new path is part of
  HamiltonianPath(const Graph* graph);

  /// Total cost of this path
  /// @return total cost of this path
  Distance Cost() const;

  /// Check if this path is a valid hamiltonian path
  /// @return true if this is a valid hamiltonian path, false otherwise
  bool IsASolution() const;

  /// Adds the vertex to this path
  /// @param vertex vertex to be added
  void Push(Vertex vertex);

  /// Removes the last element added to this path
  void Pop();

  /// Return the last element added to this path
  /// @return last element added to this path
  Vertex Peek() const;

  /// Checks if you can add a vertex to this path
  /// @param vertex vertex to check
  /// @return true if the vertex specifed can be added to this path, false
  /// otherwise
  bool CanIPush(Vertex vertex) const;

  friend std::ostream& operator<<(std::ostream& os, const HamiltonianPath& path);

 private:
  const Graph* graph_;
  std::vector<Vertex> path_;
};
