///=====================================================================================
/// \file bBlob.h
/// \brief 
///
/// \author f.visconte, francois.visconte@milpix.com
/// \version $Id$
///
///====================================================================================

#ifndef _BBLOB_H_
#define _BBLOB_H_
#include "ofxOpenCv.h"

#define PROX_TRESHOLD 3


class bBlob : public ofxCvBlob {
  
  public:
    bBlob(const ofxCvBlob &A);
    bool getPointProx(const ofPoint &point);
    
    void operator = (const ofxCvBlob &A){
      //

      area            = A.area;
      length          = A.length;
      boundingRect    = A.boundingRect;
      centroid        = A.centroid;
      hole            = A.hole;
      nPts            = A.nPts;

      pts.clear();
      pts.assign(nPts, ofPoint());

      for(int i = 0; i < nPts; i++){
        pts[i] = A.pts[i];
      }
    }
    int threshold;
};
#endif
