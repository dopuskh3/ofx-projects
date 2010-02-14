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
    ofxCvGrayscaleImage mask;
    IplImage *current; 
    IplImage *current_hsv;
    IplImage *tpl_image;
    IplImage *output;
    ofxCvGrayscaleImage stats;
    int dtype;
    CvHistogram *hist;

  public:

  //---------------------------------------------------------------
  void init(int w, int h){
    width = w; 
    height = h;
 
    mask.allocate(w, h);
    current = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 3);
    current_hsv = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 3);
    tpl_image = cvLoadImage("template.jpg");
    cvCvtColor( tpl_image, tpl_image, CV_BGR2HSV );

    int ow, oh; 
    ow =  current->width - tpl_image->width + 1; 
    oh = current->height - tpl_image->height + 1;  
    output = cvCreateImage( cvSize( ow, oh ), IPL_DEPTH_8U, 1 ); 

    stats.allocate(ow, oh);
    dtype = CV_TM_CCOEFF_NORMED;

  }

  //---------------------------------------------------------------
  void setColor(int r, int g, int b){
    r = r; 
    g = g;
    b = b;
  }

  //---------------------------------------------------------------
  void setThreshold(float t){
    threshold = t; 
  }

  //---------------------------------------------------------------
  
  void compute_histogram(){

    
    IplImage* h_plane = cvCreateImage( cvGetSize( tpl_image ), 8, 1 );
    IplImage* s_plane = cvCreateImage( cvGetSize( tpl_image ), 8, 1 );
    IplImage* v_plane = cvCreateImage( cvGetSize( tpl_image ), 8, 1 );
    IplImage* planes[] = { h_plane, s_plane };
    cvCvtPixToPlane( tpl_image, h_plane, s_plane, v_plane, 0 );

    // Build and fill the histogram
    int h_bins = 30, s_bins = 32;
      int hist_size[] = { h_bins, s_bins };
      float h_ranges[] = { 0, 180 };
      float s_ranges[] = { 0, 255 };
      float* ranges[] = { h_ranges, s_ranges };
      hist = cvCreateHist( 2, hist_size,
          CV_HIST_ARRAY, ranges, 1 );
    cvCalcHist( planes, hist, 0, 0 ); //
    cvNormalizeHist( hist, 20*255 ); //

  }

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

    cvCvtColor( current, current_hsv, CV_BGR2HSV );
  

    //cvMatchTemplate(current,tpl_image,  output, dtype);
    //cvNormalize( output, output, 1, 0, CV_MINMAX);
    cvCalcBackProject( planes, stats.getCvImage(), hist );

    cvConvertScale(output, stats.getCvImage(), 256);
    stats.flagImageChanged();

    //stats = output;

    

    // 2- Apply substraction with reference color
    // 3- Apply abs(MASK) 
    // 4- Apply Threshold. 
    // 5- Apply Blob detection
  }

  //---------------------------------------------------------------
  void draw(){
    stats.draw(0, 0);
    //current.draw(with, 0);
    // Draw mask image
  }
};
