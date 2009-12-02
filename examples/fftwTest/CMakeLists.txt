cmake_minimum_required(VERSION 2.6)

project(guiExample)

include ( ../../CMakeBase.txt ) 

# add ofx includes directories for dependencies 
include_directories ( ${ofx_includes} ) 

file ( GLOB_RECURSE app_sources_files src/*)

# VectorMath addon ##############################
#file ( GLOB_RECURSE ofxVectorMath ../../addons/ofxVectorMath/src/* )
#include_directories ( ../../addons/ofxVectorMath/src/ ) 

# ofxGui
#file ( GLOB_RECURSE ofxDirList ../../addons/ofxDirList/src/* ) 
#include_directories ( ../../addons/ofxDirList/src/ )

#file ( GLOB_RECURSE ofxXmlSettings ../../addons/ofxXmlSettings/libs/* ../../addons/ofxXmlSettings/src/* ) 
#include_directories ( ../../addons/ofxXmlSettings/libs/ ../../addons/ofxXmlSettings/src/ )

#file ( GLOB_RECURSE ofxGui ../../addons/ofxGui/src/* ) 
#include_directories ( ../../addons/ofxGui/src/ )

# ofxFFTw 
file ( GLOB_RECURSE ofxFftw ../../addons/ofxFft/src/* )
include_directories ( ../../addons/ofxFft/src/ )

find_library(fftw_libs fftw3)
find_library(fftwf_libs fftw3f)


add_executable( guiExample
    ${app_sources_files}
    ${ofxFftw}
    ${OFX_SOURCE_FILES} )

message( ${fftw_libs} )
set ( libs ${ofx_libs} ${fftwf_libs} ${fftw_libs}) 
target_link_libraries(guiExample ${libs} )
