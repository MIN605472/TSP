#!/bin/bash

ulimit -t 1800 # 30 minutes
INPUT_FILES=$(ls -v1 benchmark_input/random/*.tsp)
OPTIONS="fb av rp pd"
for OPTION in ${OPTIONS}; do
  for FILE in ${INPUT_FILES}; do
    echo -e "\033[0;32m${OPTION} $(echo ${FILE} | cut -f3 -d'/')\033[0m"
    build/tsp/tsp -${OPTION} ${FILE} 2>&1 | tail -n 2
  done
done
