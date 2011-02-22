cmake_minimum_required(VERSION 2.6)
project(dynamx_simulations)

#Stuff for call graph
set(CMAKE_CXX_FLAGS "-g -pg -Wall")
#set(CMAKE_CXX_FLAGS "-O3")

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

#include_directories("lib/dynamx/src")
add_subdirectory ("dynamx")
add_subdirectory ("common")

#Create dynamx library.

#include_directories("sim")

Find_Package ( OpenGL REQUIRED )

include_directories(/usr/include/freetype2)

set(simlibs dynamx common_sim ${OPENGL_LIBRARIES} ftgl)

#Create executables
###Particle sim
include_directories("particle")
file(GLOB particle_sim_cpp "particle/*.cpp")
add_executable(particle_sim ${particle_sim_cpp})
target_link_libraries (particle_sim ${simlibs})

###Rigid body sim
include_directories("rigid_body_motion")
file(GLOB rigidbody_sim_cpp "rigid_body_motion/*.cpp")
add_executable(rigidbody_sim ${rigidbody_sim_cpp})
target_link_libraries (rigidbody_sim ${simlibs})

# Obj Test
include_directories("obj_test")
file(GLOB obj_test_sim_cpp "obj_test/*.cpp")
add_executable(obj_test_sim ${obj_test_sim_cpp})
target_link_libraries (obj_test_sim ${simlibs})

# Sweep and Prune
include_directories("sweep_and_prune")
file(GLOB sweep_and_prune_sim_cpp "sweep_and_prune/*.cpp")
add_executable(sweep_and_prune_sim ${sweep_and_prune_sim_cpp})
target_link_libraries (sweep_and_prune_sim ${simlibs})

# Collision Detection
include_directories("collision_detection")
file(GLOB collision_detection_sim_cpp "collision_detection/*.cpp")
add_executable(collision_detection_sim ${collision_detection_sim_cpp})
#target_link_libraries (collision_detection_sim ${simlibs})
target_link_libraries (collision_detection_sim dynamx common_sim ${OPENGL_LIBRARIES} )

# Collision Detection 2
include_directories("collision_detection_2")
file(GLOB collision_detection_2_sim_cpp "collision_detection_2/*.cpp")
add_executable(collision_detection_2_sim ${collision_detection_2_sim_cpp})
#target_link_libraries (collision_detection_2_sim ${simlibs})
target_link_libraries (collision_detection_2_sim dynamx common_sim ${OPENGL_LIBRARIES} )

# Collision Detection 3
include_directories("collision_detection_3")
file(GLOB collision_detection_3_sim_cpp "collision_detection_3/*.cpp")
add_executable(collision_detection_3_sim ${collision_detection_3_sim_cpp})
#target_link_libraries (collision_detection_3_sim ${simlibs})
target_link_libraries (collision_detection_3_sim dynamx common_sim ${OPENGL_LIBRARIES} )

# Collision Detection 4
include_directories("collision_detection_4")
file(GLOB collision_detection_4_sim_cpp "collision_detection_4/*.cpp")
add_executable(collision_detection_4_sim ${collision_detection_4_sim_cpp})
#target_link_libraries (collision_detection_4_sim ${simlibs})
target_link_libraries (collision_detection_4_sim dynamx common_sim ${OPENGL_LIBRARIES} )

include_directories("response_0")
file(GLOB response_0_sim_cpp "response_0/*.cpp")
add_executable(response_0_sim ${response_0_sim_cpp})
#target_link_libraries (response_0_sim ${simlibs})
target_link_libraries (response_0_sim dynamx common_sim ${OPENGL_LIBRARIES} )




#include_directories("rigid_body_motion_1")
#file(GLOB rigidbody_1_sim_cpp "rigid_body_motion_1/*.cpp")
#add_executable(rigidbody_1_sim ${rigidbody_1_sim_cpp})
#target_link_libraries (rigidbody_1_sim ${simlibs})
#
#include_directories("rigid_body_motion_2")
#file(GLOB rigidbody_2_sim_cpp "rigid_body_motion_2/*.cpp")
#add_executable(rigidbody_2_sim ${rigidbody_2_sim_cpp})
#target_link_libraries (rigidbody_2_sim ${simlibs})
