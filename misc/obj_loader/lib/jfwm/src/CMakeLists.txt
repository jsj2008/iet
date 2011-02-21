cmake_minimum_required(VERSION 2.8)

Project ( jfwm )

#set(CMAKE_CXX_FLAGS "-g -Wall")

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
ADD_LIBRARY(libjfwm ${jfwm_cpp})

FILE(GLOB jfwm_demo_cpp "./jfwm_demo/*.cpp")
ADD_EXECUTABLE(jfwm_demo ${jfwm_demo_cpp})
TARGET_LINK_LIBRARIES(jfwm_demo libjfwm ${libThirdParty})
