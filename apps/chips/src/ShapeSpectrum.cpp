//-------------------------------------------------------------------------------------
//
// \file ShapeSpectrum.cpp
// \brief 
//
// \author Francois Visconte <f.visconte@gmail.com>
// http://digitalork.blogspot.com, http://github.com/dopuskh3
//
//------------------------------------------------------------------------------------ 




#include "ShapeSpectrum.h"

#include "ofxVec2f.h"

//------------------------------------------------------------------------- 
void ShapeSpectrum::setup(std::string audiofile, int bands){
  mAudioFile = audiofile;
  mBands = bands; 
  mShape = NULL; 
  mMusic.loadSound(mAudioFile); 



  physics.verbose = true;         // dump activity to log
  physics.setGravity(0, GRAVITY, 0);
 
  //          // set world dimensions, not essential, but speeds up collision
  physics.setWorldSize(ofPoint(0, 0), ofPoint(ofGetWidth(), ofGetHeight())); 
  physics.setDrag(0.97f);
  //

  physics.clear();
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

static void averageNormalVector(vector<ofPoint> *pts, ofxVec2f &normalVec, int at, int width){
  int w=width; 

  w = (w%2==0)?w-1:w;
    
  int startIndex = (at-w/2<0)?0:at-w/2; 
  int stopIndex = (at+w/2>pts->size())?pts->size():at+w/2; 
  std::cout<<"start="<<startIndex<<" stop="<<stopIndex<<" size="<<pts->size()<<std::endl;
  ofxVec2f sum; 
  for (int i = startIndex; i < stopIndex-1; i++){
    sum+=pts->at(i);
    sum-=pts->at(i+1);
  }
  sum /= width; 
  normalVec = sum.getPerpendicular().scale(1);
   
}
//-------------------------------------------------------------------------

void ShapeSpectrum::draw(){
  if ( ! mShape ) return; 
  float ratio = mBands / (float ) mShape->size(); 
  std::cout<<ratio<<std::endl;
  //------------------------------------------------------------------------- 
  //
  ofBeginShape();
  for(int i=0; i<mShape->size()-1; i++){
    ofxVec2f p; 
    ofxVec2f n; 
    ofxVec2f p1 = mShape->at(i); 

    averageNormalVector(mShape, p, i, 3); 
    //ofxVec2f p1 = mShape->at(i); 
    //ofxVec2f p2 = mShape->at(i+1); 
    //ofxVec2f n = p1 - p2;
    //ofxVec2f p = n.getPerpendicular(); 

    //p.scale(1); 
    int index = floor((float)i * ratio); 
    //std::cout<<index<<std::endl;
    n = p1 - p*70*mFFTList[index]; 
    ofLine(p1.x, p1.y, n.x, n.y);
    ofLine(0, index, 30*sqrt(mFFTList[index]), index);
    ofVertex(p1.x, p1.y); 
    ofVertex( n.x, n.y); 
  }
  ofEndShape();
}


