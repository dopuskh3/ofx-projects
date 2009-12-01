//-------------------------------------------------------------------------------------
//
// \file optFlowBM.cpp
// \brief 
//
// \author Francois Visconte <f.visconte@gmail.com>
// http://digitalork.blogspot.com, http://github.com/dopuskh3
//
//------------------------------------------------------------------------------------ 


#include "optFlowBM.h"

//---------------------------------------------------- 
optFlowBM::optFlowBM(){
  
}


//----------------------------------------------------   
void optFlowBM::init(int w, int h, int scale){
  width = w;
  height = h;
  step = scale;
  
  previous_image.allocate(w, h);
  current_image.allocate(w, h);
  
  CvSize tsize = cvSize(int(double(w)/scale), int(double(h)/scale));

  velX = cvCreateImage(tsize, IPL_DEPTH_32F, 1);
  velY = cvCreateImage(tsize, IPL_DEPTH_32F, 1); 

  // intialize to 0 to avoid infinites 
  cvSetZero(velX);
  cvSetZero(velY);
  //SetZero(previous_image);
  //SetZero(current_image);
  
  
  block_size = cvSize(scale, scale); 
  shift_size = cvSize(OPTFLOW_SHIFT_SIZE, OPTFLOW_SHIFT_SIZE);
  max_range  = cvSize(OPTFLOW_RANGE, OPTFLOW_RANGE); 
}

//---------------------------------------------------- 
void optFlowBM::setup(int b_size, int s_size, int max_rge){
  block_size = cvSize(b_size, b_size);
  shift_size = cvSize(s_size, s_size);
  max_range  = cvSize(max_rge, max_rge);

  CvSize tsize = cvSize(int(double(width)/step), int(double(height)/step));
  
  cvReleaseImage(&velX); 
  cvReleaseImage(&velY);

  velX = cvCreateImage(tsize, IPL_DEPTH_32F, 1);
  velY = cvCreateImage(tsize, IPL_DEPTH_32F, 1); 

}

//---------------------------------------------------- -
void optFlowBM::update(unsigned char *pixels){
   ofxCvColorImage _temp;

  _temp.allocate(getWidth(), getHeight());
  _temp.setFromPixels(pixels, getWidth(), getHeight());

  _temp.blur(4);
  previous_image = current_image;
  current_image = _temp;

  // create optical flow
  cvCalcOpticalFlowBM(previous_image.getCvImage(), current_image.getCvImage(), 
                      block_size, shift_size, max_range, 1, 
                      velX, velY);
    
}


//---------------------------------------------------- 

//---------------------------------------------------- 
int optFlowBM::getWidth(){ return width; }

//---------------------------------------------------- 
int optFlowBM::getHeight(){ return height; }

//---------------------------------------------------- 
void optFlowBM::getFlowAt(int x, int y, ofxVec2f &flow){
  int dx = x/step;
  int dy = y/step;
  if (x >= width || y >= height || x < 0 || y < 0){
    flow.x = 0; 
    flow.y = 0;
  } else {
    flow.x = cvGetReal2D(velX, dy, dx);
    flow.y = cvGetReal2D(velY, dy, dx);
  }
}

//---------------------------------------------------- 
void optFlowBM::getNMax(vector<ofxVec4f> &points){

}

//---------------------------------------------------- 
void optFlowBM::drawImage(){ 
 current_image.draw(0, 0);
}

//---------------------------------------------------- 
void optFlowBM::drawFlow(){
 for(int x=0; x < getWidth()-step; x+=step){
   for(int y=0; y < getHeight()-step; y+=step){
    ofxVec2f v; 
    getFlowAt(x, y, v);
    ofLine(x, y, x+v.x, y+v.y);
   }
 }
}

