#include <cstring>
#include <iostream>
#include "tsp_brute_force_solver.h"

int main(int argc, char *argv[]) {
  if (argc != 3 || (strcmp(argv[1], "-fb") && strcmp(argv[1], "-av") &&
                    strcmp(argv[1], "-pd") && strcmp(argv[1], "-rp"))) {
    std::cerr
        << "Incorrect parameters. Usage: tsp -[fb | av | pd | rp] file_name"
        << '\n';
    return -1;
  }

  try {
    auto graph = GraphFromFile(argv[2]);
    std::unique_ptr<TspSolver> solver;
    if (strcmp(argv[1], "-fb") == 0) {
      solver = std::unique_ptr<TspSolver>(new TspBruteForceSolver());
    } else if (strcmp(argv[1], "-av") == 0) {
    } else if (strcmp(argv[1], "-pd") == 0) {
    } else {
    }

    auto path = solver->Find(graph.get());
    if (path != nullptr) {
      std::cout << *path;
    } else {
      std::cerr << "The graph doesn't have a hamiltonian path\n";
    }
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
}
