#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	
	ofBackground(20,20,20);
	ofSetFrameRate(32);

    tracker.setup(320, 240); 
    w = ofGetWidth(); 
    h = ofGetHeight();
    // world = new bWorld();
    // world->createWorld();
    //480, 640); 
    //, 240); 
	// video.loadMovie("multiPerson-FromBehind-IR.mov");
    //spectrum.setup(std::string("test.mp3"), 72); 
    //spectrum.play(); 

}

//--------------------------------------------------------------
void testApp::update(){

  tracker.update();
  //if (tracker.getConvexBlobs().size() >= 1 )
  //  spectrum.setShape(&tracker.getBlobs()[0].pts); 
  //else
  //  std::cout<<"Nothing to draw"<<tracker.getConvexBlobs().size()<<std::endl;
  //spectrum.update();
}

//--------------------------------------------------------------
void testApp::draw(){
  ofSetColor(255, 255, 255);


  //tracker.source.draw(tracker.width*2, 0);
  //tracker.contourFinder.draw(0, 0); 
  //ofSetColor(255, 255, 255);
  //tracker.background.draw(tracker.width, 0); 
  ofSetColor(25, 25, 25);
  tracker.threshold.draw(0, 0, w, h) ; 
  tracker.draw(0, 0, w, h ); 
  ofFill();
  //spectrum.draw();
  
  //world->shapeFromBlobs(tracker.getBlobs()); 
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 

  switch(key){
    case 'g':
      tracker.setBackground();
      break;
    case OF_KEY_UP:
      tracker.threshValue+=1;
      break;
    case OF_KEY_DOWN:
      tracker.threshValue-=1; 
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
