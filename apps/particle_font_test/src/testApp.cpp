#include "testApp.h"
#include "ofxVectorMath.h"


//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(20,20,20);
	ofSetFrameRate(30);
	
	font.loadFont("Batang.ttf", 130, true, false, true);
	font.drawStringAsShapes("Foobar", 100, 100); //true, false, true);

    ofTTFCharacter charB = font.getCharacterAsPoints('F');
    for(int ci=0; ci<charB.contours.size(); ci++) { // loop all contours
         ofTTFContour contour = charB.contours[ci];
         for(int pi=0; pi<contour.pts.size()-1; pi++) { // loop all points of that contour
           ofxVec2f p1 = ofxVec2f(contour.pts[pi].x, contour.pts[pi].y);
           ofxVec2f p2 = ofxVec2f(contour.pts[pi+1].x, contour.pts[pi+1].y);
           while((p1-p2).length()>1){
            cout<<p1.x<<" - "<<p1.y<<endl;
            psys.addSourcePoint(p1.x+200, p1.y+200);
            p1 += (p2-p1).normalize();
           }
         }
    } 

	psys.setup(900, ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void testApp::update(){
	psys.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255, 255, 255);
	
	psys.draw();
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
