#!/bin/bash

mkdir tmp
for i in {1..9}; do
    mkdir "tmp/a$i"
    for j in {1..99}; do
        mkdir "tmp/a$i/b$j"
        for k in {1..49}; do
            touch "tmp/a$i/b$j/$k.tmp"
        done
    done
done
