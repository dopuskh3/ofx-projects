///=====================================================================================
/// \file bContourFinder.cpp
/// \brief 
///
///author Francois Visconte, f.visconte@gmail.com
/// \version $Id$
///
///====================================================================================


#include "bContourFinder.h"

void bContourFinder::findConvexHulls(){
  CvMemStorage *stor = cvCreateMemStorage(); 
  CvSeq * ptseq = cvCreateSeq( CV_SEQ_KIND_CURVE|CV_32SC2,
                                    sizeof(CvContour),
                                    sizeof(CvPoint),
                                    stor );
  CvSeq * hull; 
  CvPoint pt; 
  this->convexBlobs.clear();
  for(int i = 0 ; i < this->blobs.size(); i++){
    this->convexBlobs.push_back(ofxCvBlob());
    this->convexBlobs[i] = this->blobs[i];
    this->convexBlobs[i].pts.clear(); 
    // get blob i
    for(int j = 0; j < this->blobs[i].pts.size(); j++){
      // fill in blob points 
      pt.x = this->blobs[i].pts[j].x; 
      pt.y = this->blobs[i].pts[j].y; 
      cvSeqPush( ptseq, &pt); 
    }
    hull = cvConvexHull2(ptseq, 0, CV_CLOCKWISE, 0); 
    
    // get the points for the blob:
    CvPoint           pt  = **CV_GET_SEQ_ELEM( CvPoint*, hull, hull->total - 1 );
    for( int j=0; j < hull->total; j++ ) {
      pt = **CV_GET_SEQ_ELEM( CvPoint*, hull, j );
      convexBlobs[i].pts.push_back( ofPoint((float)pt.x, (float)pt.y) );
    }
    convexBlobs[i].nPts = convexBlobs[i].pts.size();
  }
  cvClearMemStorage( stor ); 
}
/*
void smoothApproxChains(int smoothMod, float value){
  CvMemStorage *stor = cvCreateMemStorage(); 
  CvSeq * ptseq = cvCreateSeq( CV_SEQ_KIND_CURVE|CV_32SC2,
                                    sizeof(CvContour),
                                    sizeof(CvPoint),
                                    stor );
  CvSeq * hull; 
  CvPoint pt; 
  for(int i = 0 ; i < this->blobs.size(); i++){
    for(int j = 0; j < this->blobs[i].pts.size(); j++){
      // fill in blob points 
      pt.x = this->blobs[i].pts[j].x; 
      pt.y = this->blobs[i].pts[j].y; 
      cvSeqPush( ptseq, &pt); 
    }
    cvApproxChains(ptseq, stor,  

  }
   
  
}*/

void bContourFinder::draw( float x, float y, float w, float h ){
  ofxCvContourFinder::draw(x, y, w, h);
  
  for(int i = 0; i < this->convexBlobs.size(); i++)
    convexBlobs[i].draw(x, y);
} 

void bContourFinder::reset(){
  ofxCvContourFinder::reset();
  convexBlobs.clear();
}
