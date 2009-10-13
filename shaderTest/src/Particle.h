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

#define PARTICLE_TTL 1000

class Particle{
  
  public:
    ofxVec3f position; 
    ofxVec3f velocity;
    ofxVec3f accel; 

    Particle(float x, float y);
    void addForce(ofxVec3f f); 
    void addDamping(); 
    void update();
    void draw();
    bool raise;
    void addAttractionForce(ofxVec3f &f, float radius, float scale);
    void addRepulsionForce(ofxVec3f &f, float radius, float scale);
    

    //---------------------------------------------------- Vars
    int ttl; 
    float fuzz; 
    float fuzzDec; 
    float damping; 
     
};
