cmake_minimum_required(VERSION 2.6)

project(specTrum)

include ( ../CMakeBase.txt ) 

# add ofx includes directories for dependencies 
include_directories ( ${ofx_includes} ) 

file ( GLOB_RECURSE app_sources_files src/*)

add_executable( specTrum ${app_sources_files} ${OFX_SOURCE_FILES} )

target_link_libraries(specTrum ${ofx_libs})                                                                                                         

