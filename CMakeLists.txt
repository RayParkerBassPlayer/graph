cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project("Graph")

include_directories("/usr/local/Cellar/spdlog/1.3.1/include/")

find_library(spdlog CONFIG REQUIRED)

add_executable(
  "${PROJECT_NAME}" 
  main.cpp
  graph.cpp
  node.cpp
)

add_executable(
  "${PROJECT_NAME}Tests"
  tests/main.cpp
)

