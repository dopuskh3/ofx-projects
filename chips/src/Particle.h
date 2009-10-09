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

class Particle{
  
  public:
    ofPoint position; 
    ofPoint velocity;
    ofPoint accel; 

    Particle(float x, float y);
    void update();
    void draw();
};

