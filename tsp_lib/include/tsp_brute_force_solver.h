#pragma once
#include <vector>
#include "tsp_solver.h"

/// A TSP solver using brute force
class TspBruteForceSolver : public TspSolver {
 public:
  /// @see TspSolver::Find
  std::unique_ptr<HamiltonianPath> Find(const Graph *graph) override;

 private:
  /// Helper method used for recursively travelling the graph search for
  /// solutions
  void FindAux();

  // Best hamiltonian path found so far
  std::unique_ptr<HamiltonianPath> best_path_;

  // Cost of the best hamiltonian path found so far
  Distance best_distance_;

  const Graph *graph_;
  std::unique_ptr<HamiltonianPath> path_aux_;
};
