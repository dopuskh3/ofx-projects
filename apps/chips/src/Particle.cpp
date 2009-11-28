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
