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

Particle::Particle(ofxVec3f pos, float time_step){

	position = pos;
  velocity = ofxVec3f(0, 0);
  accel   = ofxVec3f(0, 0);
	timeStep = time_step;

  ttl = PARTICLE_TTL;
}



void Particle::resetForce(){

  accel.x = 0;
  accel.y = 0;
  accel.z = 0;
}

///////////////////////////////////////////////////////////////////////
void Particle::addForce(ofxVec3f forcePos, float radius, float scale){
  ofxVec3f distance = position - forcePos;
  float dst = distance.length();
  // apply or not
  if (dst > radius)
    return;

  // then apply
  float effect = ( 1 - dst/radius ) * scale;
  accel += distance.normalize() * effect;
}

///////////////////////////////////////////////////////////////////////
void Particle::update(){

  velocity += accel;
  position += velocity * timeStep;

}


///////////////////////////////////////////////////////////////////////
void Particle::addDamping(float damping){
 accel -= velocity * damping;
}
//----------------------------------------------------
void Particle::draw(){

	//ofSetColor(255, 255,255);
  glVertex2f(position.x, position.y);
	//ofCircle(position.x, position.y, 1);

}
