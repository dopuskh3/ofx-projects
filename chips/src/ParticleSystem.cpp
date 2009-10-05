///=====================================================================================
/// \file ParticleSystem.cpp
/// \brief 
///
/// \author f.visconte, francois.visconte@milpix.com
/// \version $Id$
///
///====================================================================================


#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(int nParticles){
  for(int i=0; i < nParticles; i++){
    Particle p = Particle(ofRandom(0, ofGetHeight()), ofRandom(0, ofGetWidth())); 
    p.velocity.y = 1.0; 
    p.velocity.x = 0;
    this->particles.push_back(p);
  }
}

void ParticleSystem::update(){
  for(int i=0; i < this->particles.size(); i++)
    this->particles[i].update();
}

void ParticleSystem::draw(){

  for(int i=0; i < this->particles.size(); i++)
    this->particles[i].draw();

}

void ParticleSystem::checkBlob(bBlob *b){
  for(int i = 0; i < this->particles.size(); i++){
    if(b->getPointProx(this->particles[i].position))
      std:cout<<"Collision"<<std::endl;
  }
}

