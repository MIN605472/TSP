#include "tsp_brute_force_solver.h"
#include <algorithm>
#include <limits>

std::unique_ptr<HamiltonianPath> TspBruteForceSolver::Find(const Graph *graph) {
  best_distance_ = std::numeric_limits<Distance>::max();
  graph_ = graph;
  path_aux_.reset(new HamiltonianPath(graph));
  path_aux_->Push(0);
  FindAux();
  return std::move(best_path_);
}

void TspBruteForceSolver::FindAux() {
  if (path_aux_->IsASolution()) {
    auto total_distance = path_aux_->Cost();
    if (total_distance < best_distance_) {
      best_path_.reset(new HamiltonianPath(*path_aux_));
      best_distance_ = total_distance;
    }
  } else {
    auto last_vertex = path_aux_->Peek();
    for (Vertex v = 0; v < graph_->size(); ++v) {
      auto distance = (*graph_)[last_vertex][v];
      if (distance != 0 && !path_aux_->CanIPush(v)) {
        path_aux_->Push(v);
        FindAux();
        path_aux_->Pop();
      }
    }
  }
}
