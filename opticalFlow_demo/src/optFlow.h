//-------------------------------------------------------------------------------------
//
// \file optFlow.h
// \brief 
//
// \author Francois Visconte <f.visconte@gmail.com> 
// http://digitalork.blogspot.com, http://github.com/dopuskh3
//
//------------------------------------------------------------------------------------ 


#ifndef _OPTFLOW_H_
#define _OPTFLOW_H_

#include "ofMain.h"
#include "ofxVec2f.h"
#include "ofxOpenCv.h"

class optFlow {

  public:
    optFlow();
  
    void init(ofVideoGrabber *vidGrabber, float scale);   
    void update();
    void draw();
  

    int getWidth(){ return this->vidGrab->getWidth(); }
    int getHeight(){ return this->vidGrab->getHeight(); }
    void getFlowAt(int x, int y, ofxVec2f &flow);

    float scale;
    ofVideoGrabber *vidGrab;
    ofxCvGrayscaleImage  previous_image;
    ofxCvGrayscaleImage  current_image; 
    ofxCvGrayscaleImage _temp;
  
    IplImage *velX; 
    IplImage *velY;
};

#endif
