cmake_minimum_required(VERSION 3.16)
project(compressor)

set(CMAKE_CXX_STANDARD 14)

add_executable(compressor main.cpp Decomressor.cpp Decomressor.h test.cpp Suffics_array.cpp Suffics_array.h Compessor.cpp Compessor.h Compres_abstract.cpp Compres_abstract.h)