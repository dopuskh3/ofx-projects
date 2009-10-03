///=====================================================================================
/// \file bWorld.cpp
/// \brief 
///
/// \author f.visconte, francois.visconte@milpix.com
/// \version $Id$
///
///====================================================================================



#include "bWorld.h"


//------------------------------------------------------------------------- 
bWorld::bWorld(){
  
    

}




//------------------------------------------------------------------------- 
void bWorld::createWorld(){
  box2d.init(); 
  box2d.setGravity(10, 0);
  box2d.createFloor();
  box2d.checkBounds(true);
  box2d.setFPS(30.0);

  poly.init(box2d.getWorld(), ofGetWidth()/2, ofGetHeight()/2); 

}

void bWorld::shapeFromBlobs(vector<ofxCvBlob>  *blobs){

  ofSetColor(0,0,255);
  int size = (blobs->size())>=1?1:0; 
  int prevx, prevy;

  for(int i=0; i < size; i++){
    // reusable 
    ofBeginShape();
    poly.vertices.erase(poly.vertices.begin(), poly.vertices.end()); 
    for(int j = 0; j< (*blobs)[i].nPts; j+=20){
      if (prevx< (*blobs)[i].pts[j].x && prevy < (*blobs)[i].pts[j].y ){
        poly.addVertex((*blobs)[i].pts[j].x, (*blobs)[i].pts[j].y); 
        std::cout<<"Added vertex"<<std::endl;
      }

      std::cout<<"size="<<poly.vertices.size()<<std::endl;
      prevx = (*blobs)[i].pts[j].x;
      prevy = (*blobs)[i].pts[j].y;
      ofVertex((*blobs)[i].pts[j].x, (*blobs)[i].pts[j].y); 
    } 
    poly.validateShape(); 
    ofEndShape(); 
  }
  box2d.update(); 
}
