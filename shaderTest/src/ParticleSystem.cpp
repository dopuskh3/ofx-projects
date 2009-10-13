//-------------------------------------------------------------------------------------
//
// \file ParticleSystem.cpp
// \brief 
//
// \author Francois Visconte <f.visconte@gmail.com>
// http://digitalork.blogspot.com, http://github.com/dopuskh3
//
//------------------------------------------------------------------------------------ 



#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(){}


//---------------------------------------------------- Setup
// - particles
// - erase flag
//
void ParticleSystem::setup(int nParticles){
  for(int i=0; i < nParticles; i++){
    Particle p = Particle(0, ofRandom(0, ofGetWidth())); 
    p.velocity.y = 0; 
    p.velocity.x = ofRandom(2,5);
    particles.push_back(p);
  }  
  mouseX = 0; 
  mouseY = 0;
  erase = 0;
}


void setFuzzFactor(float fuzz){
      
}

void ParticleSystem::addRepiel(ofxVec3f center, float fValue, float fRadius){
  forcesPos.push_back(center); 
  forcesVal.push_back(fValue);  
  forcesRad.push_back(fRadius);
  std::cout<<fRadius<<std::endl;
}

void ParticleSystem::update(){
  int repielValue = 2; 

  // for each particles 
  for(int j=0; j < particles.size(); j++){
    particles[j].accel.set(0,0,0);
    particles[j].addDamping();
    ofxVec3f mousePos = ofxVec3f(mouseX, mouseY); 
 
    if (particles[j].ttl < 0){
      std::cout<<"erasiong particle"<<std::endl;
      particles.erase(particles.begin() + j);//  particles.erase(j);
      continue;
    }
    // for each force 
    for(int i=0; i< forcesPos.size(); i++){
        particles[j].addAttractionForce(forcesPos[i], forcesRad[i], forcesVal[i]); 
    }

    particles[j].addAttractionForce(mousePos, 1000.0f, 1.2f);
    particles[j].update();

  }

}

void ParticleSystem::toggleErase(){
 erase = ! erase; 
}



void ParticleSystem::draw(){

#ifdef DRAW_REPIELS
  ofSetColor(255, 0, 0);
  ofNoFill();
  for(int i=0; i< forcesPos.size(); i++){
    ofCircle(forcesPos[i].x, forcesPos[i].y, forcesRad[i]); 
  }
#endif 
  ofFill();
  ofSetColor(255, 255, 255);
  for(int i=0; i < this->particles.size(); i++)
    this->particles[i].draw();
}




