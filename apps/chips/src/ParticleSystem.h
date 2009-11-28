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
#include "bBlob.h"

class ParticleSystem{

  
  public:
    vector<Particle> particles; 

    ParticleSystem(int nParticles);
    void update();
    void draw();
    void checkBlob(bBlob *b); 
};
