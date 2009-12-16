//-------------------------------------------------------------------------------------
//
// \file skinClassifier.cpp
// \brief
//
//
// \author Francois Visconte <f.visconte@gmail.com>
// http://digitalork.blogspot.com, http://github.com/dopuskh3
//
//------------------------------------------------------------------------------------


#include "SkinClassifier.h"
#include "cvaux.hpp"
#define HMIN 0
#define HMAX 50
#define SMIN 0.23
#define SMAX 0.68

void skinClassifier::init(int w, int h){
 //image =  cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 3);
 width = w;
 height = h;
 skinImage.allocate(w, h);
 cimage.allocate(w, h);

 currentImage = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 3);

 cvSkinDetector = new CvAdaptiveSkinDetector(1, CvAdaptiveSkinDetector::MORPHING_METHOD_NONE);

}


void skinClassifier::setImage(unsigned char *image){
  // filter image
  uchar value;
  uchar *ptr;
  uchar *sptr;

  for ( int x = 0; x < width; x++){
    for ( int y = 0; y < height; y++){
      ptr = (uchar *)(currentImage->imageData + currentImage->widthStep * y + x*currentImage->nChannels );
      sptr = (uchar *)(image + 3*(width * y + x) );
      ptr[0] = sptr[2];
      ptr[1] = sptr[1];
      ptr[2] = sptr[0];
    }
  }

  cimage = currentImage;

  IplImage *mask = skinImage.getCvImage();

  cvSkinDetector->process(currentImage, mask);
  for ( int x = 0; x < width; x++){
    for ( int y = 0 ; y < height; y++){
      value = ((uchar *)(mask->imageData + y*mask->widthStep))[x];
      if (value){
        ((uchar *) (mask->imageData + mask->widthStep*y))[x] = 255;
      }
    }
  }
  skinImage.flagImageChanged();

  /*
  unsigned char *pixels;
  unsigned char *outPixels;

  currentImage.setFromPixels(image, width, height);
  currentImage.convertRgbToHsv();
  IplImage *inImage = currentImage.getCvImage();
  IplImage *outImage = skinImage.getCvImage();


  for(int x = 0; x < width; x++){
    for(int y = 0; y < height; y++){
      char h = CV_IMAGE_ELEM(inImage, uchar, y, pixels[x*3]);
      char s = CV_IMAGE_ELEM(inImage, uchar, y, pixels[x*3+1]);
      char v = CV_IMAGE_ELEM(inImage, uchar, y, pixels[x*3+2]);
      if ( h >= HMIN/2 && h <HMAX/2 && s > SMIN * 255 && s < SMAX * 255){
       ((uchar *)(outImage->imageData + (outImage->widthStep * y)))[x] = 1;
       } else {
       ((uchar *)(outImage->imageData + (outImage->widthStep * y)))[x] = 0;
      }
    }
    //skinImage.setFromPixels(outPixels, width, height);
  }
  */


}

void skinClassifier::draw(int x, int y){
 // convert image to of cv image
 // draw image
 cimage.draw(0, 0);
 skinImage.draw(x, y);

}
