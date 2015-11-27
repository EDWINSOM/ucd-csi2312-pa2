cmake_minimum_required(VERSION 3.3)
project(pa2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Point.cpp Point.h Cluster.cpp Cluster.h KMeans.cpp KMeans.h Exceptions.cpp Exceptions.h)
add_executable(pa2 ${SOURCE_FILES})
