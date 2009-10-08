///=====================================================================================
/// \file ShapeSpectrum.cpp
/// \brief i
///
/// \author f.visconte, francois.visconte@milpix.com
/// \version $Id$
///
///====================================================================================

#include "ShapeSpectrum.h"
#include "ofxVec2f.h"

//------------------------------------------------------------------------- 
void ShapeSpectrum::setup(std::string audiofile, int bands){
  mAudioFile = audiofile;
  mBands = bands; 
  mShape = NULL; 
  mMusic.loadSound(mAudioFile); 
} 
//------------------------------------------------------------------------- 
void ShapeSpectrum::play(){
  mMusic.play();
  mMusic.setVolume(1);
}

//------------------------------------------------------------------------- 
void ShapeSpectrum::setShape(vector<ofPoint> *points){
  mShape = points; 
}


//-------------------------------------------------------------------------
void ShapeSpectrum::update(){
  this->mFFTList = ofSoundGetSpectrum(mBands);
}


//-------------------------------------------------------------------------

void ShapeSpectrum::draw(){
  if ( ! mShape ) return; 
  float ratio = mBands / mShape->size(); 
  //------------------------------------------------------------------------- 
  for(int i=0; i<mShape->size()-1; i++){
    ofxVec2f p1 = mShape->at(i); 
    ofxVec2f p2 = mShape->at(i+1); 
    ofxVec2f n = p1 - p2;
    ofxVec2f p = n.getPerpendicular(); 

    //p.scale(1); 
    int index = (i * ratio); 
    std::cout<<index<<std::endl;
    n = p1 - p*30*mFFTList[index]; 
    ofLine(p1.x, p1.y, n.x, n.y);
  }

}
