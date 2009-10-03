///=====================================================================================
/// \file testApp.cpp
/// \brief 
///
/// \author f.visconte, francois.visconte@milpix.com
/// \version $Id$
///
///====================================================================================


#include "testApp.h"


void testApp::setup(){
  
  ofBackground(3,2,2); 
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE); 
  
  fftList=NULL;
  bands = 64;

  music.loadSound("music.mp3"); 
  music.play(); 
  music.setVolume(1); 

}


void testApp::update(){
  
  this->fftList = ofSoundGetSpectrum(bands); 

}


void testApp::draw(){
  
  for(int i =0 ; i < bands; i++){
    if ( this->fftList[i] > 0.6){
      std::cout<<"VALUE "<<this->fftList[i]<<std::endl;
      fflush(stdout);
    }

    ofLine(i, ofGetHeight(), i, (ofGetHeight() - (this->fftList[i] * ofGetHeight())));

  }

}

void testApp::keyPressed(int key){} 
void testApp::keyReleased (int key){}

void testApp::mouseMoved(int x, int y ){}
void testApp::mouseDragged(int x, int y, int button){}
void testApp::mousePressed(int x, int y, int button){}
void testApp::mouseReleased(){}




