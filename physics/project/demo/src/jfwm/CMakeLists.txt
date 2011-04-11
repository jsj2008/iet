cmake_minimum_required(VERSION 2.6)

project(jfwm)

set(CMAKE_CXX_FLAGS "-g -Wall")

#Create Dynamx library
include_directories("../")
file(GLOB jfwm_cpp "*.cpp")
add_library(jfwm ${jfwm_cpp})
