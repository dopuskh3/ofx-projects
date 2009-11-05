#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	
	ofBackground(0,0,0);
	ofSetFrameRate(32);
    
    glDepthMask(false);
    glDisable(GL_DEPTH_TEST);
    glEnable( GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
   
       
    shader.loadShader((char *)"diffuse");
    shader.printActiveUniforms(); 
    

    psys.setup(56); 
  
    glActiveTexture(GL_TEXTURE0);
    tex.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    std::cout<<"tex.getTextureData().textureName[0] "<< tex.getTextureData().textureName[0]<<std::endl;
    

    fftList=NULL;                                                                                                   
    bands = 127;

    fftSmoothed = (float *)malloc(bands* sizeof(float));
    for (int i =0 ; i < bands; i++)
      fftSmoothed[i] = 0.0; 

    music.loadSound("test.mp3"); 
    music.play(); 
    music.setVolume(1); 



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



  fftList = ofSoundGetSpectrum(bands); 

  for (int i = 0; i < bands; i++){
      //fftList[0] = 0.0f;
      //fftList[bands-1] = 0.0f;
      if(fftList[i]>1.0f) fftList[i] = 0.9f;
      fftList[i] = cbrtf(fftList[i]);
      //fftList[i] = (fftList[i-1] + fftList[i] +  fftList[i+1]) / 3.0f;
      fftSmoothed[i] =0.2f; // 0.000010f; 
      if ( fftSmoothed[i] < fftList[i] ){
        fftSmoothed[i] = fftList[i]; 
        //if(fftSmoothed[i] > 1.0f){
        //  fftSmoothed[i]=1.0f;
        //}
      }
  }

  psys.setFFT(fftSmoothed, bands); 
  psys.update(); 

}

//--------------------------------------------------------------
void testApp::draw(){
  

  //ofEnableAlphaBlending();
 
  ofEnableAlphaBlending();
  glEnable(GL_BLEND);
  glEnable(GL_LINE_SMOOTH); 
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 
  glClear(GL_COLOR_BUFFER_BIT); 
  //tex.begin();
//  glColor4f(0.4, 0.4, 0.4, 0.5); 
  //ofSetColor(200, 200, 200, 100); //55, 255);
  psys.draw(); 
  //tex.end();

  //tex.draw( ofGetWidth()/2,0 , ofGetWidth()/2, ofGetHeight()/2);
  
 // ofSetColor(255,255,255, 100);
  //glBindTexture(GL_TEXTURE_2D, (GLuint)tex.getTextureData().textureName[0]);
  
  //glActiveTexture(GL_TEXTURE0);
  //tex.bindAsTexture();
  shader.setUniform((char *)"tex", (int) 0);
 //glBindTexture(GL_TEXTURE_2D, (GLuint)tex.getTextureData().textureName[0]);
  //shader.setShaderActive(true); 
    // tex.draw(0,0);
     //, ofGetWidth()/2.0, ofGetHeight()/2.0);
  shader.setShaderActive(false);


}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 

  switch(key){
    case 'g':
      break;
    case 'f':
      ofSetFullscreen(true);
      psys.width = ofGetWidth();
      psys.height = ofGetHeight();
      break;
    case 'F':
      ofSetFullscreen(false);
      psys.width = ofGetWidth();
      psys.height = ofGetHeight();
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
