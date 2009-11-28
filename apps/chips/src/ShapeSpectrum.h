//-------------------------------------------------------------------------------------
//
// \file ShapeSpectrum.h
// \brief 
//
// \author Francois Visconte <f.visconte@gmail.com> 
// http://digitalork.blogspot.com, http://github.com/dopuskh3
//
//------------------------------------------------------------------------------------ 



#ifndef _SHAPE_SPECTRUM_H_
#define _SHAPE_SPECTRUM_H_

#include "ofMain.h"
#include "ofxMSAPhysics.h"

#define GRAVITY -1

class ShapeSpectrum {


  
  public:
    ShapeSpectrum(){}; 

    void setup(std::string audiofile, int bands);
    void setShape(vector<ofPoint> *points); 
    void play();
    void update(); 
    void draw();
  
    std::string mAudioFile; 
    vector <ofPoint> *mShape; 
    ofSoundPlayer mMusic; 
    float *mFFTList; 
    int mBands;
    ofxMSAPhysics       physics;
};

#endif
