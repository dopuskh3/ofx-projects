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
include_directories ( ../addons/ofxOpenCv/src/ )
 
if ( CMAKE_SYSTEM_NAME MATCHES "Linux" )
include(FindPkgConfig)
pkg_search_module(cv opencv)
include_directories ( ${cv_INCLUDE_DIRS} )
endif()
## mac os x
if ( CMAKE_SYSTEM_NAME MATCHES "Darwin" )
find_library(ocv, opencv/lib/osx)
include_directories( /System/Library/Frameworks/QuickTime.framework/Versions/Current/Headers/ )
include_directories( ../../ofx-dev/addons/ofxOpenCv/libs/opencv/include/ )
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
 
endif()
 
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
 
