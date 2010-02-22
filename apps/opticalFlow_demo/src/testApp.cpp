#include "testApp.h"

#define CAP_W 640
#define CAP_H 480

//--------------------------------------------------------------
void testApp::setup(){	
	ofBackground(20,20,20);
	ofSetFrameRate(22);

	vidGrabber.initGrabber(CAP_W, CAP_H);
    cout<<vidGrabber.getWidth()<<endl;
    cout<<vidGrabber.getHeight()<<endl;
    vidGrabber.setVerbose(true);
  

	oflow.init(CAP_W, CAP_H,10);
    //grabber.init();

    particles.setup(300, &oflow, CAP_W, CAP_H);

}

//--------------------------------------------------------------
void testApp::update(){
  vidGrabber.grabFrame();
  if (vidGrabber.isFrameNew()){
    oflow.update(vidGrabber.getPixels());
  }
  particles.update();


}

//--------------------------------------------------------------
void testApp::draw(){
  ofSetColor(255, 255, 255);
  
  oflow.drawImage();
  oflow.drawFlow();
  particles.draw();
  //grabber.grab();
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
