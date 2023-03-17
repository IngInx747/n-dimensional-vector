cmake_minimum_required(VERSION 3.5.0)
project(n-vector)
add_executable(n-vector main.cc vector_n.hh)
include_directories("${CMAKE_SOURCE_DIR}")