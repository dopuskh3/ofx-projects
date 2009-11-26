//-------------------------------------------------------------------------------------
//
// \file bContourFinder.h
// \brief 
//
// \author Francois Visconte <f.visconte@gmail.com> 
// http://digitalork.blogspot.com, http://github.com/dopuskh3
//
//------------------------------------------------------------------------------------ 


#include "ofxOpenCv.h"


typedef vector<ofPoint> bHullShape;

class bContourFinder : public ofxCvContourFinder {
  
  public: 
    bContourFinder() : ofxCvContourFinder() {}; 
    
    void findConvexHulls();
    void smoothApproxChains();  

    virtual void  draw() { draw(0,0, _width, _height); };
    virtual void  draw( float x, float y ) { draw(x,y, _width, _height); };
    void reset();
    virtual void  draw( float x, float y, float w, float h ); //{ ofxCvContourFinder::draw(x, y, w, h);  }; 

  
    vector <ofxCvBlob> convexBlobs; 

};

