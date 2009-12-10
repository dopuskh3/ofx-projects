cmake_minimum_required(VERSION 2.6)

project(skin)

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

# opencv 
# OpenCv addon ##################################
if ( APPLE )

else ( APPLE )
    file ( GLOB_RECURSE ofxOpenCv ../../addons/ofxOpenCv/src/* )
    include_directories ( ../../addons/ofxOpenCv/src/ ) 
endif ( APPLE )

if ( CMAKE_SYSTEM_NAME MATCHES "Linux" ) 
    include(FindPkgConfig)
    pkg_search_module(CV opencv)
    include_directories ( ${CV_INCLUDE_DIRS} )
endif()


add_executable( skin
    ${app_sources_files}
    ${ofxVectorMath}
    ${ofxOpenCv}
    ${ofxMSAInteractiveObject}
    ${ofxXmlSettings}
    ${ofxSimpleGuiToo})

if ( APPLE ) 
    find_library(OF openFrameworks PATHS /usr/local/Frameworks)
    message("${OF}")
    include_directories ( "${OF}/Headers")
    set ( OF_LIBRARIES ${OF} )  
    set ( libs ${OF} "-framework OpenGL") # ${ofx_libs} ${cv_LIBRARIES}) 
else ( APPLE ) 
    message( "Building for linux")
    message( " LIBS : ${OF_LIBRARIES} INCLUDES ${OF_INCLUDE_DIRS}" )
    include(FindPkgConfig)
    pkg_check_modules(OF openFrameworks)
    include_directories (${OF_INCLUDE_DIRS}) # ${OF_CFLAGS})
endif ( APPLE )

set ( libs ${OF_LIBRARIES} ${CV_LIBRARIES} )
target_link_libraries(skin ${libs})
