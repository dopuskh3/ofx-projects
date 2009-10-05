#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	
	ofBackground(20,20,20);
	ofSetFrameRate(32);

    tracker = new bTracker(320, 240); 
    world = new bWorld();
    world->createWorld();
    //480, 640); 
    //, 240); 
	//video.loadMovie("multiPerson-FromBehind-IR.mov");

}

//--------------------------------------------------------------
void testApp::update(){
  tracker->update();
}

//--------------------------------------------------------------
void testApp::draw(){
  ofSetColor(255, 255, 255);
  tracker->source.draw(tracker->width*2, 0);
  ofSetColor(255, 255, 255);
  //tracker->contourFinder.draw(0, 0); 
  ofSetColor(255, 255, 255);
  tracker->background.draw(tracker->width, 0); 
  tracker->threshold.draw(0, tracker->height);
  world->shapeFromBlobs(tracker->getBlobs()); 
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 

  switch(key){
    case 'g':
      tracker->setBackground();
      break;
    case OF_KEY_UP:
      tracker->threshValue+=10;
      break;
    case OF_KEY_DOWN:
      tracker->threshValue-=10; 
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