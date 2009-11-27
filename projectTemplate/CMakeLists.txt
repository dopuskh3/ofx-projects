cmake_minimum_required(VERSION 2.6)

project(%%PROJECT_NAME%%)

include ( ../CMakeBase.txt ) 

# add ofx includes directories for dependencies 
include_directories ( ${ofx_includes} ) 

file ( GLOB_RECURSE app_sources_files src/*)

# VectorMath addon ##############################
file ( GLOB_RECURSE ofxVectorMath ../addons/ofxVectorMath/src/* )
include_directories ( ../addons/ofxVectorMath/src/ ) 


add_executable( %%PROJECT_NAME%%
    ${app_sources_files}
    ${ofxVectorMath}
    ${OFX_SOURCE_FILES} )

set ( libs ${ofx_libs} ${cv_LIBRARIES}) 
target_link_libraries(%%PROJECT_NAME%% ${libs} )
