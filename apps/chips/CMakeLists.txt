cmake_minimum_required(VERSION 2.6)

project(chips)


# add ofx includes directories for dependencies 
include_directories ( ${ofx_includes} ) 

file ( GLOB_RECURSE app_sources_files src/*)

# VectorMath addon ##############################
file ( GLOB_RECURSE ofxVectorMath ../../addons/ofxVectorMath/src/* )
include_directories ( ../../addons/ofxVectorMath/src/ ) 

# OpenCv addon ##################################
file ( GLOB_RECURSE ofxOpenCv ../../addons/ofxOpenCv/src/* )
include_directories ( ../../addons/ofxOpenCv/src/ ) 

if ( CMAKE_SYSTEM_NAME MATCHES "Linux" ) 
    include(FindPkgConfig)
    pkg_search_module(cv opencv)
    include_directories ( ${cv_INCLUDE_DIRS} )
endif()

# msaPhysics
file ( GLOB_RECURSE ofxMSAPhysics ../../addons/ofxMSAPhysics/src/* )
include_directories ( ../../addons/ofxMSAPhysics/src/Callbacks ../../addons/ofxMSAPhysics/src/Constraints ../../addons/ofxMSAPhysics/src/Core ../../addons/ofxMSAPhysics/src/serialization/ ../../addons/ofxMSAPhysics/src/ ) 

# ofxObjCPointer
file ( GLOB_RECURSE ofxObjCPointer ../../addons/ofxObjCPointer/src/* ) 
include_directories ( ../../addons/ofxObjCPointer/src/ )


#################################################
# box2d
#################################################
# file ( GLOB_RECURSE b2d_sources_files ../addons/ofxBox2d-vanderline/*)
#include_directories( ../addons/ofxBox2d-vanderline/lib/Box2D/Include ../addons/ofxBox2d-vanderline/ ) 


add_executable( chips
    ${app_sources_files}
    ${ofxMSAPhysics}
    ${ofxOpenCv}
    ${ofxVectorMath}
    ${ofxObjCPointer}
    )

if ( APPLE ) 

    find_library(OF openFrameworks PATHS /usr/local/Frameworks)
    message("${OF}")
    include_directories ( "${OF}/Headers")
    set ( OF_LIBRARIES ${OF} )  
    set ( libs ${OF} ${cv_LIBRARIES} "-framework OpenGL") # ${ofx_libs} ${cv_LIBRARIES}) 

else ( APPLE ) 
    message( "Building for linux")
    message( " LIBS : ${OF_LIBRARIES} INCLUDES ${OF_INCLUDE_DIRS}" )
    include(FindPkgConfig)
    pkg_check_modules(OF openFrameworks)
    include_directories (${OF_INCLUDE_DIRS}) # ${OF_CFLAGS})
endif ( APPLE )


set ( libs ${OF_LIBRARIES} ${cv_LIBRARIES}) 
target_link_libraries(chips ${libs} )
