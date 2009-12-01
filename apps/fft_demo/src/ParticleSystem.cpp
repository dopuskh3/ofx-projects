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
void ParticleSystem::setup(int nParticles){
  for(int i=0; i < nParticles; i++){
  //addParticle();
  }  

  mouseX = 0; 
  mouseY = 0;
  erase = 0;
  
  noise = new Perlin(5, 6, 1, time(NULL));  

  fft=NULL;
  fftSize = 0;
  fftMult = FFT_MULT;
  fftThresh = FFT_THRESH;
  enableNoise = ENABLE_NOISE;
  noiseMult = NOISE_MULT;
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

void ParticleSystem::update(){
  int repielValue = 2; 
  float averfft=1.0f; 
  float fftMax = 0.0f;
  
  
  if(fftSize && fft >0){
    for(int i=0; i< fftSize; i++){
      averfft+=fft[i];
      if(fft[i]>fftMax)
        fftMax = fft[i];
    }
    averfft/=fftSize;
    int count = averfft * fftMax * 200;
    for (int j=count; j>=0; j--){
      int i = ofRandom(0, fftSize-1);
      if(fft[i] > averfft && particles.size() < 3*fftSize){
        // addParticle(); 
        Particle p=Particle(width/2, height/2);///2 + ofRandom(-200, 200), height/2 + ofRandom(-200.0, 200.0));
        
        p.alpha = 0.0f;
        p.id = i; 
        p.angle = /*(ofGetFrameNum()%100/100.0f) * TWO_PI*/ + i/(fftSize-1)*TWO_PI;
        //p.angle = ofRandomf() * TWO_PI;
        p.accel = fft[i]*ofxVec3f(cos(p.angle), -sin(p.angle), 0.0f); 
        
        p.update();
        particles.push_back(p);
        //    particles.at(particles.size()-1).id = i; 
      }
    }

  }
         
  // for each particles 
  for(int j=0; j < particles.size(); j++){
    particles[j].accel = 0;
    //particles[j].addDamping();
    
    if(! particleDeserveToLive(j)){
      //cout<<"ERASING"<<endl;
      particles.erase(particles.begin()+j);
      continue;
      //addParticle(); 
    }

    // for each force 
    for(int i=0; i< forcesPos.size(); i++){
        particles[j].addAttractionForce(forcesPos[i], forcesRad[i], forcesVal[i]); 
    }
    
    //---------------------------------------------------- Move Particles with a perlin noise
    if(enableNoise){
      float noiseAngle = noise->Get(particles[j].position.x/width, particles[j].position.y/height) * TWO_PI; 
      float noiseAngle2  = noise->Get(particles[j].position.x/width, particles[j].position.y/height) * TWO_PI; 
      ofxVec3f noiseForce = ofxVec3f(cos(noiseAngle), -sin(noiseAngle2), 0); 
      particles[j].accel += noiseMult * noiseForce;
    }
    
    if (fftSize > 0){
      int fftid=particles[j].id;
      float fftAngle = (float )(fft[fftid]/fftMax)*TWO_PI + particles[j].angle; //+ (1.0f/fftSize)*PI; //4.0f*(PI/2.0f))
      
      // apply force 
      ofxVec2f fftForce = /*averfft + sqrtf(fft[fftid]))*/ ofxVec3f(fft[fftid] * fftMult * cos(fftAngle), fft[fftid] * fftMult * -sin(fftAngle), 0); 
      particles[j].accel += fftForce; // ofRandom(-1, 1); 
      //particles[j].velocity += averfft * 0.01; 
      

      msaColor color; 
      int h = (lroundf(particles[j].id * 360.0f / (float)fftSize)); //+ ofGetFrameNum() )%360; 
      //color.setHSV(h,  MIN(sqrtf(fft[fftid]), 1.0), MIN(sqrtf(averfft), 1.0) ); 
      color.setHSV(h,  MIN(2.0f*fft[fftid], 1.0), MIN(2.0f* averfft, 1.0) ); 
      particles[j].r = color.r; 
      particles[j].g = color.g;
      particles[j].b = color.b;
      particles[j].alpha = 0.5 + 0.5 * fft[fftid];
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




