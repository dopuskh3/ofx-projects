///=====================================================================================
/// \file ShapeSpectrum.h
/// \brief 
///
/// \author f.visconte, francois.visconte@milpix.com
/// \version $Id$
///
///====================================================================================

#ifndef _SHAPE_SPECTRUM_H_
#define _SHAPE_SPECTRUM_H_

#include "ofMain.h"

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
};

#endif
