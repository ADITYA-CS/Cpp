cmake_minimum_required(VERSION 3.16)
project(Dictionary)

set(CMAKE_CXX_STANDARD 17)

add_executable(dict word.hpp trie.hpp main.cpp)