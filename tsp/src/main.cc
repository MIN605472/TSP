#include <cstring>
#include <iostream>
#include "tsp_branch_bound_solver.h"
#include "tsp_brute_force_solver.h"
#include "tsp_dynamic_solver.h"
#include "tsp_greedy_solver.h"
#include <chrono>

int main(int argc, char *argv[]) {
  if (argc != 3 || (strcmp(argv[1], "-fb") && strcmp(argv[1], "-av") &&
                    strcmp(argv[1], "-pd") && strcmp(argv[1], "-rp"))) {
    std::cerr
        << "Incorrect parameters. Usage: tsp -[fb | av | pd | rp] file_name\n";
    return -1;
  }

  try {
    auto graph = GraphFromFile(argv[2]);
    std::unique_ptr<TspSolver> solver;
    if (strcmp(argv[1], "-fb") == 0) {
      solver.reset(new TspBruteForceSolver());
    } else if (strcmp(argv[1], "-av") == 0) {
      solver.reset(new TspGreedySolver());
    } else if (strcmp(argv[1], "-pd") == 0) {
      solver.reset(new TspDynamicSolver());
    } else {
      solver.reset(new TspBranchBoundSolver());
    }

    auto t1 = std::chrono::high_resolution_clock::now();
    auto path = solver->Find(graph.get());
    auto t2 = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    if (path != nullptr) {
      std::cout << *path << elapsed_time << " us\n";
    } else {
      std::cerr << "The graph doesn't have a hamiltonian path\n";
    }
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
}
