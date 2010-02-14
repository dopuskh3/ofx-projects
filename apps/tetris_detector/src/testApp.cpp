#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(20,20,20);
	//ofSetFrameRate(32);

  vidGrabber.setVerbose(true);
	//vidGrabber.setUseTexture(false);
  vidGrabber.initGrabber(640, 480);
  tclass.init(640, 480);

}

//--------------------------------------------------------------
void testApp::update(){

  vidGrabber.grabFrame();
  if( vidGrabber.isFrameNew()){
    tclass.update(vidGrabber.getPixels());
  }
}

//--------------------------------------------------------------
void testApp::draw(){
  ofSetColor(255, 255, 255);
  //vidGrabber.draw(0, 0);
  tclass.draw();
  //skin_classifier.draw(700, 700);
  //skin_classifier.draw(700, 700);
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){

  switch(key){
    case 'g':
      break;
    case OF_KEY_UP:
      break;
    case OF_KEY_DOWN:
      break;
  }
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
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
