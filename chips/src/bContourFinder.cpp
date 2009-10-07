///=====================================================================================
/// \file bContourFinder.cpp
/// \brief 
///
/// \author f.visconte, francois.visconte@milpix.com
/// \version $Id$
///
///====================================================================================


#include "bContourFinder.h"

int bContourFinder::findConvexHulls(ofxCvGrayscaleImage&  input,
									  int minArea,
									  int maxArea,
									  int nConsidered,
									  bool bFindHoles,
                                      bool bUseApproximation){

    vector <CvSeq *> blobsSeqVec; 

   // get width/height disregarding ROI
    IplImage* ipltemp = input.getCvImage();
    _width = ipltemp->width;
    _height = ipltemp->height;


	// opencv will clober the image it detects contours on, so we want to
    // copy it into a copy before we detect contours.  That copy is allocated
    // if necessary (necessary = (a) not allocated or (b) wrong size)
	// so be careful if you pass in different sized images to "findContours"
	// there is a performance penalty, but we think there is not a memory leak
    // to worry about better to create mutiple contour finders for different
    // sizes, ie, if you are finding contours in a 640x480 image but also a
    // 320x240 image better to make two ofxCvContourFinder objects then to use
    // one, because you will get penalized less.

	if( inputCopy.getWidth() == 0 ) {
		inputCopy.allocate( _width, _height );
	} else if( inputCopy.getWidth() != _width || inputCopy.getHeight() != _height ) {
        // reallocate to new size
        inputCopy.clear();
        inputCopy.allocate( _width, _height );
	}

    inputCopy = input;
    inputCopy.setROI( input.getROI() );

	CvSeq* contour_list = NULL;
	contour_storage = cvCreateMemStorage( 1000 );
	storage	= cvCreateMemStorage( 1000 );

	CvContourRetrievalMode  retrieve_mode  = (bFindHoles) ? CV_RETR_LIST : CV_RETR_EXTERNAL;

	cvFindContours( inputCopy.getCvImage(), contour_storage, &contour_list,
                    sizeof(CvContour), retrieve_mode, bUseApproximation ? CV_CHAIN_APPROX_SIMPLE : CV_CHAIN_APPROX_NONE );

	CvSeq* contour_ptr = contour_list;

	// put the contours from the linked list, into an array for sorting
	while( (contour_ptr != NULL) ) {
		float area = fabs( cvContourArea(contour_ptr, CV_WHOLE_SEQ) );
		if( (area > minArea) && (area < maxArea) ) {
            blobsSeqVec.push_back(contour_ptr);
		}
		contour_ptr = contour_ptr->h_next;
	}

    hulls.clear();
    for(int i = 0; i < blobsSeqVec.size(); i++){
      CvSeq *hull = cvConvexHull2(blobsSeqVec[i], 0, CV_CLOCKWISE, 0); 
      bHullShape hs;
      for (int j = 0; j < hull->total; j++){
        CvPoint *p = *CV_GET_SEQ_ELEM(CvPoint *, hull, j); 
        hs.push_back(ofPoint(p->x, p->y));
      }
      hulls.push_back(hs);
      std::cout<<"Hull size = "<<hull->total<<std::endl;

    }

	// Free the storage memory.
	// Warning: do this inside this function otherwise a strange memory leak
	if( contour_storage != NULL ) { cvReleaseMemStorage(&contour_storage); }
	if( storage != NULL ) { cvReleaseMemStorage(&storage); }
    return 0;

}


void bContourFinder::reset(){
  ofxCvContourFinder::reset();
  convexHulls.clear(); 
}
