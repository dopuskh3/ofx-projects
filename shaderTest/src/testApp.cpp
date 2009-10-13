#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	
	ofBackground(20,20,20);
	ofSetFrameRate(32);
    
    glDepthMask(false);
    glDisable(GL_DEPTH_TEST);
    glEnable( GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
   
       
    shader.loadShader((char *)"diffuse");
    shader.printActiveUniforms(); 
    psys.setup(50); 
  
    glActiveTexture(GL_TEXTURE0);
    tex.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    std::cout<<"tex.getTextureData().textureName[0] "<< tex.getTextureData().textureName[0]<<std::endl;
    

    /*for (int i = 0 ; i < 10; i++){
      ofxVec3f pos; 
      pos.x = ofRandom(0, ofGetWidth()); 
      pos.y = ofRandom(0, ofGetHeight());
      pos.z = 0; 
      float forceVal = ofRandom(1,2); 
      float radius = ofRandom(100, 400); 
      psys.addRepiel(pos, forceVal, radius); 
    }*/

    //---------------------------------------------------- -
}

//--------------------------------------------------------------
void testApp::update(){

  psys.update(); 

}

//--------------------------------------------------------------
void testApp::draw(){
  

  //ofEnableAlphaBlending();
 
  ofEnableAlphaBlending();
 
 
  tex.begin();
  ofSetColor(200, 200, 200); //55, 255);
  psys.draw(); 
  tex.end();

  //tex.draw( ofGetWidth()/2,0 , ofGetWidth()/2, ofGetHeight()/2);
  
  ofSetColor(255,255,255);
  //glBindTexture(GL_TEXTURE_2D, (GLuint)tex.getTextureData().textureName[0]);
  
  //glActiveTexture(GL_TEXTURE0);
  //tex.bindAsTexture();
  shader.setUniform("tex", (int) 0);
 //glBindTexture(GL_TEXTURE_2D, (GLuint)tex.getTextureData().textureName[0]);
  shader.setShaderActive(true); 
     tex.draw(0,0);
     //, ofGetWidth()/2.0, ofGetHeight()/2.0);
  shader.setShaderActive(false);


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
