cmake_minimum_required(VERSION 3.16)
project(compressor)

set(CMAKE_CXX_STANDARD 14)

add_executable(compressor main.cpp Decomressor.cpp Decomressor.h Compessor.cpp Compessor.h suffix_array.cpp suffix_array.h)