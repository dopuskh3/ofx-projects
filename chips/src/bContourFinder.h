///=====================================================================================
/// \file bContourFinder.h
/// \brief 
///
/// \author f.visconte, francois.visconte@milpix.com
/// \version $Id$
///
///====================================================================================

#include "ofxOpenCv.h"


typedef vector<ofPoint> bHullShape;

class bContourFinder : public ofxCvContourFinder {
  
  public: 
    bContourFinder() : ofxCvContourFinder() {}; 
    
    void findConvexHulls();
    virtual void  draw() { draw(0,0, _width, _height); };
    virtual void  draw( float x, float y ) { draw(x,y, _width, _height); };
    void reset();
    virtual void  draw( float x, float y, float w, float h ); //{ ofxCvContourFinder::draw(x, y, w, h);  }; 
  
    vector <CvSeq *> convexHulls;
    vector <bHullShape> hulls;
    vector <ofxCvBlob> convexBlobs; 

};

