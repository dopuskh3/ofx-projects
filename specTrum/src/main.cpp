///=====================================================================================
/// \file main.cpp
/// \brief e
///
/// \author f.visconte, francois.visconte@milpix.com
/// \version $Id$
///
///====================================================================================


#include "ofMain.h"
#include "testApp.h"
        
        
//========================================================================
int main( ){

  ofSetupOpenGL(800, 600, OF_WINDOW);         // <-------- setup

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:

    ofRunApp(new testApp());

}   

