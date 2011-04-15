cmake_minimum_required(VERSION 2.8)

Project ( jfModelDemo )

#set(CMAKE_CXX_FLAGS "-g -Wall")
set(CMAKE_CXX_FLAGS "-O3")

#add_subdirectory ("src/jfwm")
#add_subdirectory ("src/jfModel")

#include_directories("lib/jfwm/src")
#include_directories("src")

### Set include dirs
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# Since FindGLEE.cmake is not in cmake yet.
# From : http://code.google.com/p/nvidia-texture-tools/source/browse/trunk/cmake/FindGLEW.cmake?r=96
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/glew" ${CMAKE_MODULE_PATH})

find_package( SDL REQUIRED )
find_package( OpenGL REQUIRED )
find_package( GLEW REQUIRED )

include_directories(/usr/include/freetype2)

SET(libThirdParty ${SDL_LIBRARY} ${OPENGL_LIBRARY} ${GLEW_LIBRARY} ftgl)

FILE(GLOB jfwm_cpp "./jfwm/*.cpp")
FILE(GLOB jfModel_cpp "./jfModel/*.cpp")
FILE(GLOB jfAlgebra_cpp "./jfAlgebra/*.cpp")
FILE(GLOB jfwm_demo_cpp "./jfwm_demo/*.cpp")
FILE(GLOB jfModel_demo_cpp "./jfModel_demo/*.cpp")

ADD_LIBRARY(jfAlgebra ${jfAlgebra_cpp})
ADD_LIBRARY(jfWm ${jfwm_cpp})
ADD_LIBRARY(jfModel ${jfModel_cpp} ${jfAlgebra_cpp} )

ADD_EXECUTABLE(jfwm_demo ${jfwm_demo_cpp})
TARGET_LINK_LIBRARIES(jfwm_demo jfWm ${libThirdParty})

ADD_EXECUTABLE(jfPoint_demo ${jfPoint_demo_cpp})
TARGET_LINK_LIBRARIES(jfPoint_demo jfWm ${libThirdParty})
