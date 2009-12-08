cmake_minimum_required(VERSION 2.6)

project(fft_demo)

# include ( ../../CMakeBase.txt ) 

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

# ofxFft
file ( GLOB_RECURSE ofxFft ./../../addons/ofxFft/src/* )
include_directories ( ./../../addons/ofxFft/src )
find_library(fftw_libs fftw3)
find_library(fftwf_libs fftw3f)




# ofxShader addons ##############################
#file ( GLOB_RECURSE ofxShader ../addons/ofxShader/* )
#include_directories ( ../addons/ofxShader )

add_executable( fft_demo
    ${app_sources_files}
    ${ofxVectorMath}
    ${ofxMSAInteractiveObject}
    ${ofxXmlSettings}
    ${ofxFft}
    ${ofxSimpleGuiToo})

    # ${OFX_SOURCE_FILES} )

include(FindPkgConfig)
pkg_check_modules(OF openFrameworks)
# message("${OF_INCLUDES} ${OF_CFLAGS} asdas")
#find_library(gl OpenGL)
#find_library(oflib openFrameworks ./../../openFrameworks)
#message ("${oflib}")
#include (../../openFrameworks.cmake)
include_directories (${OF_INCLUDE_DIRS}) # ${OF_CFLAGS})
set ( libs ${OF_LIBRARIES} ${fftwf_libs} ${fftwf_libs} )#oflib} ${gl} ${cv_LIBRARIES}) # ${ofx_libs} ${cv_LIBRARIES}) 
target_link_libraries(fft_demo ${libs} )
