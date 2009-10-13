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

Particle::Particle(float x, float y){

  this->position = ofxVec3f(x,y); 
  this->velocity = ofxVec3f(0, 0);
  this->accel   = ofxVec3f(0, 0); 
  ttl = PARTICLE_TTL; 
  damping = 0.02f;
  fuzz = 0.0;

}

//---------------------------------------------------- 
void Particle::update(){
  ttl--; 
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
void Particle::addDamping(){
 accel = accel - velocity * damping; 
}

//----------------------------------------------------
void Particle::addForce(ofxVec3f f){
  //std::cout<<f.length()<<std::endl;
  //float oldlen = velocity.length();  
  accel += f; 
  //velocity.scale(oldlen);
}

//---------------------------------------------------- 
void Particle::addAttractionForce(ofxVec3f &fpos, float radius, float scale){

  ofxVec3f diff = position - fpos; 
  float len = diff.length(); 

  if ( radius > 0 && len < radius){
    float pct = 1 - (len / radius); 
    diff.normalize(); 
    accel -= diff * scale * pct; 
  }

}

//---------------------------------------------------- 
void Particle::addRepulsionForce(ofxVec3f &pos, float radius, float scale){
  addAttractionForce(pos, radius, 0-scale); 
}


//---------------------------------------------------- 
void Particle::draw(){
  //if(!raise)
  ofCircle(this->position.x, this->position.y, 5);
  //glBegin(GL_POINTS);
  //glVertex3f(position.x, position.y, position.z);
  //glEnd( );
}
