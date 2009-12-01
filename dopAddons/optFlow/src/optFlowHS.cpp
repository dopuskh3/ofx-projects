//-------------------------------------------------------------------------------------
//
// \file optFlowHS.cpp
// \brief 
//
// \author Francois Visconte <f.visconte@gmail.com>
// http://digitalork.blogspot.com, http://github.com/dopuskh3
//
//------------------------------------------------------------------------------------ 
#include "optFlowHS.h"

optFlowHS::optFlowHS(){}

void optFlowHS::init(int w, int h, int scale){
  width = w;
  height = h;
  step = scale;
  optFlowSmooth = OPTFLOW_SMOOTH;

  previous_image.allocate(w, h);
  current_image.allocate(w, h);
  
  _tvx = cvCreateImage(cvSize(w, h), IPL_DEPTH_32F, 1);
  _tvy = cvCreateImage(cvSize(w, h), IPL_DEPTH_32F, 1); 
  _criteria.epsilon = 0.0001f;
  _criteria.max_iter=3;
  _criteria.type = CV_TERMCRIT_EPS | CV_TERMCRIT_ITER;
  _lambda = 30;
  

  CvSize tsize = cvSize(int(ceil(double(w)/scale)), int(ceil(double(h)/scale)));

  velX = cvCreateImage(tsize, IPL_DEPTH_32F, 1);
  velY = cvCreateImage(tsize, IPL_DEPTH_32F, 1); 

  // intialize to 0 to avoid infinites 
  cvSetZero(_tvx);
  cvSetZero(_tvy);
  cvSetZero(velX);
  cvSetZero(velY);
}   



void optFlowHS::update(unsigned char *pixels){
  ofxCvColorImage _temp;

  _temp.allocate(getWidth(), getHeight());
  _temp.setFromPixels(pixels, getWidth(), getHeight());
  //_temp.resize(current_image.getWidth(), current_image.getHeight());

  //_temp.erode();
  _temp.blur(4);
  previous_image = current_image;
  current_image = _temp;
  
   cvCalcOpticalFlowHS(previous_image.getCvImage(), current_image.getCvImage(), 0, 
      _tvx, _tvy, 
      _lambda, _criteria);
  
  if(optFlowSmooth){
    IplImage *_tmpImage = cvCreateImage( cvSize(getWidth(), getHeight()), IPL_DEPTH_32F, 1); 
    cvSmooth(_tvx, _tmpImage, CV_GAUSSIAN, 3, 3);
    cvResize(_tmpImage, velX);

    cvSmooth(_tvy, _tmpImage, CV_GAUSSIAN, 3, 3);
    cvResize(_tmpImage, velY);
  } else { 
    cvResize(_tvx, velX);
    cvResize(_tvy, velY);
  }


}

int optFlowHS::getWidth(){return width;}

int optFlowHS::getHeight(){return height;}


void optFlowHS::getFlowAt(int x, int y, ofxVec2f &flow){
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

void optFlowHS::drawImage(){
 current_image.draw(0, 0);
} 
void optFlowHS::drawFlow(){
 for(int x=0; x < getWidth()-step; x+=step){
   for(int y=0; y < getHeight()-step; y+=step){
    ofxVec2f v; 
    getFlowAt(x, y, v);
    ofLine(x, y, x+v.x, y+v.y);
   }
 }

}


