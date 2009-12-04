# vim:set ft=cmake:syn on
cmake_minimum_required(VERSION 2.6)

project(openFrameworks)

include(../openFrameworks.cmake)

set (OFX_SOURCE_FILES 
    app/ofAppGlutWindow.cpp
    events/ofEvents.h
    events/ofEventUtils.h
    utils/ofConstants.h
    utils/ofUtils.h
    utils/ofMath.cpp
    utils/ofTypes.h
    utils/ofUtils.cpp
    utils/ofMath.h
    ofMain.h
    graphics/ofImage.h
    graphics/ofGraphics.cpp
    graphics/ofGraphics.h
    graphics/ofBitmapFont.cpp
    graphics/ofBitmapFont.h
    graphics/ofTrueTypeFont.h
    graphics/ofTrueTypeFont.cpp
    graphics/ofTexture.cpp
    graphics/ofImage.cpp
    graphics/ofTexture.h
    communication/ofArduino.h
    communication/ofStandardFirmata.cpp
    communication/ofSerial.cpp
    communication/ofSerial.h
    communication/ofStandardFirmata.h
    communication/ofArduino.cpp
    video/ofUCUtils.h
    video/ofVideoGrabber.h
    video/ofVideoPlayer.h
    video/ofUCUtils.cpp
    video/ofQtUtils.cpp
    video/ofVideoPlayer.cpp
    video/ofQtUtils.h
    video/ofV4LUtils.h
    video/ofVideoGrabber.cpp
    sound/ofSoundStream.h
    sound/ofSoundStream.cpp
    sound/ofSoundPlayer.cpp
    sound/ofSoundPlayer.h
    app/ofBaseApp.h
    app/ofAppRunner.h
    app/ofAppRunner.cpp
    app/ofAppBaseWindow.h
    app/ofAppGlutWindow.h )



include_directories( .
                     app
                     communication
                     events
                     graphics
                     sound
                     utils
                     video)

include_directories(${OPENFRAMEWORKS_INCLUDES})

add_library( openFrameworks ${OFX_SOURCE_FILES})

target_link_libraries(openFrameworks ${OPENFRAMEWORKS_LIBRARIES})

