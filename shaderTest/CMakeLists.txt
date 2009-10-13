cmake_minimum_required(VERSION 2.6)

project(pshape)

include ( ../CMakeBase.txt ) 

# add ofx includes directories for dependencies 
include_directories ( ${ofx_includes} ) 

file ( GLOB_RECURSE app_sources_files src/*)

# VectorMath addon ##############################
file ( GLOB_RECURSE ofxVectorMath ../addons/ofxVectorMath/src/* )
include_directories ( ../addons/ofxVectorMath/src/ ) 

# ofxShader addons ##############################
file ( GLOB_RECURSE ofxShader ../addons/ofxShader/* )
include_directories ( ../addons/ofxShader )

add_executable( pshape
    ${app_sources_files}
    ${ofxShader}
    ${ofxVectorMath}
    ${OFX_SOURCE_FILES} )

set ( libs ${ofx_libs} ${cv_LIBRARIES}) 
target_link_libraries(pshape ${libs} )
