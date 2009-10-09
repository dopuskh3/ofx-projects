///=====================================================================================
/// \file bTracket.h
/// \brief 
///
/// \author f.visconte, francois.visconte@milpix.com
/// \version $Id$
///
///====================================================================================

#ifndef _BTRACKER_H_
#define _BTRACKER_H_

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ParticleSystem.h"
#include "bContourFinder.h"


#define ABDIFF_MODE 0
#define LIGHT_MODE  1
#define DARK_MODE   2

class bTracker {

  
  public: 
      ParticleSystem * particleSystem;
      // video grabber 
	  ofVideoGrabber vidGrabber;
      // contour finder 
	  //ofxCvContourFinder contourFinder;
      bContourFinder contourFinder;

      // threshold image
      ofxCvGrayscaleImage threshold;
      ofxCvGrayscaleImage background;
      ofxCvGrayscaleImage grey;
      // source image
	  ofxCvColorImage          source;
      // sizwe
      int height, width, blur, erode, dilate, diffMode;
      // blob var
      int minBlobSize, maxBlobSize, maxBlobs; 
      // thresh value
      int threshValue; 

      
      bTracker(){};
      void setup(int w, int h ); 
      // set background 
      void setBackground(); 
      // process 
      void update(); 
      // set diff mode 
      void setDiffMode(int diffMode); 
      void setThreshold(int t); 
      void draw();
      // Retrieve background image
      ofxCvGrayscaleImage *getBackgroundImage(); 
      // retrieve current image
      ofxCvGrayscaleImage *getThresholdImage(); 
      ofxCvColorImage *getFrameImage(); 

      vector<ofxCvBlob>  &getBlobs();
      vector<ofxCvBlob> &getConvexBlobs();
//      vector<CvSeq *>    convexHulls;

};

#endif
