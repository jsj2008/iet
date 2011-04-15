cmake_minimum_required(VERSION 2.8)

Project ( jfModel )

include_directories("../")
file(GLOB jfModel_cpp "*.cpp")
add_library(jfModel ${jfModel_cpp})
