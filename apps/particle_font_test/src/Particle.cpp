//-------------------------------------------------------------------------------------
//
// \file Particle.cpp
// \brief 
//
// \author Francois Visconte <f.visconte@gmail.com>
// http://digitalork.blogspot.com, http://github.com/dopuskh3
//
//------------------------------------------------------------------------------------ 



#include "Particle.h"

Particle::Particle(ofxVec3f pos, ofxVec3f dest){

	position = pos;
  velocity = ofxVec3f(0, 0);
  accel   = ofxVec3f(0, 0); 
	destination = dest; 
	
	
  ttl = PARTICLE_TTL; 
  vDamping = 0.01f;
  aDamping = 0.0f;
  



}


// ---------------------------------------------------- 
void Particle::update(){

  //ttl--; 
	accel += destination - position; 

	accel += noise * accel.length();
	accel/=100; //accel.normalize();
	//cout<<"Accell norm"<<accel.length()<<endl;
  velocity += accel; 
  position += velocity;
  
  //if(fuzz != 0){
  //  ofxVect3f fuzz; 
  //  fuzz.x  = ofRandom(0, 100); 
  //  fuzz.y  = ofRandom(0, 100); 
  //  fuzz.normalize(fuzz); 
  //}
}

//---------------------------------------------------- 
void Particle::draw(){
 
	//ofSetColor(255, 255,255);
	
	ofCircle(position.x, position.y, 2);
	
}
