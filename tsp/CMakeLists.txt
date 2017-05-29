cmake_minimum_required(VERSION 2.8)
project(tsp)
set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} src/main.cc)
target_link_libraries(${PROJECT_NAME} PRIVATE tsp_lib)
