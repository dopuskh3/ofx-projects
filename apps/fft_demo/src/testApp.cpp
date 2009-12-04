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
    bands = 256;
    amort = 0;
    tbands = bands;

    fftSmoothed = (float *)malloc(bands* sizeof(float));

    for (int i =0 ; i < bands; i++)
      fftSmoothed[i] = 0.0; 
  
    gui.addTitle("Control");
    gui.addSlider("fft mult", psys.fftMult , 0.0, 200.0);
    gui.addSlider("noise mul", psys.noiseMult, 0.0, 30.0);
    gui.addSlider("max particles", psys.maxParticles, 0, 800);
    gui.addSlider("Low Thresh", psys.lowThresh, 0.0, 1.0);
    gui.addSlider("Mid Thresh", psys.midThresh, 0.0, 1.0);
    gui.addSlider("High Thresh", psys.highThresh, 0.0, 1.0);
    gui.addSlider("Particle Size Min", psys.particleSizeMin, 0, 50);
    gui.addSlider("Particle Size Max", psys.particleSizeMax, 0, 50);
    gui.addSlider("Particle Velocity Mult", psys.particleVelocityMult, 0.0, 1.0);
    gui.addSlider("Velocity Damp", psys.velocityDamp, 0.0, 1.0);
    gui.addSlider("Accel Damp", psys.accelDamp, 0.0, 1.0);
    gui.addToggle("average toggle", psys.averageTrigger);
    gui.addToggle("enable noise", psys.enableNoise); 
    gui.addToggle("rotating angle", psys.rotatingAngle);
    gui.addToggle("random pos", psys.particleRandomPos);
    gui.addToggle("Draw FFT", psys.drawFFT);
    gui.addToggle("Average FFT Speed", psys.averFFTSpeed);
    gui.addSlider("Takke bands", tbands, 0, bands);
    gui.addSlider("Amort", amort, 0, 1);


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
      fftSmoothed[i] *= amort;
      if ( fftSmoothed[i] < fftList[i] ){
        fftSmoothed[i] = fftList[i]; 
        //if(fftSmoothed[i] > 1.0f){
        //  fftSmoothed[i]=1.0f;
        //}
      }
  }

  psys.setFFT(fftSmoothed, tbands);
  //ands);
  //160);
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