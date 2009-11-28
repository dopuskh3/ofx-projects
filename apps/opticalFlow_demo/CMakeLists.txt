cmake_minimum_required(VERSION 2.6)

project(opticalFlowDemo)

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
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
    find_library(cv_LIBRARIES cv PATHS /Users/fv/Dev/openframeworks/opencv/OpenCV-2.0.0/lib)
    find_library(cvaux_LIBRARIES cvaux PATHS /Users/fv/Dev/openframeworks/opencv/OpenCV-2.0.0/lib)
    find_library(cvcore_LIBRARIES cxcore PATHS /Users/fv/Dev/openframeworks/opencv/OpenCV-2.0.0/lib)
    include_directories( /Users/fv/Dev/openframeworks/opencv/OpenCV-2.0.0/include/opencv/ )
    # include_directories( ../../ofx-dev/addons/ofxopencv/OpenCV/libs/opencv/OpenCV/include/ )
    set( cv_LIBRARIES ${cv_LIBRARIES} ${cvaux_LIBRARIES} ${cvcore_LIBRARIES})
    message ("--- ${cv_LIBRARIES}")
endif()



add_executable( opticalFlowDemo
    ${app_sources_files}
    ${ofxVectorMath}
    ${ofxOpenCv}
    ${OFX_SOURCE_FILES} )

set ( libs ${ofx_libs} ${cv_LIBRARIES}) 
target_link_libraries(opticalFlowDemo ${libs} )
