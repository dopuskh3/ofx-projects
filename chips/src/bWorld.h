///=====================================================================================
/// \file bWorld.h
/// \brief 
///
/// \author f.visconte, francois.visconte@milpix.com
/// \version $Id$
///
///====================================================================================

#ifndef _BWORLD_H_
#define _BWORLD_H_
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxBox2d.h"

class bWorld { 
  public:

    ofxBox2d                        box2d;
    //vector      <ofxBox2dPolygon>   polygons;
    
    ofxBox2dPolygon poly;
    bWorld(); 
    void createWorld();
    void shapeFromBlobs(vector<ofxCvBlob>  *blobs);
 

};


#endif 

