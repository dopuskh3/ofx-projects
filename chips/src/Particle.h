///=====================================================================================
/// \file Particle.h
/// \brief 
///
/// \author f.visconte, francois.visconte@milpix.com
/// \version $Id$
///
///====================================================================================

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

