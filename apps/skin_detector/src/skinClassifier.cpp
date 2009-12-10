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

#define HMIN 0
#define HMAX 50
#define SMIN 0.23
#define SMAX 0.68

void skinClassifier::init(int w, int h){
 //image =  cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 3);
 width = w;
 height = h;
 currentImage.allocate(w, h);
 skinImage.allocate(w, h);
}


void skinClassifier::setImage(unsigned char *image){
  // filter image
  unsigned char *pixels;
  unsigned char *outPixels;

  currentImage.setFromPixels(image, width, height);
  currentImage.convertRgbToHsv();
  pixels = currentImage.getPixels();

  outPixels = skinImage.getPixels();

  for(int i = 0; i < width*height; i++){
    char h = pixels[i*3];
    char s = pixels[i*3+1];
    char v = pixels[i*3+2];
    if ( h >= HMIN/2 && h <HMAX/2 && s > SMIN * 255 && s < SMAX * 255){
      outPixels[i] = 1;
    } else {
      outPixels[i] = 0;
    }
    skinImage.setFromPixels(outPixels, width, height);
  }

}

void skinClassifier::draw(int x, int y){
 // convert image to of cv image
 // draw image

 skinImage.draw(x, y);

}
