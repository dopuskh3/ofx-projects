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

void bContourFinder::smoothApproxChains(){ //int smoothMod, float value){
  CvMemStorage *stor = cvCreateMemStorage(); 
  CvSeq * ptseq = cvCreateSeq( CV_SEQ_KIND_CURVE  | CV_SEQ_ELTYPE_POINT,
                                    sizeof(CvSeq),
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
  

    hull = cvApproxPoly(ptseq, sizeof(CvContour), stor,
        CV_POLY_APPROX_DP, cvContourPerimeter(ptseq)*0.004, 0);

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

void bContourFinder::draw( float x, float y, float w, float h ){
  ofxCvContourFinder::draw(x, y, w, h);
   float scalex = 0.0f;
    float scaley = 0.0f;
    if( _width != 0 ) { scalex = w/_width; } else { scalex = 1.0f; }
    if( _height != 0 ) { scaley = h/_height; } else { scaley = 1.0f; }


  ofSetColor(0x00FFFF);

	// ---------------------------- draw the bounding rectangle
	ofSetColor(0xDD00CC);
    glPushMatrix();
    glTranslatef( x, y, 0.0 );
    glScalef( scalex, scaley, 0.0 );

	ofNoFill();
	// ---------------------------- draw the blobs
	ofSetColor(0x00FFFF);

	for( int i=0; i<(int)convexBlobs.size(); i++ ) {
		ofNoFill();
		ofBeginShape();
		convexBlobs[i].draw();
        ofEndShape();

	}
	glPopMatrix();
} 

void bContourFinder::reset(){
  ofxCvContourFinder::reset();
  convexBlobs.clear();
}
