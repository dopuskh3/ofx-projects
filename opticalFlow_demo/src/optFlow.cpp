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


void optFlow::init(ofVideoGrabber *vidGrab, float scale){
  cout<<"Initializing video grabber"<<endl;
  this->vidGrab = vidGrab; 
  this->previous_image.allocate(this->getWidth()*scale, this->getHeight()*scale);
  this->current_image.allocate(this->getWidth()*scale, this->getHeight()*scale);
  
  this->velX = cvCreateImage( cvSize(this->getWidth()*scale, this->getHeight()*scale), IPL_DEPTH_32F, 1);
  this->velY = cvCreateImage( cvSize(this->getWidth()*scale, this->getHeight()*scale), IPL_DEPTH_32F, 1);
  this->scale = scale;
}




void optFlow::update(){
  // swap images 
  ofxCvColorImage _temp;
  this->vidGrab->grabFrame();

  if (this->vidGrab->isFrameNew()){
    _temp.allocate(this->getWidth(), this->getHeight());
    _temp.setFromPixels(this->vidGrab->getPixels(), this->getWidth(), this->getHeight());
    _temp.resize(current_image.getWidth(), current_image.getHeight());
    //_temp.erode();
    //_temp.blur(3);
    this->previous_image = this->current_image;
    this->current_image = _temp;
    
     
    cvCalcOpticalFlowLK(this->previous_image.getCvImage(), this->current_image.getCvImage(), cvSize(3,3),
                        velX, velY);
  }
}

void optFlow::getFlowAt(int x, int y, ofxVec2f &flow){
  int i = (float)x*this->scale;
  int j = (float)x*this->scale;
  //cout<<"Pixel at ("<<x<<", "<<y<<") -> ("<<i<<", "<<j<<")"<<endl;
  
  flow.x = (float )(this->velX->imageData + this->velX->widthStep*j)[i];
  flow.y = (float )(this->velY->imageData + this->velY->widthStep*j)[i];
}

void optFlow::draw(){

 //this->velX.draw(0, 0);
 int xstep = floor(1.0/scale);
 int ystep = floor(1.0/scale); 
 
 current_image.draw(100, 400);
 for(int x=0; x < this->getWidth(); x+=xstep){
   for(int y=0; y < this->getHeight(); y+=ystep){
    ofxVec2f v; 
    getFlowAt(x, y, v);
    ofLine(x, y, x+v.x*0.1, y+v.y*0.1);
   }
 }
}
