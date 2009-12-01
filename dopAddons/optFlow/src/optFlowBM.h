//-------------------------------------------------------------------------------------
//
// \file optFlow.h
// \brief 
//
// \author Francois Visconte <f.visconte@gmail.com> 
// http://digitalork.blogspot.com, http://github.com/dopuskh3
//
//------------------------------------------------------------------------------------ 


#ifndef _OPTFLOWBM_H_
#define _OPTFLOWBM_H_

#include "ofMain.h"
#include "ofxVec2f.h"
#include "ofxVec4f.h"
#include "ofxOpenCv.h"

#define OPTFLOW_SMOOTH true
#define OPTFLOW_THRESHOLD 3.0

// optical flow BM parameters 
// see: 
// http://opencv.willowgarage.com/documentation/motion_analysis_and_object_tracking.html?highlight=opticalflowbm#cvCalcOpticalFlowBM
//
// note those parameters highly depends on camera framerate
//
#define OPTFLOW_SHIFT_SIZE 1
#define OPTFLOW_RANGE 10

class optFlowBM {

  public:
    optFlowBM();
  
    void init(int w, int h, int scale);   
    void setup(int b_size, int s_size, int max_rge);
    void update(unsigned char *pixels);
  

	int getWidth();
	int getHeight();
    void getFlowAt(int x, int y, ofxVec2f &flow);
    void getNMax(vector<ofxVec4f> &points);

    void drawImage(); 
    void drawFlow();

    ofVideoGrabber *vidGrab;
    ofxCvGrayscaleImage  previous_image;
    ofxCvGrayscaleImage  current_image; 
    ofxCvGrayscaleImage _temp;
		
	int step;
	int height; 
	int width;
    IplImage *velX; 
    IplImage *velY;
    
    CvSize block_size;
    CvSize shift_size;
    CvSize max_range;

    IplImage *_tvx;
    IplImage *_tvy;

};

#endif
