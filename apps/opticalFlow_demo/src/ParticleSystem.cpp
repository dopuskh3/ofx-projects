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
#include "msaColor.cpp"

ParticleSystem::ParticleSystem(){

 
  height = ofGetHeight(); 
  width = ofGetWidth();



}


//---------------------------------------------------- Setup
// - particles
// - erase flag
//
void ParticleSystem::setup(int nParticles, optFlow *oflow, int w, int h){
  
  height = h;
  width = w;
  flow = oflow;

  for(int i=0; i < nParticles; i++){
    addParticle();
  }  
  mouseX = 0; 
  mouseY = 0;
  erase = 0;
  
  noise = new Perlin(5, 6, 1, time(NULL));  

  fft=NULL;
  fftSize = 0;
}

void ParticleSystem::setFFT(float *fftVector, int size){
  fft=fftVector; 
  fftSize=size; 
}

void setFuzzFactor(float fuzz){
      
}

void ParticleSystem::addRepiel(ofxVec3f center, float fValue, float fRadius){
  forcesPos.push_back(center); 
  forcesVal.push_back(fValue);  
  forcesRad.push_back(fRadius);
}

void ParticleSystem::addParticle(){
      Particle p = Particle(width/2 + ofRandom(-20, 20), height/2 + ofRandom(-20.0, 20.0)); 
      p.id = ofRandom(0, fftSize-1); 
      particles.push_back(p);
}

bool ParticleSystem::particleDeserveToLive(int j){
    if (particles[j].hPos[0].x < 0 || particles[j].hPos[0].y < 0
        || particles[j].hPos[0].x > width || particles[j].hPos[0].y > height
        || particles[j].ttl < 0  ) {
      return false;
    }

  return true;
}

#define FFT_THRESH 0.05f
#define FFT_MULT 5.4f
#define FLOW_MULT 0.3f
#define NOISE_MULT 0.06f
void ParticleSystem::update(){
  
        //Particle p=Particle(width/2, height/2);///2 + ofRandom(-200, 200), height/2 + ofRandom(-200.0, 200.0));
        
        //p.alpha = 0.0f;
        //p.id = i; 
        //p.angle = /*(ofGetFrameNum()%100/100.0f) * TWO_PI*/ + i/(fftSize-1)*TWO_PI;
        //p.angle = ofRandomf() * TWO_PI;
        //p.accel = fft[i]*ofxVec3f(cos(p.angle), -sin(p.angle), 0.0f); 
        
        //p.update();
        //particles.push_back(p);
        //    particles.at(particles.size()-1).id = i; 
      //}
   // }

  //}
  //vector <ofxVec4f> sortedFlow;
  //flow->getNMax(sortedFlow);  
  // for each particles 
  for(int j=0; j < particles.size(); j++){
    particles[j].accel = 0.0;
    //particles[j].addDamping();
     
    if(! particleDeserveToLive(j)){
      //cout<<"ERASING"<<endl;
      particles.erase(particles.begin()+j);
      cout<<"Creating particle"<<endl;
      Particle p=Particle(ofRandom(0, width), ofRandom(0, height));

      //p.velocity.x = sortedFlow[0].z;
      //p.velocity.y = sortedFlow[0].w;
      particles.push_back(p);
      continue;
      //addParticle(); 
    }

    // for each force 
    for(int i=0; i< forcesPos.size(); i++){
        particles[j].addAttractionForce(forcesPos[i], forcesRad[i], forcesVal[i]); 
    }
    
    //---------------------------------------------------- Move Particles with a perlin noise
    float noiseAngle = noise->Get(particles[j].position.x/width, particles[j].position.y/height) * TWO_PI; 
    float noiseAngle2  = noise->Get(particles[j].position.x/width, particles[j].position.y/height) * TWO_PI; 
    ofxVec3f noiseForce = ofxVec3f(cos(noiseAngle), -sin(noiseAngle2), 0);
    particles[j].accel += noiseForce * NOISE_MULT; 
    ofxVec2f f; 

    flow->getFlowAt(particles[j].position.x, particles[j].position.y, f);
    particles[j].accel += ofxVec3f(FLOW_MULT * f.x, FLOW_MULT* f.y, 0); //flow.getFlowAt(particles[j].position.x, flow.getFlowAt(particles[j].position.y, particles[j].accel)

    particles[j].update();
      particles[j].r = ofRandomf();
      particles[j].g = ofRandomf();
      particles[j].b = ofRandomf();
      particles[j].alpha = 0.5;


  }

}

void ParticleSystem::toggleErase(){
 erase = ! erase; 
}



void ParticleSystem::draw(){

#ifdef DRAW_REPIELS
  for(int i=0; i< forcesPos.size(); i++){
    ofCircle(forcesPos[i].x, forcesPos[i].y, forcesRad[i]); 
  }
#endif 
  for(int i=0; i < this->particles.size(); i++)
    this->particles[i].draw();
  ofNoFill(); 
/*
  //; debug
  for(int i =0 ; i < fftSize; i++){
    glColor4f(0.6, 0.6, 0.6, 1.0); 
    ofRect(100+i*5, ofGetHeight()-100, 5,  -(fft[i] * 500));
  }
  ofRect(100, ofGetHeight() - (100.0*FFT_THRESH*500.0f), ofGetWidth()-100, 2); 

  ofLine(100, ofGetHeight() - 100.0 - (FFT_THRESH*500.0f), ofGetWidth()-100.0f,  ofGetHeight() - 100.0f - (FFT_THRESH*500.0f));
*/
}




