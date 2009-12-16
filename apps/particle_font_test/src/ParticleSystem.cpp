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




ParticleSystem::ParticleSystem(){
  noise = new Perlin(5, 4, 1.0f, time(NULL));

}
//---------------------------------------------------- Setup
// - particles
// - erase flag
//
void ParticleSystem::setup(int nParticles, int w, int h){
	
	width = w;
	height = h;
	
  for(int i=0; i < nParticles; i++){
    addParticle();
  }

}

void ParticleSystem::addSourcePoint(float x, float y){
  sourcePoints.push_back(ofxVec3f(x, y, 0));
}

void ParticleSystem::addParticle(){
  int index = ofRandom(0, sourcePoints.size() - 1);

  Particle p = Particle(ofxVec3f(ofRandom(0, width), ofRandom(0, height), 0), 
												sourcePoints[index]);
  particles.push_back(p);
}

bool ParticleSystem::particleDeserveToLive(int j){
  if (particles[j].position.x < 0 || particles[j].position.y < 0
      || particles[j].position.x > width || particles[j].position.y > height
      || particles[j].ttl < 0  ) {
    return false;
  }
  return true;
}

void ParticleSystem::update(){
  
	for(int i = 0; i < particles.size(); i++){
		particles[i].velocity *= 0.9;
		float noiseAngle = noise->Get(particles[i].position.x, particles[i].position.y) * PI;
		float noiseAngle2  = noise->Get(particles[i].position.x, particles[i].position.y) * PI;

		ofxVec3f noiseForce = ofxVec3f(1.2f * cos(noiseAngle), -1.2f * sin(noiseAngle2), 0);
		particles[i].noise = noiseForce;
		particles[i].update();
	}
	
}

void ParticleSystem::toggleErase(){
  erase = ! erase;
}



void ParticleSystem::draw(){
	
	ofSetColor(255,255,255);

	for(int i = 0; i < particles.size(); i++){
		//cout<<"Particle drawing "<<i<<endl;
		particles[i].draw();
	}	
	ofSetColor(255, 0, 0); 
	ofCircle(width/2.0, height/2.0, 3.0);
	
	
}




