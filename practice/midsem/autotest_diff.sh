#!/bin/bash
# Autotest Difference

make

for test in difference_tests/*; do
  ./difference < $test
  if [ $? -ne 0 ]; then
    echo -e "Test $test \e[31mError\e[39m"
    exit 1
  else
    echo -e "Test $test \e[32mSuccess\e[39m"
  fi
done
