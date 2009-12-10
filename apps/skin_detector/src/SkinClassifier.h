//-------------------------------------------------------------------------------------
//
// \file SkinClassifier.h
// \brief
//
// \author Francois Visconte <f.visconte@gmail.com>
// http://digitalork.blogspot.com, http://github.com/dopuskh3
//
//------------------------------------------------------------------------------------

#include "ofMain.h"
#include "ofxOpenCv.h"


class skinClassifier {

  public:
    void init(int w, int h);
    void draw(int x, int y);
    void draw(){
      draw(0, 0);
    }
    void setImage(unsigned char *image);

    int width;
    int height;

  private:
    ofxCvColorImage currentImage;
    ofxCvGrayscaleImage skinImage;

};
