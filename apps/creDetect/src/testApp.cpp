#include "testApp.h"

#define WIDTH 640
#define HEIGHT 480

//--------------------------------------------------------------
void testApp::setup(){
  ofBackground(20,20,20);
	//ofSetFrameRate(32);

  vidGrabber.setVerbose(true);
  vidGrabber.initGrabber(WIDTH, HEIGHT); 

  image.allocate(WIDTH, HEIGHT);
  gimage.allocate(WIDTH, HEIGHT); 
  deplay.init();


}

//--------------------------------------------------------------
void testApp::update(){

  vidGrabber.grabFrame();
  if( vidGrabber.isFrameNew()){
    image.setFromPixels(vidGrabber.getPixels(), WIDTH, HEIGHT); 
    gimage = image; 
    deplay.update(gimage); 
  }
}

//--------------------------------------------------------------
void testApp::draw(){
  ofSetColor(255, 255, 255);
  //vidGrabber.draw(0, 0);
  //gimage.draw(0,0); 
  deplay.draw();
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

  //cout<<"Mouse pressed "<<endl;

}

//--------------------------------------------------------------
void testApp::mouseReleased(){

}
