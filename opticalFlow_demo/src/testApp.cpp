#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	
	ofBackground(20,20,20);
	ofSetFrameRate(32);

	vidGrabber.initGrabber(800, 600);
    cout<<vidGrabber.getWidth()<<endl;
    cout<<vidGrabber.getHeight()<<endl;
    vidGrabber.setVerbose(true);

	oflow.init(800, 600,2);
}

//--------------------------------------------------------------
void testApp::update(){
  vidGrabber.grabFrame();
  if (vidGrabber.isFrameNew()){
    oflow.update(vidGrabber.getPixels());
  }


}

//--------------------------------------------------------------
void testApp::draw(){
  ofSetColor(255, 255, 255);
  
  oflow.draw();


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
