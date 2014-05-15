project(sort C)
cmake_minimum_required(VERSION 2.8)

add_library(sort quicksort.c mergesort.c heapsort.c)

