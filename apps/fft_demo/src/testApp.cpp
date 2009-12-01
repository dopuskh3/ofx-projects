#include "testApp.h"
#include "ofxSimpleGuiToo.h"

//--------------------------------------------------------------
void testApp::setup(){	
	ofBackground(0,0,0);
	ofSetFrameRate(32);
    
    glDepthMask(false);
    glDisable(GL_DEPTH_TEST);
    glEnable( GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
   
       
    psys.setup(56); 

    fftList=NULL;                                                                                                   
    bands = 127;
    fftSmoothed = (float *)malloc(bands* sizeof(float));

    for (int i =0 ; i < bands; i++)
      fftSmoothed[i] = 0.0; 
  
    gui.addTitle("Control");
    gui.addSlider("fft mult", psys.fftMult , 0.0, 30.0);
    gui.addSlider("noise mul", psys.noiseMult, 0.0, 30.0);
    gui.addToggle("enable noise", psys.enableNoise); 


    music.loadSound("test.mp3"); 
    music.play(); 
    music.setVolume(1); 
  
    gui.loadFromXML();
    gui.show();
}

//--------------------------------------------------------------
void testApp::update(){

  fftList = ofSoundGetSpectrum(bands); 

  for (int i = 0; i < bands; i++){
      //fftList[0] = 0.0f;
      //fftList[bands-1] = 0.0f;
      if(fftList[i]>1.0f) fftList[i] = 0.9f;
      fftList[i] = cbrtf(fftList[i]);
      //fftList[i] = (fftList[i-1] + fftList[i] +  fftList[i+1]) / 3.0f;
      fftSmoothed[i] *= 0.002f; // 0.000010f; 
      if ( fftSmoothed[i] < fftList[i] ){
        fftSmoothed[i] = fftList[i]; 
        //if(fftSmoothed[i] > 1.0f){
        //  fftSmoothed[i]=1.0f;
        //}
      }
  }

  psys.setFFT(fftSmoothed, bands); 
  psys.update(); 

}

//--------------------------------------------------------------
void testApp::draw(){
  

  //ofEnableAlphaBlending();
 
  ofEnableAlphaBlending();
  glEnable(GL_BLEND);
  glEnable(GL_LINE_SMOOTH); 
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 
  psys.draw(); 
  gui.draw();

}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 

  switch(key){
    case 'g':
      break;
    case 'f':
      ofSetFullscreen(true);
      psys.width = ofGetWidth();
      psys.height = ofGetHeight();
      break;
    case 'F':
      ofSetFullscreen(false);
      psys.width = ofGetWidth();
      psys.height = ofGetHeight();
      break;
    case OF_KEY_UP:
      break;
    case ' ': gui.toggleDraw(); break;
    case OF_KEY_DOWN:
      break;
  }
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){ 
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
  psys.mouseX = x;
  psys.mouseY = y; 
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(){

}
