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
 #ifndef LIVE_MUSIC
  	bands = 256;
    amort = 0;
    tbands = bands;

    fftSmoothed = new float[bands];

    music.loadSound("test.mp3");
    music.play();
    music.setVolume(1);
#else
  	bands = 256;
    amort = 0;
    tbands = bands;

	fft = ofxFft::create(bands*2, OF_FFT_HAMMING, OF_FFT_FFTW);

	// 0 output channels,
	// 1 input channel
	// 44100 samples per second
	// [bins] samples per buffer
	// 4 num buffers (latency)

	ofSoundStreamSetup(0, 1, this, 44100, bands*2, 4);

	audioInput = new float[bands*2];

    fftList = NULL;
    fftSmoothed = new float[bands];
    for (int i =0 ; i < bands; i++)
      fftSmoothed[i] = 0.0;


#endif
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
    gui.addSlider("Amort", amort, 0.0, 1.0f);
    gui.addSlider("Flow Factor", psys.fftFlowFactor, 0.0, 500.0);


    gui.loadFromXML();
    gui.show();

}

//--------------------------------------------------------------
void testApp::update(){

#ifndef LIVE_MUSIC
  fftList = ofSoundGetSpectrum(bands);

  for (int i = 0; i < bands; i++){
      //fftList[0] = 0.0f;
      //fftList[bands-1] = 0.0f;
      if(fftList[i]>1.0f) fftList[i] = 1.0f;
      //fftList[i] = sqrtf(sqrtf(sqrtf(fftList[i])));
      //fftList[i] = (fftList[i-1] + fftList[i] +  fftList[i+1]) / 3.0f;
      fftSmoothed[i] *= amort;
      if ( fftSmoothed[i] < fftList[i] ){
        fftSmoothed[i] = fftList[i];
      }
      }
  }
#else
  if (fftList){
    //cout<<fft->getBinSize()<<endl;
    psys.setFFT(fftSmoothed, fft->getBinSize());
  //ands);
  //160);
    psys.update();
  }
#endif
}

#ifdef LIVE_MUSIC
void testApp::audioReceived(float* input, int bufferSize, int nChannels) {

    memcpy(audioInput, input, sizeof(float) * bufferSize);
	// compute fft given audioInput
    //
    //
    //

  fftList = fft->fft(audioInput);
  for (int i = 0; i < bands; i++){
      //fftList[0] = 0.0f;
      //fftList[bands-1] = 0.0f;
      if(i<1){ fftList[i] /= 2.0f;}
      //if(fftList[i]>0.7f){ cout<<"LSKD"<<endl; fftList[i] /= 2.0f;}
      fftList[i] = cbrtf(fftList[i]);
      //fftList[i] = (fftList[i-1] + fftList[i] +  fftList[i+1]) / 3.0f;
      fftSmoothed[i];
      fftSmoothed[i] *= amort;
      if ( fftList[i] > fftSmoothed[i]){ //fftSmoothed[i] < fftList[i] ){
        fftSmoothed[i] = fftList[i];
        //if(fftSmoothed[i] > 1.0f){
        //  fftSmoothed[i]=1.0f;
        //}
      } else{
        fftSmoothed[i] *= 0.8f;}
  }

  psys.setFFT(fftSmoothed, tbands);

}
#endif

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
