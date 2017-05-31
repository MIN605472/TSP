#! /bin/bash

export CXX=$(which g++)

if [ ! -d "build" ]; then
  mkdir build
fi

if [ ! -d "benchmark_input" ]; then
  mkdir benchmark_input
fi

cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
cd ../benchmark_input
../build/tsp_gen/tsp_gen 50
