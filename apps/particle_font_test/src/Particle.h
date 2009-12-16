//-------------------------------------------------------------------------------------
//
// \file Particle.h
// \brief
//
// \author Francois Visconte <f.visconte@gmail.com>
// http://digitalork.blogspot.com, http://github.com/dopuskh3
//
//------------------------------------------------------------------------------------



#include "ofMain.h"
#include "ofxVectorMath.h"

//---------------------------------------------------- -
#include <deque>

#define PARTICLE_TTL 1000
#define VELOCITY_MULTIPLIER 0.1

class Particle{

  public:
    ofxVec3f position;
    ofxVec3f velocity;
    ofxVec3f accel;


    Particle(ofxVec3f initial_position, float timeStep);
    void update();
    void draw();
    bool raise;
    void addDamping(float damping = 0.01f);
    void resetForce();
    void addForce(ofxVec3f force, float radius, float scale);


    //---------------------------------------------------- Vars
    int ttl;
    int id;
    float timeStep;
};

