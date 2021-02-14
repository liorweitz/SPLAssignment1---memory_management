cmake_minimum_required(VERSION 3.17)
project(Assignment1)
include_directories(include)

set(CMAKE_CXX_STANDARD 11)

add_executable(Assignment1 src/main.cpp src/Agent.cpp src/Graph.cpp /src/Session.cpp src/Tree.cpp)