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


// Default parameters values
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
#define PARTICLE_VELOCITY_MULT 0.1
#define VELOCITY_DAMP 0.9f
#define ACCEL_DAMP 0.0f
#define DRAW_FFT false
#define AVER_FFT_SPEED false
#define FFT_FLOW_FACTOR 10.0f

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

    // average fft speed
    bool averFFTSpeed;
    // fft multiplier
    float fftMult;
    // noise multiplier
    float noiseMult;

    // noise enabled
    bool enableNoise;

    // trigger fft on average value
    bool averageTrigger;

    // max number of particles
    int maxParticles;

    // start particles at random position
    bool particleRandomPos;

    // particles rotating direction
    bool rotatingAngle;

    // low/mid/high freq threshold
    float lowThresh;
    float midThresh;
    float highThresh;

    // minimum particle size
    int particleSizeMin;
    // maximumm particle size
    int particleSizeMax;
    // particle velocity multiplier
    float particleVelocityMult;

    // velocity damping
    float velocityDamp;
    // accell damping
    float accelDamp;

    float fftFlowFactor;
    // draw fft
    bool drawFFT;
};
