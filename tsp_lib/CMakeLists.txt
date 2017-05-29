cmake_minimum_required(VERSION 2.8)
project(tsp_lib)
set(CMAKE_CXX_STANDARD 11)

set(SOURCES src/hamiltonian_path.cc src/common.cc src/tsp_brute_force_solver.cc src/tsp_greedy_solver.cc src/tsp_dynamic_solver.cc src/tsp_branch_bound_solver.cc)
set(INCLUDES include/tsp_solver.h include/hamiltonian_path.h include/common.h include/tsp_brute_force_solver.h include/tsp_greedy_solver.h include/tsp_dynamic_solver.h include/tsp_branch_bound_solver.h)
add_library(${PROJECT_NAME} ${SOURCES} ${INCLUDES})
target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE src
)
