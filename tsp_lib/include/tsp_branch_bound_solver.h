#pragma once
#include "tsp_solver.h"

/// A TSP solver using a branch and bound algorithm
class TspBranchBoundSolver : public TspSolver {
 public:
  /// @see TspSolver::Find
  std::unique_ptr<HamiltonianPath> Find(const Graph *graph) override;

 private:
  /// Helper class. It represents a node in the search tree.
  class Node {
   public:
    /// Constructs a root node of the search tree. Calculates the reduced graph
    /// and the lower bound.
    /// @parm graph graph of which we want to find the hamiltonian path
    Node(const Graph *graph);

    /// Returns the lower bound of this node
    /// @return lower bound of this node
    Distance lower_bound() const;

    /// Returns the hamitlonian path of this node
    /// @reurn hamiltonian path of this node
    std::unique_ptr<HamiltonianPath> path() const;

    /// Returns the cost of the hamiltonian path of this node
    /// @return cost of the hamiltonian path of this node
    Distance Cost() const;

    /// Checks if the hamiltonian path of this node is a solution, if it is a
    /// valid hamiltonian path.
    /// @return true if the hamiltonian path of this node is a valid one, false
    /// oterwhise
    bool IsASolution() const;

    /// Returns the possible children of this node
    /// @return the children of this node
    std::vector<Node> Children() const;

    bool operator>(const Node &node) const;
    bool operator<(const Node &node) const;

   private:
    /// Calculates the reduced matrix
    /// @param graph to be reduced
    /// @return cantity reduced. It represent a lower bound of a hamiltonian
    /// path.
    static Distance CalculateReducedMatrix(Graph &graph);

    /// Returns the minimum value in a row inside a matrix
    /// @param graph matrix to be checked
    /// @param row row to check
    /// @return minimum value of the specifed row of the  specified matrix
    static Distance GetRowMin(const Graph &graph, Vertex row);

    /// Returns the minimum value in a column inside a matrix
    /// @param graph matrix to be checked
    /// @param col column to check
    /// @return minimum value of the specifed column of the specified matrix
    static Distance GetColumnMin(const Graph &graph, Vertex col);

    /// Reduces a row from a matrix
    /// @param graph matrix to check
    /// @param row row inside the matrix to reduce
    /// @return cantity reduced
    static Distance ReduceRow(Graph &graph, Vertex row);

    /// Reduces a column from a matrix
    /// @param graph matrix to check
    /// @param col column inside the matrix to reduce
    /// @return cantity reduced
    static Distance ReduceColumn(Graph &graph, Vertex col);

    Graph reduced_graph_;
    HamiltonianPath path_;
    Distance lower_bound_;
    const Graph *graph_;
  };

  /// Calculates an upper bound for a hamiltonian path of a graph
  /// @param graph
  /// @return upper bound for a hamiltonian path of the graph specified
  Distance CalculateUpperBound(const Graph *graph) const;
};
