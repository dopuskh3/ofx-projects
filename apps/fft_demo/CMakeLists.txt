cmake_minimum_required(VERSION 2.6)

project(fft_demo)

# include ( ../../CMakeBase.txt ) 
# add ofx includes directories for dependencies 
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

#include(FindPkgConfig)
#pkg_search_module(OF openFrameworks)
find_library(OF openFrameworks PATHS /usr/local/Frameworks)
message("${OF}")

include_directories ( ${OF_INCLUDE_DIRS} "${OF}/Headers")
set ( libs ${OF} ${cv_LIBRARIES} "-framework OpenGL") # ${ofx_libs} ${cv_LIBRARIES}) 
target_link_libraries(fft_demo ${libs} )
