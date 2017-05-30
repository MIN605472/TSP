#!/bin/bash

ulimit -t 1200 # 20 minutes
INPUT_FILES="benchmark_input/random/*.tsp"
OPTIONS="fb av rp pd"
for OPTION in $OPTIONS; do
  for FILE in $INPUT_FILES; do
    echo -e "\033[0;32m $OPTION $FILE \033[0m"
    time build/tsp/tsp -${OPTION} $FILE > /dev/null
  done
done
