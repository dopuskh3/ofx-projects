cmake_minimum_required(VERSION 2.6)

project(ofxFft_example)

include ( ../../CMakeBase.txt ) 

# add ofx includes directories for dependencies 
include_directories ( ${ofx_includes} ) 

file ( GLOB_RECURSE app_sources_files src/*)

# ofxFFTw 
file ( GLOB_RECURSE ofxFftw ../../addons/ofxFft/src/* )
include_directories ( ../../addons/ofxFft/src/ )

find_library(fftw_libs fftw3)
find_library(fftwf_libs fftw3f)


add_executable( ofxFft_example
    ${app_sources_files}
    ${ofxFftw}
    ${OFX_SOURCE_FILES} )

message( ${fftw_libs} )
set ( libs ${ofx_libs} ${fftwf_libs} ${fftw_libs}) 

target_link_libraries(ofxFft_example ${libs} )
