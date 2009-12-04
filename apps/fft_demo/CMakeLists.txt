cmake_minimum_required(VERSION 2.6)

project(fft_demo)

# include ( ../../CMakeBase.txt ) 

set ( ofx_base /home/fv/Dev/openFrameworks/ofx-projects/openFrameworks ) 
set ( ofx_includes  ${ofx_base}
            ${ofx_base}/app
            ${ofx_base}/communication
            ${ofx_base}/events
            ${ofx_base}/graphics
            ${ofx_base}/sound
            ${ofx_base}/utils
            ${ofx_base}/video)


# add ofx includes directories for dependencies 
include_directories ( ${ofx_includes} ) 

file ( GLOB_RECURSE app_sources_files src/*)

# VectorMath addon ##############################
file ( GLOB_RECURSE ofxVectorMath ../../addons/ofxVectorMath/src/* )
include_directories ( ../../addons/ofxVectorMath/src/ ) 


# ofxGui

file ( GLOB_RECURSE ofxMSAInteractiveObject ../../addons/ofxMSAInteractiveObject/src/* ) 
include_directories ( ../../addons/ofxMSAInteractiveObject/src/ )

file ( GLOB_RECURSE ofxSimpleGuiToo ../../addons/ofxSimpleGuiToo/src/* ../../addons/ofxSimpleGuiToo/src/ofxSimpleGuiToo.h ../../addons/ofxSimpleGuiToo/src/Controls ) 
include_directories ( ../../addons/ofxSimpleGuiToo/src/ ../../addons/ofxSimpleGuiToo/src/Controls)

file ( GLOB_RECURSE ofxXmlSettings ../../addons/ofxXmlSettings/libs/* ../../addons/ofxXmlSettings/src/* ) 
include_directories ( ../../addons/ofxXmlSettings/libs/ ../../addons/ofxXmlSettings/src/ )



# ofxShader addons ##############################
#file ( GLOB_RECURSE ofxShader ../addons/ofxShader/* )
#include_directories ( ../addons/ofxShader )

add_executable( fft_demo
    ${app_sources_files}
    ${ofxVectorMath}
    ${ofxMSAInteractiveObject}
    ${ofxXmlSettings}
    ${ofxSimpleGuiToo})

    # ${OFX_SOURCE_FILES} )
find_library(oflib openFrameworks ./../../openFrameworks)
message ("${oflib}")
include (../../openFrameworks.cmake)
include_directories ( ${OPENFRAMEWORKS_INCLUDES} )
set ( libs ${oflib} ${cv_LIBRARIES}) # ${ofx_libs} ${cv_LIBRARIES}) 
target_link_libraries(fft_demo ${libs} )
