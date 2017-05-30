#include "tsp_branch_bound_solver.h"
#include <functional>
#include <limits>
#include <queue>
#include "tsp_greedy_solver.h"

std::unique_ptr<HamiltonianPath> TspBranchBoundSolver::Find(
    const Graph *graph) {
  std::unique_ptr<HamiltonianPath> solution;
  Distance upper_bound = CalculateUpperBound(graph);
  std::priority_queue<Node, std::vector<Node>, std::greater<Node>> alive;
  Node root_node(graph);
  alive.push(root_node);
  bool better_solutions = true;
  while (better_solutions) {
    auto children = alive.top().Children();
    alive.pop();
    for (const auto &node : children) {
      if (node.lower_bound() < upper_bound) {
        alive.push(node);
        auto cost = node.Cost();
        if (node.IsASolution() && cost < upper_bound) {
          solution = node.path();
          upper_bound = cost;
        }
      }
    }
    better_solutions =
        !alive.empty() && alive.top().lower_bound() < upper_bound;
  }
  return solution;
}

Distance TspBranchBoundSolver::CalculateUpperBound(const Graph *graph) const {
  TspGreedySolver greedy;
  auto path = greedy.Find(graph);
  if (path != nullptr) {
    return path->Cost() + 1;
  } else {
    return std::numeric_limits<Distance>::max();
  }
}

TspBranchBoundSolver::Node::Node(const Graph *graph)
    : path_(graph), graph_(graph), reduced_graph_(*graph) {
  path_.Push(0);
  for (Vertex i = 0; i < reduced_graph_.size(); i++) {
    reduced_graph_[i][i] = std::numeric_limits<Distance>::max();
  }
  lower_bound_ = CalculateReducedMatrix(reduced_graph_);
}

bool TspBranchBoundSolver::Node::operator>(const Node &node) const {
  return lower_bound_ > node.lower_bound_;
}

bool TspBranchBoundSolver::Node::operator<(const Node &node) const {
  return lower_bound_ < node.lower_bound_;
}

Distance TspBranchBoundSolver::Node::lower_bound() const {
  return lower_bound_;
}

bool TspBranchBoundSolver::Node::IsASolution() const {
  return path_.IsASolution();
}

std::vector<TspBranchBoundSolver::Node> TspBranchBoundSolver::Node::Children()
    const {
  std::vector<Node> children;
  children.reserve(graph_->size());
  for (Vertex v = 0; v < graph_->size(); ++v) {
    auto distance = (*graph_)[path_.Peek()][v];
    if (distance != 0 && path_.CanIPush(v)) {
      Node node = *this;
      node.path_.Push(v);
      for (Vertex i = 0; i < node.reduced_graph_.size(); ++i) {
        node.reduced_graph_[path_.Peek()][i] =
            std::numeric_limits<Distance>::max();
        node.reduced_graph_[i][v] = std::numeric_limits<Distance>::max();
      }
      node.reduced_graph_[v][0] = std::numeric_limits<Distance>::max();
      auto cantity_reduced = CalculateReducedMatrix(node.reduced_graph_);
      node.lower_bound_ += reduced_graph_[path_.Peek()][v] + cantity_reduced;
      children.push_back(node);
    }
  }
  return children;
}

Distance TspBranchBoundSolver::Node::CalculateReducedMatrix(Graph &graph) {
  Distance cantity_reduced = 0;
  for (Vertex row = 0; row < graph.size(); row++) {
    cantity_reduced += ReduceRow(graph, row);
  }
  for (Vertex col = 0; col < graph.size(); col++) {
    cantity_reduced += ReduceColumn(graph, col);
  }
  return cantity_reduced;
}

Distance TspBranchBoundSolver::Node::ReduceRow(Graph &graph, Vertex row) {
  auto row_min = GetRowMin(graph, row);
  if (row_min != std::numeric_limits<Distance>::max()) {
    for (Vertex col = 0; col < graph.size(); col++) {
      if (graph[row][col] != std::numeric_limits<Distance>::max()) {
        graph[row][col] -= row_min;
      }
    }
    return row_min;
  } else {
    return 0;
  }
}

Distance TspBranchBoundSolver::Node::ReduceColumn(Graph &graph, Vertex col) {
  auto col_min = GetColumnMin(graph, col);
  if (col_min != std::numeric_limits<Distance>::max()) {
    for (Vertex row = 0; row < graph.size(); row++) {
      if (graph[row][col] != std::numeric_limits<Distance>::max()) {
        graph[row][col] -= col_min;
      }
    }
    return col_min;
  } else {
    return 0;
  }
}

Distance TspBranchBoundSolver::Node::GetRowMin(const Graph &graph, Vertex row) {
  Distance min = graph[row][0];
  for (Vertex col = 1; col < graph.size() && min != 0; ++col) {
    min = std::min<Distance>(graph[row][col], min);
  }
  return min;
}

Distance TspBranchBoundSolver::Node::GetColumnMin(const Graph &graph,
                                                  Vertex col) {
  Distance min = graph[0][col];
  for (Vertex row = 1; row < graph.size() && min != 0; ++row) {
    min = std::min<Distance>(graph[row][col], min);
  }
  return min;
}

std::unique_ptr<HamiltonianPath> TspBranchBoundSolver::Node::path() const {
  return std::unique_ptr<HamiltonianPath>(new HamiltonianPath(path_));
}

Distance TspBranchBoundSolver::Node::Cost() const { return path_.Cost(); }
