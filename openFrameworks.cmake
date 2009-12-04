# - Find openFrameworks dependencies 
#
# Find openframeworks dependencies on Linux and OS X 
# This code set the following variables
# OPENFRAMEWORKS_LIBRARIES 
# OPENFRAMEWORKS_INCLUDES 

# Check the following dependencies 
cmake_minimum_required(VERSION 2.6)

set (OPENFRAMEWORKS_PREFIX "/opt/openFrameworks")

if ( DEFINED OPENFRAMEWORKS_PREFIX ) 
    MESSAGE ( "Searching libraries in ${OPENFRAMEWORKS_PREFIX}" )
    set (OPENFRAMEWORKS_LIBRARY_PREFIX "${OPENFRAMEWORKS_PREFIX}/lib")
    set (OPENFRAMEWORKS_INCLUDE_PREFIX "${OPENFRAMEWORKS_PREFIX}/include")
endif( DEFINED OPENFRAMEWORKS_PREFIX ) 

message ( "${OPENFRAMEWORKS_INCLUDE_PREFIX}")
message("${CMAKE_SYSTEM_NAME}")
#if ( CMAKE_SYSTEM_NAME MATCHES "Darwin" )
    set (CMAKE_FIND_LIBRARY_PREFIXES "" "lib")
    set (CMAKE_FIND_LIBRARY_SUFFIXES ".dylib" ".a" ".lib", ".so")
#endif ()

MACRO (find_lib_inc varname libname incfile)
    find_library(${varname}_LIBRARIES ${libname} PATHS ${OPENFRAMEWORKS_LIBRARY_PREFIX})
    find_path(${varname}_INCLUDES NAMES ${incfile} PATHS ${OPENFRAMEWORKS_INCLUDE_PREFIX}
            /usr/local/X11R6/include
            /usr/local/X11/include
            /usr/X11/include
            /sw/include
            /opt/local/include
            /usr/freeware/include   
    )
    if ( NOT ${varname}_LIBRARIES ) 
        message ( FATAL_ERROR "Cannot find ${libname} library")
    else()
        message ( STATUS "Found ${libname} library")
    endif()
    if ( NOT ${varname}_INCLUDES ) 
        message ( FATAL_ERROR "Cannot find ${incfile}" )
    else ()
        message ( STATUS "Found ${incfile}")
    endif()
ENDMACRO(find_lib_inc)
    

find_lib_inc(POCO PocoFoundation "Poco/Poco.h")
find_lib_inc(GLEE GLee GLee.h)
find_lib_inc(FMODEX fmodex fmod.h)
find_lib_inc(RTAUDIO RtAudio RtAudio.h)
find_lib_inc(FREEIMAGE FreeImage FreeImage.h)


# freetype 
include (FindFreeType)
if (NOT FREETYPE_FOUND)
    message( FATAL_ERROR "Cannot find freetype 2 library")
else()
    message( STATUS "Found Freetype2" )
endif()

if ( APPLE ) 
# find opengl framework
    FIND_PATH( GLU_INCLUDES 
            glu.h
            /System/Library/Frameworks/OpenGL.framework/Versions/A/Headers)

    if (GLU_INCLUDES)
        message(STATUS "Found GLU")
        set ( GLU_LIBRARY "-framework OpenGL")
    else()
        message(FATAL_ERROR "Cannot Find GLU")
    endif()
else()
    # find GLU
    include(FindGLU)
    if ( GLU_LIBRARY )
        message (STATUS "Found GLU")
    else ( GLU_LIBRARY )
        message ( WARNING "Cannot find GLU")
    endif (GLU_LIBRARY)
endif()
        
# find GLUT 
include(FindGLUT)
if ( GLUT_LIBRARIES )
    message ( STATUS "Found GLUT ${GLUT_LIBRARIES}")
else ( GLUT_LIBRARIES )
    message ( FATAL_ERROR  "Cannot find GLUT")
endif (GLUT_LIBRARIES)


if ( APPLE ) 
    #include(FindQuickTime)
#    FIND_PATH( QUICKTIME_INCLUDES 
#            QuickTime.h
#            /System/Library/Frameworks/QuickTime.framework/Versions/A/Headers)
#    if ( QUICKTIME_INCLUDES )
#        message ( STATUS "Found QuickTime framework")
#        set (QUICKTIME_LIBRARIES "-framework QuickTime")
#    else()
#        message (WARNING "Cannot find quicktime")
#    endif()
    
    find_library(QUICKTIME_LIBRARIES QuickTime)
    if ( QUICKTIME_LIBRARIES )
        message (STATUS "Found quicktime")
    else()
        message( FATAL_ERROR "Cannot find QuickTime")
    endif()


    ### COREAUDIO
    FIND_LIBRARY(COREAUDIO_LIBRARY CoreAudio)
    if ( COREAUDIO_LIBRARY)
        message (STATUS "Found CoreAudio library")
    else ()
        message (FATAL_ERROR "Cannot find CoreAudio")
    endif()
    ### CARBON                                                                                                                    
    FIND_LIBRARY(CARBON_LIBRARY Carbon)
    if ( CARBON_LIBRARY ) 
        message(STATUS "Found Carbon library")
    else()
        message( FATAL_ERROR "Cannot find Carbon")
    endif ()
    ### COREFOUNDATION
    FIND_LIBRARY(COREFOUNDATION_LIBRARY CoreFoundation )
    if (COREFOUNDATION_LIBRARY)
        message(STATUS "Found CoreFoundation library")
    else()
        message(FATAL_ERROR "Cannot find CoreFoundation")
    endif()

endif()



SET(OPENFRAMEWORKS_LIBRARIES
    ${POCO_LIBRARIES}
    ${RTAUDIO_LIBRARIES}
    ${FMODEX_LIBRARIES}
    ${GLEE_LIBRARIES}
    ${FREEIMAGE_LIBRARIES}
    ${FREETYPE_LIBRARIES}
    ${GLUT_LIBRARIES}
    ${GLU_LIBRARY}
    )

set(OPENFRAMEWORKS_INCLUDES
    ${FREETYPE_INCLUDE_DIRS}
    ${FREETYPE_INCLUDE_DIRS}/freetype
    ${OPENFRAMEWORKS_INCLUDE_PREFIX})

if ( APPLE ) 
    set (OPENFRAMEWORKS_LIBRARIES ${OPENFRAMEWORKS_LIBRARIES}
    ${COREAUDIO_LIBRARY}
    ${COREFOUNDATION_LIBRARY}
    ${CARBON_LIBRARY}
    ${QUICKTIME_LIBRARIES})
endif()
    

message("${OPENFRAMEWORKS_LIBRARIES}")
message("${OPENFRAMEWORKS_INCLUDES}")
