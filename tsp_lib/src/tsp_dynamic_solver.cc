#include "tsp_dynamic_solver.h"
#include <iostream>
#include <limits>

std::unique_ptr<HamiltonianPath> TspDynamicSolver::Find(const Graph *graph) {
  std::size_t num_of_rows = 1 << graph->size();
  g_matrix_.resize(num_of_rows, std::vector<Distance>(graph->size(), 0));
  p_matrix_.resize(num_of_rows, std::vector<Vertex>(graph->size(), 0));
  graph_ = graph;
  for (Vertex v = 0; v < graph->size(); ++v) {
    g_matrix_[0][v] = (*graph)[v][0];
  }
  std::bitset<MAX_VERTICES> set(num_of_rows - 1);
  set.reset(0);
  if (G(0, set) == std::numeric_limits<Distance>::max()) {
    return nullptr;
  } else {
    set.set(0);
    return P(0, set);
  }
}

Distance TspDynamicSolver::G(Vertex vertex, std::bitset<MAX_VERTICES> set) {
  if (set.to_ullong() == 0) {
    return g_matrix_[0][vertex];
  } else {
    if (g_matrix_[set.to_ullong()][vertex] != 0) {
      return g_matrix_[set.to_ullong()][vertex];
    } else {
      auto min = std::numeric_limits<Distance>::max();
      Vertex best_vertex = 0;
      for (Vertex v = 0; v < graph_->size(); ++v) {
        if (set[v]) {
          auto d = (*graph_)[vertex][v];
          set.reset(v);
          auto g = G(v, set);
          auto distance = d + g;
          if (d == 0 || g == 0 || g == std::numeric_limits<Distance>::max()) {
            distance = std::numeric_limits<Distance>::max();
          }
          if (distance < min) {
            min = distance;
            best_vertex = v;
          }
          set.set(v);
        }
      }
      g_matrix_[set.to_ullong()][vertex] = min;
      p_matrix_[set.to_ullong()][vertex] = best_vertex;
      return min;
    }
  }
}

std::unique_ptr<HamiltonianPath> TspDynamicSolver::P(
    Vertex vertex, std::bitset<MAX_VERTICES> set) {
  std::unique_ptr<HamiltonianPath> path(new HamiltonianPath(graph_));
  while (set.to_ullong()) {
    auto succesor = p_matrix_[set.to_ullong()][vertex];
    path->Push(succesor);
    set.reset(succesor);
    vertex = succesor;
  }
  path->Push(0);
  return path;
}
