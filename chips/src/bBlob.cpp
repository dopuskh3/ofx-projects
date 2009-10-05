///=====================================================================================
/// \file bBlob.cpp
/// \brief 
///
/// \author f.visconte, francois.visconte@milpix.com
/// \version $Id$
///
///====================================================================================


#include "bBlob.h"

bBlob::bBlob(const ofxCvBlob &A){
  area            = A.area;
  length          = A.length;
  boundingRect    = A.boundingRect;
  centroid        = A.centroid;
  hole            = A.hole;
  nPts            = A.nPts;
  threshold       = 3;


  pts.clear();
      pts.assign(nPts, ofPoint());


  for(int i = 0; i < nPts; i++){
    pts[i] = A.pts[i];
  }

  // process smoothing 
  //
}

#define pnorm(p) sqrt((p.x*p.x + p.y*p.y + p.z*p.z))
bool bBlob::getPointProx(const ofPoint &point){
  // get min point distance 
  for(int i = 0; i < nPts; i++){
    ofPoint d = pts[i]; 
    d -= point; 
    int norm = pnorm(d);
    if (norm < threshold){ 
      return true;
    }
  }
  return false;

}


