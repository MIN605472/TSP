cmake_minimum_required(VERSION 2.8)
project(tsp_gen)
set(CMAKE_CXX_STANDARD 11)

set(SOURCES src/main.cc)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE tsp_lib)
