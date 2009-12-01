///=====================================================================================
/// \file ParticleSystem.h
/// \brief 
///
///author Francois Visconte, f.visconte@gmail.com
/// \version $Id$
///
///====================================================================================

#include "ofMain.h"
#include "Particle.h"
#include "ofxVectorMath.h"
#include "perlin.h"

#define FFT_THRESH 0.05f
#define FFT_MULT 5.4f
#define ENABLE_NOISE false
#define NOISE_MULT 2.0f
#define DRAW_REPIELS 1
#define AVERAGE_TRIGGER false
#define MAX_PARTICLES 400
#define PARTICLE_RANDOM_POS false
#define ROTATING_ANGLE false
#define LOW_THRESH 0.25f
#define HIGH_THRESH 0.04f
#define MID_THRESH 0.2f
#define PARTICLE_SIZE_MIN 3
#define PARTICLE_SIZE_MAX 8
#define VELOCITY_DAMP 0.9f
#define ACCEL_DAMP 0.0f

class ParticleSystem{

  
  public:
    vector<Particle> particles; 
    float *fft; 
    float fftSize;
    vector <int>particleToFFT; 
    Perlin *noise;

    ParticleSystem();
    void setup(int nParticles); 
    void update();
    void draw();
    void addRepiel(ofxVec3f r, float value, float radius);
    void toggleErase();
    void setFFT(float *, int); 
    bool particleDeserveToLive(int); 
    void addParticle();

    vector <ofxVec3f> forcesPos; 
    vector <float> forcesVal; 
    vector <float> forcesRad; 
    float mouseX, mouseY; 
    bool erase;
    int width, height; 
    
    float fftMult; 
    float noiseMult;
    float fftThresh;
    bool enableNoise;
    bool averageTrigger;
    int maxParticles;
    bool particleRandomPos;
    bool rotatingAngle; 
    
    float lowThresh;
    float midThresh;
    float highThresh;

    int particleSizeMin;
    int particleSizeMax;

    float velocityDamp;
    float accelDamp;
};
