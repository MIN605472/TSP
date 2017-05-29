#pragma once
#include <vector>
#include "common.h"
#include "hamiltonian_path.h"

/// Interface that the different solvers of the TSP must implement
class TspSolver {
 public:
  /// Returns the minimum hamiltonian path. An empty path is returned in case in
  /// doesn't exist
  /// @param graph graph of which we should find the minimum hamiltonian path
  /// @return sequence of vertices that form the path
  virtual std::unique_ptr<HamiltonianPath> Find(const Graph *graph) = 0;
};
