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
#include "ofxVec4f.h"
#include "ofxOpenCv.h"

#define OPTFLOW_SMOOTH true
#define OPTFLOW_THRESHOLD 3.0

class optFlow {

  public:
    optFlow();
  
    void init(int w, int h, int scale);   
    void update(unsigned char *pixels);
    void draw();
  

	int getWidth(){ return width; }
	int getHeight(){ return height; }
    void getFlowAt(int x, int y, ofxVec2f &flow);
    void getNMax(vector<ofxVec4f> &points);

    ofVideoGrabber *vidGrab;
    ofxCvGrayscaleImage  previous_image;
    ofxCvGrayscaleImage  current_image; 
    ofxCvGrayscaleImage _temp;
		
	int step;
	int height; 
	int width;
    IplImage *velX; 
    IplImage *velY;
    IplImage *_tvx;
    IplImage *_tvy;
    IplImage *_pvx;
    IplImage *_pvy;

    bool optFlowSmooth;
};

#endif
