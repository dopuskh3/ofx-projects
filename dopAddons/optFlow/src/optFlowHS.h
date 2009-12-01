//-------------------------------------------------------------------------------------
//
// \file optFlow.h
// \brief 
//
// \author Francois Visconte <f.visconte@gmail.com> 
// http://digitalork.blogspot.com, http://github.com/dopuskh3
//
//------------------------------------------------------------------------------------ 


#ifndef _OPTFLOWHS_H_
#define _OPTFLOWHS_H_

#include "ofMain.h"
#include "ofxVec2f.h"
#include "ofxVec4f.h"
#include "ofxOpenCv.h"

#define OPTFLOW_SMOOTH false

// optical flow BM parameters 
// see: 

class optFlowHS {

  public:
    optFlowHS();
  
    void init(int w, int h, int scale);   
    void update(unsigned char *pixels);
  
	int getWidth();
	int getHeight();
    void getFlowAt(int x, int y, ofxVec2f &flow);

    void drawImage(); 
    void drawFlow();

    ofxCvGrayscaleImage  previous_image;
    ofxCvGrayscaleImage  current_image; 
		
	int step;
	int height; 
	int width;
    IplImage *velX; 
    IplImage *velY;
    IplImage *_tvx;
    IplImage *_tvy;

    bool optFlowSmooth; 
    CvTermCriteria _criteria;
    float _lambda;
};

#endif
