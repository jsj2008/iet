cmake_minimum_required(VERSION 2.6)
project(dynamx)

set(CMAKE_CXX_FLAGS "-g -Wall")

#Create Dynamx library
include_directories("../")
file(GLOB dynamx_cpp "*.cpp")
add_library(dynamx ${dynamx_cpp})
