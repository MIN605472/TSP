#pragma once
#include <bitset>
#include "tsp_solver.h"

#define MAX_VERTICES 64

/// A TSP solver using a dynamic programming.
class TspDynamicSolver : public TspSolver {
 public:
  /// @see TspSolver::Find
  std::unique_ptr<HamiltonianPath> Find(const Graph *graph) override;

 private:
  Distance G(Vertex vertex, std::bitset<MAX_VERTICES> set);

  std::unique_ptr<HamiltonianPath> P(Vertex vertex,
                                     std::bitset<MAX_VERTICES> set);

  // Matrix that saves the minimum distance. A column is a vertex and a row is a
  // set.
  std::vector<std::vector<Distance>> g_matrix_;

  // Matrix that saves the vertex that gaves the vertex that produces the
  // minimum distance.
  std::vector<std::vector<Vertex>> p_matrix_;

  const Graph *graph_;
};
