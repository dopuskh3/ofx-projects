///=====================================================================================
/// \file Particle.cpp
/// \brief 
///
/// \author f.visconte, francois.visconte@milpix.com
/// \version $Id$
///
///====================================================================================


#include "Particle.h"

Particle::Particle(float x, float y){

  this->position = ofPoint(x,y); 
  this->velocity = ofPoint(0, 0);
  this->accel   = ofPoint(0, 0); 

}

void Particle::update(){
  this->velocity += this->accel; 
  this->position += this->velocity; 
}

void Particle::draw(){

  ofCircle(this->position.x, this->position.y, 2);
}
