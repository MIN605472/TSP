#pragma once
#include "tsp_solver.h"

/// A TSP solver using a greedy algorithm, in particular the nearest neighbour
/// algorithm. This solver doesn't find the optimal path but it finds a solution
/// very fast.
class TspGreedySolver : public TspSolver {
 public:
  /// @see TspSolver::Find
  std::unique_ptr<HamiltonianPath> Find(const Graph *graph) override;
};
