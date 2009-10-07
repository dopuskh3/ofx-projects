///=====================================================================================
/// \file bContourFinder.cpp
/// \brief 
///
/// \author f.visconte, francois.visconte@milpix.com
/// \version $Id$
///
///====================================================================================


#include "bContourFinder.h"

int bContourFinder::findConvexHulls(){
  for( int i = 0; i < MIN(nConsidered, (int)cvSeqBlobs.size()); i++){
    std::cout<<"Analyse contour "<<cvSeqBlobs[i]->total<<std::endl;
    CvPoint *arr = (CvPoint *)malloc(cvSeqBlobs[i]->total*sizeof(CvPoint)); 
    cvCvtSeqToArray(this->cvSeqBlobs[i], arr, CV_WHOLE_SEQ); 
    free(arr);
    //CvSeq *hull = cvConvexHull2(arr, 0, CV_CLOCKWISE, 0); 
    //this->convexHulls.push_back(hull); 
  }
}

void bContourFinder::reset(){
  ofxCvContourFinder::reset();
  convexHulls.clear(); 
}
