//-------------------------------------------------------------------------------------
//
// \file tetrisClassifier.h
// \brief
//
// \author Francois Visconte <f.visconte@gmail.com>
// http://digitalork.blogspot.com, http://github.com/dopuskh3
//
//------------------------------------------------------------------------------------

#include "ofxOpenCv.h"
#include "ofMain.h"
#include "cv.h"
#include "cvaux.h"
#include "cxcore.h"
#include "cxtypes.h"
#include "cvtypes.h"
#include "highgui.h"

class TetrisClassifier {

  private:
    int r, g, b;
    float threshold;
    int width, height;

    //ofxCvGrayscaleImage mask;
    IplImage *current;
    IplImage *mask;
    IplImage *stats;

    ofxCvGrayscaleImage omask;

  public:

  //---------------------------------------------------------------
  void init(int w, int h){
    width = w;
    height = h;
    r=0;
    g=0;
    b=255;
    current = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 3);
    stats = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 3);
    mask = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 3);

    omask.allocate(w, h);

  }

  //---------------------------------------------------------------
  void setColor(int r, int g, int b){
    r = r;
    g = g;
    b = b;
    cvSet(mask, cvScalar(b, g, r));
    cvCvtColor(mask, mask, CV_BGR2HSV);

  }

  void setColor(int x, int y){
    uchar *ptr = (uchar *)(current->imageData + current->widthStep * y + x*current->nChannels );
    cvSet(mask, cvScalar(ptr[0], ptr[1]));


  }

  //---------------------------------------------------------------
  void setThreshold(float t){
    threshold = t;
  }

  //---------------------------------------------------------------


  //----------------------------------------------------
  void update(unsigned char *pixels){
    uchar value;
    uchar *ptr;
    uchar *sptr;

    // 1- Update current image
    for ( int x = 0; x < width; x++){
      for ( int y = 0; y < height; y++){
        ptr = (uchar *)(current->imageData + current->widthStep * y + x*current->nChannels );
        sptr = (uchar *)(pixels + 3*(width * y + x) );
        ptr[0] = sptr[2];
        ptr[1] = sptr[1];
        ptr[2] = sptr[0];
      }
    }

    cvSmooth(current, current, 3, 3);
    cvCvtColor( current, current, CV_BGR2HSV );
    cvAbsDiff( mask, current, stats);

    IplImage *om = omask.getCvImage();

    for ( int x = 0 ; x < width; x++){
      for (int y = 0 ; y <height; y++){
           ptr = (uchar *)(stats->imageData + stats->widthStep * y + x*stats->nChannels );
           sptr = (uchar *)(om->imageData + om->widthStep * y + x*om->nChannels);
          sptr[0] = (ptr[0] + ptr[1])/2;
      }
    }

    omask.flagImageChanged();
  }

  //---------------------------------------------------------------
  void draw(){
    omask.draw(0, 0);
    //current.draw(with, 0);
    // Draw mask image
  }
};
