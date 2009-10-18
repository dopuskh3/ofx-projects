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

 
  height = ofGetHeight(); 
  width = ofGetWidth();



}


//---------------------------------------------------- Setup
// - particles
// - erase flag
//
void ParticleSystem::setup(int nParticles){
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
  std::cout<<fRadius<<std::endl;
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

#define FFT_THRESH 0.1f
#define FFT_MULT 50.0f
void ParticleSystem::update(){
  int repielValue = 2; 
  float averfft=1.0f; 
  
  
  if(fftSize && fft >0){
    for (int i=0; i<fftSize; i++){
      if(fft[i]>FFT_THRESH && particles.size() < 250){
        // addParticle(); 
        Particle p=Particle(width/2 + ofRandom(-20, 20), height/2 + ofRandom(-20.0, 20.0));
        p.id = i; 
        particles.push_back(p);
        //    particles.at(particles.size()-1).id = i; 
      }
      averfft += fft[i];
    }

    averfft/=fftSize; 
  }
         
  // for each particles 
  cout<<particles.size()<<endl;
  for(int j=0; j < particles.size(); j++){
    particles[j].accel *=0.2; //.set(0,0,0);
    particles[j].addDamping();
    ofxVec3f mousePos = ofxVec3f(mouseX, mouseY); 
    
    if(! particleDeserveToLive(j)){
      particles.erase(particles.begin()+j);
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

    //particles[j].accel += noiseForce; 
    //---------------------------------------------------- -
    //particles[j].addAttractionForce(mousePos, 100.0f, 2.2f);
    //---------------------------------------------------- Move Particles with fft noise
  
    
    if (fftSize > 0){
      int fftid=particles[j].id;
      // change angle id sign
      //if (fft[fftid] > FFT_THRESH)
      //   particles[j].id -= 2*particles[j].id; 

      // get multiplicator from sign
      //float angleSign=(particles[j].id<0)?-1.0f:1.0f;

      float fftAngle = (fft[fftid]*TWO_PI); 
      // apply force 
      ofxVec3f fftForce = averfft * FFT_MULT * ofxVec3f(cos(fftAngle), -sin(fftAngle), 0); 
      particles[j].accel += fftForce; // + ofRandom(-1, 1); 
      //particles[j].velocity += averfft * 0.01; 
      particles[j].alpha = (fft[fftid] /4)*64 + 192; 
     // if (particles.size() < 500 && averfft>0.02){
     //   addParticle();
     // }
      //particles[j].velocity += averfft; 
      //particles[j].velocity = averfft + sqrt(fft[fftid]) * 5.0; 
    }

    particles[j].update();

  }

 // fft
  if(fft && fftSize > 0){
    //
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
  for(int i=0; i < this->particles.size(); i++)
    this->particles[i].draw();

  // debug
  for(int i =0 ; i < fftSize; i++){
    glColor4f(0.0, 0.0, 0.0, 1.0); 
    ofRect(100+i*5, ofGetHeight()-100, 5,  -(fft[i] * 500));
  }

}




