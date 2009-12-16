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


class ParticleSystem{


  public:
    vector<Particle> particles;
  	vector<ofxVec3f> destination;
    vector<ofxVec3f> sourcePoints;
    Perlin *noise;
    float timeStep;
    float steps;

    ParticleSystem();
    void setup(int nParticles, int width, int height);
    void update();
    void draw();
    void toggleErase();
    bool particleDeserveToLive(int);
    void addParticle();
    void addSourcePoint(float x, float y);

    bool erase;
	  int height, width;

};
