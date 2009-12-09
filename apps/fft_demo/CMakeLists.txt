cmake_minimum_required(VERSION 2.6)

project(fft_demo)

# add ofx includes directories for dependencies 
file ( GLOB_RECURSE app_sources_files src/*)
# VectorMath addon ##############################
file ( GLOB_RECURSE ofxVectorMath ../../addons/ofxVectorMath/src/* )
include_directories ( ../../addons/ofxVectorMath/src/ ) 

# ofxGui
file ( GLOB_RECURSE ofxMSAInteractiveObject ../../addons/ofxMSAInteractiveObject/src/* ) 
include_directories ( ../../addons/ofxMSAInteractiveObject/src/ )

# ofx
file ( GLOB_RECURSE ofxSimpleGuiToo ../../addons/ofxSimpleGuiToo/src/* ../../addons/ofxSimpleGuiToo/src/ofxSimpleGuiToo.h ../../addons/ofxSimpleGuiToo/src/Controls ) 
include_directories ( ../../addons/ofxSimpleGuiToo/src/ ../../addons/ofxSimpleGuiToo/src/Controls)

file ( GLOB_RECURSE ofxXmlSettings ../../addons/ofxXmlSettings/libs/* ../../addons/ofxXmlSettings/src/* ) 
include_directories ( ../../addons/ofxXmlSettings/libs/ ../../addons/ofxXmlSettings/src/ )

# ofxFft
file ( GLOB_RECURSE ofxFft ./../../addons/ofxFft/src/* )
include_directories ( ./../../addons/ofxFft/src )
find_library(fftw_libs fftw3)
find_library(fftwf_libs fftw3f)


add_executable( fft_demo
    ${app_sources_files}
    ${ofxVectorMath}
    ${ofxMSAInteractiveObject}
    ${ofxXmlSettings}
    ${ofxFft}
    ${ofxSimpleGuiToo})

if ( APPLE ) 

    find_library(OF openFrameworks PATHS /usr/local/Frameworks)
    message("${OF}")
    include_directories ( "${OF}/Headers")
    set ( OF_LIBRARIES ${OF} )  
    set ( libs ${OF} ${cv_LIBRARIES} "-framework OpenGL") # ${ofx_libs} ${cv_LIBRARIES}) 

else ( APPLE ) 

    include(FindPkgConfig)
    pkg_check_modules(OF openFrameworks)
    include_directories (${OF_INCLUDE_DIRS}) # ${OF_CFLAGS})

endif ( APPLE )

set ( libs ${OF_LIBRARIES} ${fftwf_libs} ${fftwf_libs} )#oflib} ${gl} ${cv_LIBRARIES}) # ${ofx_libs} ${cv_LIBRARIES}) 
