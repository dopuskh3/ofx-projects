#include "testApp.h"
#include "ofxVectorMath.h"


//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(20,20,20);
	ofSetFrameRate(30);

	font.loadFont("Batang.ttf", 130, true, false, true);
	//font.drawStringAsShapes("Foobar", 100, 100); //true, false, true);
	cs = new charShape(&font);
    cs->loadChar('F');


}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255, 255, 255);
	//ofSetColor(0, 0, 0);
	
//	psys.draw();
	cs->draw(400, 400);
	
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
