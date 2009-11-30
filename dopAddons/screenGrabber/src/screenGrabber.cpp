//-------------------------------------------------------------------------------------
//
// \file screenGrabber.cpp
// \brief 
//
// \author Francois Visconte <f.visconte@gmail.com>
// http://digitalork.blogspot.com, http://github.com/dopuskh3
//
//------------------------------------------------------------------------------------ 


#include "screenGrabber.h"



void screenGrabber::init(int w, int h){
  

  width = w;
  height = h; 
  count = 0;
}

void screenGrabber::init(){

  width = ofGetWidth();
  height = ofGetHeight();
}


void screenGrabber::grab(){
  
  char filename[255];

  img.grabScreen(0, 0, height, width);  
  //img.resize(height/2, width/2); 
  sprintf(filename, "screen_%08i.png", count);
  img.saveImage(filename);
  //img.saveThreaded(filename);
  //Threaded(filename);
  count++;

}
