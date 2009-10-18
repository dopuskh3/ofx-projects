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

#define DRAW_REPIELS 1
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
};
