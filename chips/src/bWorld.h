//-------------------------------------------------------------------------------------
//
// \file bWorld.h
// \brief 
//
// \author Francois Visconte <f.visconte@gmail.com> 
// http://digitalork.blogspot.com, http://github.com/dopuskh3
//
//------------------------------------------------------------------------------------ 



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

