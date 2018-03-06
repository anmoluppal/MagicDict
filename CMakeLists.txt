cmake_minimum_required(VERSION 3.9)
project(MagicDict)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O2")

add_library(magicDict MagicDict.cpp MagicDict.h)