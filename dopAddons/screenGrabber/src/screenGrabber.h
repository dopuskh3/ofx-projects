//-------------------------------------------------------------------------------------
//
// \file screenGrabber.h
// \brief 
// i
//
// \author Francois Visconte <f.visconte@gmail.com> 
// http://digitalork.blogspot.com, http://github.com/dopuskh3
//
//------------------------------------------------------------------------------------ 

#include "ofMain.h"
#include "ofxThreadedImageSaver.h"

class screenGrabber {

  
  public:
    
    int count;
    int width;
    int height;
    

    void init(int w, int h);
    void init();

    void grab();
};

