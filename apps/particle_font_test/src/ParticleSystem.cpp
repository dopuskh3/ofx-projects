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
  noise = new Perlin(2, 4, 1.0f, time(NULL));
  timeStep = 3.0f;
  steps= 100.0f;
}


//---------------------------------------------------- Setup
// - particles
// - erase flag
//
void ParticleSystem::setup(int nParticles, int w, int h){

	width = w;
	height = h;

  //for(int i=0; i < nParticles; i++){
  //  addParticle();
  //}

}

void ParticleSystem::addSourcePoint(float x, float y){
  sourcePoints.push_back(ofxVec3f(x, y, 0));
}

void ParticleSystem::addParticle(){
  int index = ofRandom(0, sourcePoints.size() - 1);

  Particle p = Particle(ofxVec3f(ofRandom(width-10, width+10), ofRandom(0, height)), timeStep);

  p.id = index;
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

  steps=(steps>=1.0f)?steps-1:0.0f;
  cout<<steps<<endl;
	for(int i = 0; i < particles.size(); i++){
    particles[i].resetForce();

    particles[i].addForce(sourcePoints[particles[i].id], 1000.0f, -10.0f);
    //particles[i].addForce(ofxVec3f(1000, 1000), 10000.0f, -10.0f);
    //particles[i].addForce(ofxVec3f(width/2.0f, height/2.0f), 10000.0f, -4.0f);
    float noiseAngle   = noise->Get(particles[i].position.x*0.001, particles[i].position.y*0.001) * TWO_PI;
		float noiseAngle2  = noise->Get(particles[i].position.x*0.001, particles[i].position.y*0.001) * TWO_PI;
		particles[i].accel += ofxVec3f(cos(noiseAngle), -sin(noiseAngle2), 0) * ((particles[i].position - sourcePoints[particles[i].id]).length()/-100.0f);

    particles[i].addDamping(0.9);

		particles[i].update();
    //particles[i].noise +=
		/* particles[i].velocity *= 0.9;
		float noiseAngle   = noise->Get(particles[i].position.x*0.001, particles[i].position.y*0.001) * TWO_PI;
		float noiseAngle2  = noise->Get(particles[i].position.x*0.001, particles[i].position.y*0.001) * TWO_PI;
    //particles[i].noise += ofxVec3f(noiseAngle, noiseAngle2, 0);
    ofxVec3f noiseForce = ofxVec3f(cos(noiseAngle), -sin(noiseAngle), 0);
		particles[i].noise = noiseForce;
		particles[i].update();*/
	}
}

void ParticleSystem::toggleErase(){
  erase = ! erase;
}



void ParticleSystem::draw(){

	ofSetColor(255,255,255);


  glBegin(GL_POINTS);
	for(int i = 0; i < particles.size(); i++){
		//cout<<"Particle drawing "<<i<<endl;
		particles[i].draw();
	}
	glEnd();
	ofSetColor(255, 0, 0);
	ofCircle(width/2.0, height/2.0, 3.0);


}




