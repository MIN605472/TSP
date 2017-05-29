#include "hamiltonian_path.h"
#include <algorithm>
#include <string>

HamiltonianPath::HamiltonianPath(const Graph* graph) : graph_(graph) {
  path_.reserve(graph->size() + 1);
}

Distance HamiltonianPath::Cost() const {
  Distance dist = 0;
  for (Vertex i = 0; i < path_.size() - 1; i++) {
    dist += (*graph_)[path_[i]][path_[i + 1]];
  }
  return dist;
}

bool HamiltonianPath::IsASolution() const { return path_.size() == graph_->size() + 1; }

void HamiltonianPath::Push(Vertex vertex) { path_.push_back(vertex); }

void HamiltonianPath::Pop() { path_.pop_back(); }

Vertex HamiltonianPath::Peek() const { return path_.back(); }

bool HamiltonianPath::CanIPush(Vertex vertex) const {
  return std::find(path_.begin(), path_.end(), vertex) != path_.end() &&
         !(vertex == 0 && path_.size() == graph_->size());
}

std::ostream& operator<<(std::ostream& os, const HamiltonianPath& path) {
  for (const auto& v : path.path_) {
    os << v << " ";
  }
  os << '\n' << path.Cost() << '\n';
  return os;
}
