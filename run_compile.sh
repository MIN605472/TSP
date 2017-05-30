#! /bin/bash

# If I don't to this, CMake would identify an old version of GCC in that
# machine
if [ ${HOSTNAME} = "lab000" ]; then
  export CXX=$(which g++)
fi

if [ ! -d "build" ]; then
  mkdir build
fi

cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
