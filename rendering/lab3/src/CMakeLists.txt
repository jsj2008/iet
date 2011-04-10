cmake_minimum_required(VERSION 2.8)

Project ( OpenglApp )

set(CMAKE_CXX_FLAGS "-g -Wall")

### Set include dirs
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)
find_package(DevIL REQUIRED)

SET(libThirdParty GLEW ${IL_LIBRARIES} ${ILU_LIBRARIES} ${ILUT_LIBRARIES} ${DEVIL_LIBRARY} ${GLUT_LIBRARY} ${OPENGL_LIBRARY})

#Make Libraries
FILE(GLOB openglApp_cpp "./*.cpp")
ADD_EXECUTABLE(opengl_app ${openglApp_cpp})
TARGET_LINK_LIBRARIES(opengl_app ${libThirdParty})
