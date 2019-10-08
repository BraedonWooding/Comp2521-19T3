#!/bin/bash
# Autotest Polyfit

make

for test in poly_tests/*; do
  ./polyfit < $test
  if [ $? -ne 0 ]; then
    echo -e "Test $test \e[31mError\e[39m"
    exit 1
  else
    echo -e "Test $test \e[32mSuccess\e[39m"
  fi
done
