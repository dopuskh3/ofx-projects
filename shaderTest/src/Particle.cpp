//-------------------------------------------------------------------------------------
//
// \file Particle.cpp
// \brief 
//
// \author Francois Visconte <f.visconte@gmail.com>
// http://digitalork.blogspot.com, http://github.com/dopuskh3
//
//------------------------------------------------------------------------------------ 



#include "Particle.h"

Particle::Particle(float x, float y){

  this->position = ofxVec3f(x,y); 
  this->velocity = ofxVec3f(0, 0);
  this->accel   = ofxVec3f(0, 0); 
  ttl = PARTICLE_TTL; 
  damping = 0.01f;
  fuzz = 0.0;
  numH = 50; 

  r = (int)ofRandom(40, 60);
  g = (int)ofRandom(10, 30);
  b = (int)ofRandom(0, 10);

  alpha = 0;


}

// ---------------------------------------------------- 
void Particle::update(){

  //ttl--; 

    if(numH > 0){
    hPos.push_back(position); 
    hVel.push_back(velocity); 
    hAc.push_back(accel); 
    if(hPos.size() >= numH){
      hPos.pop_front(); 
      hVel.pop_front();
      hAc.pop_front(); 
    }
  }
  velocity += accel; 
  position += velocity;




  //if(fuzz != 0){
  //  ofxVect3f fuzz; 
  //  fuzz.x  = ofRandom(0, 100); 
  //  fuzz.y  = ofRandom(0, 100); 
  //  fuzz.normalize(fuzz); 
  //}
}

//---------------------------------------------------- 
void Particle::addDamping(){
 accel = accel - velocity * damping; 
}

//----------------------------------------------------
void Particle::addForce(ofxVec3f f){
  //std::cout<<f.length()<<std::endl;
  //float oldlen = velocity.length();  
  accel += f; 
  //velocity.scale(oldlen);
}

//---------------------------------------------------- 
void Particle::addAttractionForce(ofxVec3f &fpos, float radius, float scale){

  ofxVec3f diff = position - fpos; 
  float len = diff.length(); 

  if ( radius > 0 && len < radius){
    float pct = 1 - (len / radius); 
    diff.normalize(); 
    accel -= diff * scale * pct; 
  }

}

//---------------------------------------------------- 
void Particle::addRepulsionForce(ofxVec3f &pos, float radius, float scale){
  addAttractionForce(pos, radius, 0-scale); 
}


//---------------------------------------------------- 
void Particle::draw(){
  //if(!raise)
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    vector<ofxVec3f> tmp; 


	glBegin(GL_QUAD_STRIP);
    for(int i=0 ; i < hPos.size(); i++){
      float l = hVel[i].length();
      float angle = atan2(hVel[i].y, hVel[i].x); 
      float ofx = sin(angle)*l*0.2; 
      float ofy = cos(angle)*l*0.2; 

      ofSetColor(r, g, b, alpha);
      glVertex3f(hPos[i].x+ofx, hPos[i].y+ofy , 0.0f); 
      glVertex3f(hPos[i].x-ofx, hPos[i].y-ofy , 0.0f); 
      tmp.push_back(ofxVec3f(ofx, ofy , 0.0f)); 
    }
	glEnd();
    

    glBegin(GL_LINE_STRIP); 
    for (int i =0 ; i < tmp.size(); i++){
      glVertex3f(hPos[i].x+tmp[i].x, hPos[i].y+tmp[i].y, 0); // hPos[i].z + tmp[i].z); 
    }
    for (int i=tmp.size()-1; i >= 0; i--){
      glVertex3f(hPos[i].x-tmp[i].x, hPos[i].y-tmp[i].y, 0); // hPos[i].z - tmp[i].z); 
    }
    glEnd(); 

	//glVertex3f(position.x-(velocity.x)+2, position.y-velocity.y+2,0.0f);
	//glVertex3f(position.x-(velocity.x)-2, position.y-velocity.y-2,0.0f);
	//glVertex3f(position.x+2, position.y+2,0.0f);
	//glVertex3f(position.x-2, position.y-2, 0.0f);
	
//  ofCircle(this->position.x, this->position.y, 5);
  //glBegin(GL_POINTS);
  //glVertex3f(position.x, position.y, position.z);
  //glEnd( );
}
