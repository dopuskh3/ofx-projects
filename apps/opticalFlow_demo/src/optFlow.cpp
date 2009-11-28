//-------------------------------------------------------------------------------------
//
// \file optFlow.cpp
// \brief 
//
//
// \author Francois Visconte <f.visconte@gmail.com>
// http://digitalork.blogspot.com, http://github.com/dopuskh3
//
//------------------------------------------------------------------------------------ 

#include "optFlow.h"

optFlow::optFlow(){
   
}


void optFlow::init(int w, int h, int step){
  cout<<"Initializing video grabber"<<endl;
  
  optFlowSmooth = OPTFLOW_SMOOTH;

  vidGrab = vidGrab; 
  width = w;
  height = h;
  
  previous_image.allocate(getWidth(), getHeight());
  current_image.allocate(getWidth(), getHeight());
  
  velX = cvCreateImage( cvSize(getWidth()/step, getHeight()/step), IPL_DEPTH_32F, 1);
  velY = cvCreateImage( cvSize(getWidth()/step, getHeight()/step), IPL_DEPTH_32F, 1);
  
  _pvx = cvCreateImage( cvSize(getWidth()/step, getHeight()/step), IPL_DEPTH_32F, 1);
  _pvy = cvCreateImage( cvSize(getWidth()/step, getHeight()/step), IPL_DEPTH_32F, 1);

  _tvx = cvCreateImage(cvSize(w, h), IPL_DEPTH_32F, 1);
  _tvy = cvCreateImage(cvSize(w, h), IPL_DEPTH_32F, 1); 

  this->step = step;
	
}


void optFlow::update(unsigned char *pixels){
  // swap images 
  ofxCvColorImage _temp;

  _temp.allocate(getWidth(), getHeight());
  _temp.setFromPixels(pixels, getWidth(), getHeight());
  //_temp.resize(current_image.getWidth(), current_image.getHeight());

  //_temp.erode();
  _temp.blur(4);
  previous_image = current_image;
  current_image = _temp;

  cvCalcOpticalFlowLK(previous_image.getCvImage(), current_image.getCvImage(), cvSize(3,3),
      _tvx, _tvy);
 
  cvCopy(velX, _pvx);
  cvCopy(velY, _pvy);

  cvResize(_tvx, velX);
  cvResize(_tvy, velY);
  
  
  if(optFlowSmooth){
    IplImage *_tmpImage = cvCreateImage( cvSize(getWidth()/step, getHeight()/step), IPL_DEPTH_32F, 1); 
    cvSmooth(velX, _tmpImage, CV_GAUSSIAN, 3, 3);
    //cvThreshold(_tmpImage, velX, OPTFLOW_THRESHOLD, 0, CV_THRESH_TOZERO);
    cvCopy(_tmpImage, velX);

    cvSmooth(velY, _tmpImage, CV_GAUSSIAN, 3, 3);
    cvCopy(_tmpImage, velY);
    //cvThreshold(_tmpImage, velY, OPTFLOW_THRESHOLD, 0, CV_THRESH_TOZERO);
    
    cvAdd(velX, _pvx, _tmpImage);
    cvScale(_tmpImage, velX, 0.5);
    cvAdd(velY, _pvy, _tmpImage);
    cvScale(_tmpImage, velY, 0.5);
  }

}


void optFlow::getFlowAt(int x, int y, ofxVec2f &flow){
  int dx = x/step;
  int dy = y/step;
  flow.x = cvGetReal2D(velX, dy, dx);
  flow.y = cvGetReal2D(velY, dy, dx);
}

void optFlow::draw(){
 
 current_image.draw(0, 0);
 ofSetColor(255, 0, 0);

 for(int x=0; x < getWidth()-step; x+=step){
   for(int y=0; y < getHeight()-step; y+=step){
    ofxVec2f v; 
    getFlowAt(x, y, v);
    ofLine(x, y, x+v.x, y+v.y);
   }
 }
}
