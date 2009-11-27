///=====================================================================================
/// \file testApp.h
/// \brief 
///
/// \author f.visconte, francois.visconte@milpix.com
/// \version $Id$
///
///====================================================================================

#ifndef _TESTAPP_H_
#define _TESTAPP_H_

#include "ofMain.h"


class testApp : public ofSimpleApp {
  
  public:
    float *fftList; 
    float *fftSmoothed; 	
    int bands;


    void setup(); 
    void update(); 
    void draw();

    void keyPressed(int key); 
    void keyReleased (int key);

    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased();
  

    ofSoundPlayer music;
};



#endif
