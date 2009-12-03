cmake_minimum_required(VERSION 2.6)

project(ofxSimpleGuiToo_example)

include ( ../../CMakeBase.txt ) 
include ( ../../ofxAddons.txt )

# add ofx includes directories for dependencies 
include_directories ( ${ofx_includes} ) 

file ( GLOB_RECURSE app_sources_files src/*)

# VectorMath addon ##############################
file ( GLOB_RECURSE ofxVectorMath ../addons/ofxVectorMath/src/* )
include_directories ( ../addons/ofxVectorMath/src/ ) 

# ofxGui

file ( GLOB_RECURSE ofxMSAInteractiveObject ../addons/ofxMSAInteractiveObject/src/* ) 
include_directories ( ../addons/ofxMSAInteractiveObject/src/ )

file ( GLOB_RECURSE ofxSimpleGuiToo ../addons/ofxSimpleGuiToo/src/* ../addons/ofxSimpleGuiToo/src/ofxSimpleGuiToo.h ../addons/ofxSimpleGuiToo/src/Controls ) 
include_directories ( ../addons/ofxSimpleGuiToo/src/ ../addons/ofxSimpleGuiToo/src/Controls)

file ( GLOB_RECURSE ofxXmlSettings ../addons/ofxXmlSettings/libs/* ../addons/ofxXmlSettings/src/* ) 
include_directories ( ../addons/ofxXmlSettings/libs/ ../addons/ofxXmlSettings/src/ )


add_executable( ofxSimpleGuiToo_example
    ${app_sources_files}
    ${ofxVectorMath}
    ${ofxXmlSettings}
    ${ofxSimpleGuiToo}
    ${ofxXmlSettings}
    ${ofxMSAInteractiveObject}
    ${OFX_SOURCE_FILES} )

set ( libs ${ofx_libs} ${cv_LIBRARIES}) 
target_link_libraries(ofxSimpleGuiToo_example ${libs} )
