
Find_Package ( SDL REQUIRED )


if ( NOT SDL_FOUND )
   message ( FATAL_ERROR "SDL not found!" )
endif ( NOT SDL_FOUND )

set(sdllibs ${SDL_LIBRARY} )

include_directories("..")
#Create common sim lib
file(GLOB common_sim_cpp "*.cpp")
add_library(common_sim ${common_sim_cpp})
target_link_libraries (common_sim ${sdllibs})
