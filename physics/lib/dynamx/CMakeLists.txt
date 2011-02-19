cmake_minimum_required(VERSION 2.6)
project(dynamx_test_project)

#set(CMAKE_CXX_FLAGS "-g -Wall")

Find_Package ( OpenGL REQUIRED )

add_subdirectory ("src/dynamx")
add_subdirectory ("lib/UnitTest++")

include_directories("src")
include_directories("lib/UnitTest++/src")
include_directories("src/test")
set(testlibs UnitTestPP ${OPENGL_LIBRARIES} dynamx)
file(GLOB dynamx_test_cpp "src/test/*.cpp")
add_executable(dynamx_test ${dynamx_test_cpp})
target_link_libraries (dynamx_test ${testlibs})
