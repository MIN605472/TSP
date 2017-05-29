#include "tsp_greedy_solver.h"
#include <limits>

std::unique_ptr<HamiltonianPath> TspGreedySolver::Find(const Graph *graph) {
  std::unique_ptr<HamiltonianPath> path(new HamiltonianPath(graph));
  path->Push(0);
  bool error = false;
  while (!path->IsASolution() && !error) {
    Vertex min_distance_vertex;
    auto min = std::numeric_limits<Distance>::max();
    error = true;
    for (Vertex v = 0; v < graph->size(); ++v) {
      auto last_vertex = path->Peek();
      auto distance = (*graph)[last_vertex][v];
      if (distance != 0 && distance < min && path->CanIPush(v)) {
        min_distance_vertex = v;
        min = (*graph)[path->Peek()][v];
        error = false;
      }
    }
    path->Push(min_distance_vertex);
  }

  if (error) {
    return nullptr;
  } else {
    return path;
  }
}
