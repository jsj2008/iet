cmake_minimum_required(VERSION 2.8)

Project ( jfModelDemo )

#set(CMAKE_CXX_FLAGS "-g -Wall")

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

SET(libThirdParty ${SDL_LIBRARY} ${OPENGL_LIBRARY} ${GLEW_LIBRARY})

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

#FILE(GLOB jfModel_demo_cpp "./src/jfModel_demo/*.cpp")
ADD_EXECUTABLE(jfModel_demo ${jfModel_demo_cpp})
TARGET_LINK_LIBRARIES(jfModel_demo jfModel jfWm ${libThirdParty})
#TARGET_LINK_LIBRARIES(jfModel_demo jfWm ${libThirdParty})

#FILE(GLOB jfRenderingLab3_demo_cpp "./src/jfRenderingLab3_demo/*.cpp")

### This is for lab3 only!!!
find_package(DevIL REQUIRED)
find_package(GLUT REQUIRED)

FILE(GLOB jfRenderingLab3_demo_cpp "./jfRenderingLab3_demo/*.cpp")
ADD_EXECUTABLE(jfRenderingLab3_demo ${jfRenderingLab3_demo_cpp})
TARGET_LINK_LIBRARIES(jfRenderingLab3_demo glut jfModel ${libThirdParty} ${IL_LIBRARIES} ${ILU_LIBRARIES} ${ILUT_LIBRARIES} ${DEVIL_LIBRARY} ${GLUT_LIBRARY})
