#!/bin/bash
# Autotest Difference

make

for test in difference_tests/*; do
  ./difference < $test
  if [ $? -ne 0 ]; then
    printf "Test $test \e[31mError\e[39m\n"
    exit 1
  else
    printf "Test $test \e[32mSuccess\e[39m\n"
  fi
done
