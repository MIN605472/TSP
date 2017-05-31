#!/bin/bash

INPUT_FILES=$(ls -v1 benchmark_input/random/*.tsp)
OPTIONS="fb av rp pd"
NUM_SAMPLES="5"
TO="false"
for OPTION in ${OPTIONS}; do
  echo ${OPTION}
  echo "${INPUT_FILES}" | while read FILE && [ ${TO} = "false" ]; do
    echo -en "$(echo ${FILE} | cut -f3 -d'/');"
    SAMPLE=0
    while [ ${SAMPLE} -lt ${NUM_SAMPLES} -a ${TO} = "false" ]; do
      RES=$(timeout 2h bash -c "build/tsp/tsp -${OPTION} ${FILE} 2>&1 | tail -n 1")
      if [ $? -eq  124 ]; then
        TO="true"
      fi
      echo -n "${RES};"
      SAMPLE=$(expr ${SAMPLE} + 1)
    done
    echo
  done
  TO="false"
done
