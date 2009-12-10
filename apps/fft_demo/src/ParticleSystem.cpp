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

  noise = new Perlin(5, 10, 1.0f, time(NULL));



  // intialize fft
  fft=NULL;
  fftSize = 0;


  // intialize default configuartion
  fftMult = FFT_MULT;
  averFFTSpeed = AVER_FFT_SPEED;
  enableNoise = ENABLE_NOISE;
  noiseMult = NOISE_MULT;
  averageTrigger = AVERAGE_TRIGGER;
  maxParticles = MAX_PARTICLES;
  particleRandomPos = PARTICLE_RANDOM_POS;
  rotatingAngle = ROTATING_ANGLE;
  lowThresh = LOW_THRESH;
  midThresh = MID_THRESH;
  highThresh = HIGH_THRESH;
  particleSizeMin = PARTICLE_SIZE_MIN;
  particleSizeMax = PARTICLE_SIZE_MAX;
  particleVelocityMult = PARTICLE_VELOCITY_MULT;
  velocityDamp = VELOCITY_DAMP;
  accelDamp = ACCEL_DAMP;
  drawFFT = DRAW_FFT;
  fftFlowFactor = FFT_FLOW_FACTOR;
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
  Particle p = Particle(width/2 + ofRandom(-20, 20), height/2 + ofRandom(-20.0, 20.0), particleSizeMin, particleSizeMax);
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
  float trigger;


  // fft is uninitialized
  if(!fftSize || !fft)
   return ;

  // compute fft average value and maximum
  for(int i=0; i< fftSize; i++){  averfft+=fft[i];
    if(fft[i]>fftMax)
      fftMax = fft[i];
  }
  averfft/=fftSize;

  int x, y;// -----
  if (particles.size() > maxParticles & fftFlowFactor > 0){
    fftFlowFactor-=0.1;
  }
  if (particles.size() < maxParticles ) {
    fftFlowFactor+=0.1; 
  } 
  for(int k = fftSize; k >0 ; --k){
      int i = ofRandom(0, fftSize);
      float factor = fftFlowFactor * cbrtf(fft[i]*(float)(i+1)/20.0); 
      //factor = sqrtf(factor);
      int numPart = factor * fft[i];

      for(int j=0; j< numPart; j++){
        float angle;
        if (rotatingAngle){
          angle = ofGetFrameNum()%100;
        } else{
          angle = 0;
        }
        if(particleRandomPos){
          x = ofRandom(0, width);
          y = ofRandom(0, height);
        } else {
          x = width/2;
          y = height/2;
        }
        Particle p=Particle(x, y, particleSizeMin, particleSizeMax);
        p.alpha = 0.0f;
        p.id = i;
        p.velocityMultiplier = particleVelocityMult;
        p.angle = angle  +  i/(fftSize-1)*TWO_PI;
        p.update();
        particles.push_back(p);
      }
  }

  // FIXME: rewrite this
  // number of particles to add
  /*int count = fftSize; // averfft * fftMax * 2000;
  while ( count >= 0){
    int i = ofRandom(0, fftSize-1);
    // apply correct threshold depending on frequency
    if ( i < fftSize/3 && ! averageTrigger ){
      trigger = lowThresh;
    } else if(i >= fftSize/3 && i < 2*(fftSize/3) && ! averageTrigger){
      trigger = midThresh;
    } else if( ! averageTrigger ){
      trigger = highThresh;
    } else { // then averfft trigger enabled
      trigger = averfft;
    }
    count--;
    // if fft value and not reaching max paticles number
    if(fft[i] > trigger && particles.size() < maxParticles){
      //cout<<fft[i]*10<<endl;
      for(float cnt = 0.0f; cnt < fft[i] * 10.0f ; cnt+=0.1f){
      //cout<<count<<endl;
      //count--;
      // add new particle
      int x = width/2;
      int y = height/2;
      float angle;
      if (rotatingAngle){
        angle = ofGetFrameNum()%100;
      } else{
        angle = 0;
      }
      if(particleRandomPos){
        x = ofRandom(0, width);
        y = ofRandom(0, height);
      } else {

      }
      Particle p=Particle(x, y, particleSizeMin, particleSizeMax);
      p.alpha = 0.0f;
      p.id = i;
      p.velocityMultiplier = particleVelocityMult;
      p.angle = angle  +  i/(fftSize-1)*TWO_PI;
      p.update();
      particles.push_back(p);
      }
    }
  }*/

  // for each particles
  for(int j=0; j < particles.size(); j++){
    particles[j].accel *= accelDamp;
    particles[j].velocity *= velocityDamp;
    //particles[j].addDamping();

    if(! particleDeserveToLive(j)){
      //cout<<"ERASING"<<endl;
      particles.erase(particles.begin()+j);
      continue;
      //addParticle();
    }

    //---------------------------------------------------- Move Particles with a perlin noise
    if(enableNoise){
      float noiseAngle = noise->Get(particles[j].position.x, particles[j].position.y) * TWO_PI;
      float noiseAngle2  = noise->Get(particles[j].position.x, particles[j].position.y) * TWO_PI;
      ofxVec3f noiseForce = ofxVec3f(cos(noiseAngle), -sin(noiseAngle2), 0);
      particles[j].accel += noiseMult * noiseForce;
    }

    int fftid=particles[j].id;
    float sign=(ofRandom(0,1))?-1.0f:1.0f;
    float fftAngle = sign * ((float )(fft[fftid]/fftMax)*PI + particles[j].angle);

    // apply force
    ofxVec2f fftForce;

    if( averFFTSpeed)
      fftForce = ofxVec3f(averfft * fftMult * cos(fftAngle), averfft * fftMult * sin(fftAngle), 0);
    else
      fftForce = ofxVec3f(sqrt(fft[fftid]) * averfft * fftMult * cos(fftAngle), averfft * sqrt(fft[fftid]) * fftMult * sin(fftAngle), 0);

    particles[j].accel += fftForce;

    // set particle color
    msaColor color;
    int h = (lroundf(particles[j].id * 360.0f / (float)fftSize));
    color.setHSV(h,  MIN(2.0f*fft[fftid], 1.0), MIN(2.0f* averfft, 1.0) );
    particles[j].r = color.r;
    particles[j].g = color.g;
    particles[j].b = color.b;
    particles[j].alpha = 0.5 + 0.5 * fft[fftid];
    particles[j].update();
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

  if(drawFFT){
    for(int i =0 ; i < fftSize; i++){
      glColor4f(0.6, 0.6, 0.6, 1.0);
      ofRect(100+i*5, ofGetHeight()-100, 5,  -(fft[i] * 500));
    }
    ofRect(100, ofGetHeight() - (100.0*FFT_THRESH*500.0f), ofGetWidth()-100, 2);
    ofLine(100, ofGetHeight() - 100.0 - (FFT_THRESH*500.0f), ofGetWidth()-100.0f,  ofGetHeight() - 100.0f - (FFT_THRESH*500.0f));
  }
}




