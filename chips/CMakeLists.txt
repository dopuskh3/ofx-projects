cmake_minimum_required(VERSION 2.6)

project(chips)

include ( ../CMakeBase.txt ) 

# add ofx includes directories for dependencies 
include_directories ( ${ofx_includes} ) 

file ( GLOB_RECURSE app_sources_files src/*)

# VectorMath addon ##############################
file ( GLOB_RECURSE ofxVectorMath ../addons/ofxVectorMath/src/* )
include_directories ( ../addons/ofxVectorMath/src/ ) 

# OpenCv addon ##################################
file ( GLOB_RECURSE ofxOpenCv ../addons/ofxOpenCv/src/* )
include(FindPkgConfig)
pkg_search_module(cv opencv)
include_directories ( ../addons/ofxOpenCv/src/ ) 
include_directories ( ${cv_INCLUDE_DIRS} )
#################################################
# box2d
#################################################
file ( GLOB_RECURSE b2d_sources_files ../addons/ofxBox2d-vanderline/*)
include_directories( ../addons/ofxBox2d-vanderline/lib/Box2D/Include ../addons/ofxBox2d-vanderline/ ) 


add_executable( chips
    ${app_sources_files}
    ${b2d_sources_files}
    ${ofxOpenCv}
    ${ofxVectorMath}
    ${OFX_SOURCE_FILES} )

set ( libs ${ofx_libs} ${cv_LIBRARIES}) 
target_link_libraries(chips ${libs} )
