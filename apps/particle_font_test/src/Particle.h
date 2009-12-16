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
	  ofxVec3f destination;
	ofxVec3f noise;

    Particle(ofxVec3f initial_position, ofxVec3f final_destination);
    void update();
    void draw();
    bool raise;
    

    //---------------------------------------------------- Vars
    int ttl; 
    float vDamping; 
    float aDamping;
    int id;
    float r, g, b, alpha;
    float velocityMultiplier;
     
};

