#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	
	ofBackground(20,20,20);
	ofSetFrameRate(32);
    //ofSetFrameRate(30);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);                                                                                                                            
    glDepthMask(false);
    glDisable(GL_DEPTH_TEST);
    glEnable( GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    
    tex.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    std::cout<<"tex.getTextureData().textureName[0]"<< tex.getTextureData().textureName[0]<<std::endl;
    //glActiveTexture(GL_TEXTURE0);
    // load shader 
    shader.loadShader("diffuse");
    shader.printActiveUniforms(); 
    psys.setup(5000); 
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
  
  //getTextureId());

  //ofEnableAlphaBlending();
   
  ofEnableAlphaBlending();
 
 
  tex.begin();
  ofSetColor(200, 200, 200); //55, 255);
  psys.draw(); 
  tex.end();

  tex.draw( ofGetWidth()/2,0 , ofGetWidth()/2, ofGetHeight()/2);
  
  ofSetColor(255,255,255);
  glActiveTexture(GL_TEXTURE0);
  tex.bindAsTexture(); 
  shader.setUniform("tex", (int) 0);
 //glBindTexture(GL_TEXTURE_2D, (GLuint)tex.getTextureData().textureName[0]);
  shader.setShaderActive(true); 
  
     tex.draw(0,0, ofGetWidth()/2.0, ofGetHeight()/2.0);

  shader.setShaderActive(false);


  /*
  glEnable(tex.getTextureData().textureTarget );
  //glBindTexture (tex.getTextureData().textureTarget, (GLuint)tex.getTextureData().textureID ); 

  glActiveTexture(GL_TEXTURE0); 
  tex.loadScreenData(0, 0, ofGetWidth(), ofGetHeight());
  glBindTexture(GL_TEXTURE_2D, (GLuint)tex.getTextureData().textureName[0]);
  shader.setUniform("tex", 0);
  shader.setShaderActive(true); 
  
  //glBindTexture(GL_TEXTURE_2D, (GLuint)tex.getTextureData().textureName[0]); 
  tex.draw(0,0, ofGetWidth()/2, ofGetHeight()/2);
  //glBindTexture(GL_TEXTURE_2D, (GLuint)tex.getTextureData().textureName[0]); 
  //glActiveTexture(GL_TEXTURE4);
  //glBindTexture(GL_TEXTURE_2D, (GLuint)tex.getTextureData().textureName[0]);
  shader.setShaderActive(false);
  glBindTexture(tex.getTextureData().textureTarget, 0);                                                                                            
  glDisable(tex.getTextureData().textureTarget );
  */

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
