///=====================================================================================
/// \file testApp.cpp
/// \brief 
///
/// \author f.visconte, francois.visconte@milpix.com
/// \version $Id$
///
///====================================================================================


#include "testApp.h"

void clamp(float *f, int size){
  
  float max=-100.0f;
  //0000000000; 
  float min=100.0f; 
  float factor=0.0f;
 for(int i = 0; i<size; i++){
  max=f[i]>max?f[i]:max;
  min=f[i]<min?f[i]:min;
 } 

 factor = (max!=min)?1/(max-min):1; 
 for(int i=0; i<size; i++)
   f[i] = (f[i]-min)*factor; 
 
}
void testApp::setup(){
  
  ofBackground(3,2,2); 
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE); 
  
  fftList=NULL;
  bands = 256;

  fftSmoothed = (float *)malloc(bands* sizeof(float));
  for (int i =0 ; i < bands; i++)
    fftSmoothed[i] = 1.0; 

  music.loadSound("test.mp3"); 
  music.play(); 
  music.setVolume(1); 
    
  /* ofSoundStreamListDevices(); 
  ofSoundStreamSetup(1, 1, this); 
  ofSoundStreamStart(); 
  */
}


void testApp::update(){
  
  this->fftList = ofSoundGetSpectrum(bands); 

  for (int i = 0; i < bands; i++){
      if (i>2 && i < bands-2)
        fftList[i] = (fftList[i-1] +fftList[i-2] + fftList[i+2] + fftList[i+1]) / 4.0f;
      fftSmoothed[i] *= 0.80f; 
      if ( fftSmoothed[i] < fftList[i] ){
        fftSmoothed[i] = fftList[i]; 
        if(fftSmoothed[i] > 1.0f){
          fftSmoothed[i]=1.0f;
        }
      }
  }

}


void testApp::draw(){
  
  for(int i =0 ; i < bands; i++){
    glColor4f(1.0, 1.0, 1.0, fftSmoothed[i]); 

    ofRect(100+i*5, ofGetHeight()-100, 5,  -(fftSmoothed[i] * 500));

  }

}

void testApp::keyPressed(int key){} 
void testApp::keyReleased (int key){}

void testApp::mouseMoved(int x, int y ){}
void testApp::mouseDragged(int x, int y, int button){}
void testApp::mousePressed(int x, int y, int button){}
void testApp::mouseReleased(){}




