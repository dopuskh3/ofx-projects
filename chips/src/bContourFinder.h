///=====================================================================================
/// \file bContourFinder.h
/// \brief 
///
/// \author f.visconte, francois.visconte@milpix.com
/// \version $Id$
///
///====================================================================================

#include "ofxOpenCv.h"


class bContourFinder : public ofxCvContourFinder {
  
  public: 

    //vector<ofxCvBlob>  blobs;
    //int                nBlobs;    // DEPRECATED: use blobs.size() instead
 

    bContourFinder() : ofxCvContourFinder() {}; 
    
    virtual int  findContours( ofxCvGrayscaleImage& input,
                               int minarea, int maxarea,
                               int nconsidered, bool bfindholes,
                               bool buseapproximation = true){
        int i = ofxCvContourFinder::findContours(input, minarea, maxarea, nconsidered, bfindholes, buseapproximation);
        findConvexHulls(); 
        return i;

    }
                               // approximation = don't do points for all points 
                               // of the contour, if the contour runs
                               // along a straight line, for example...


    virtual void  draw() { draw(0,0, _width, _height); };
    virtual void  draw( float x, float y ) { draw(x,y, _width, _height); };
    virtual void  draw( float x, float y, float w, float h ){ ofxCvContourFinder::draw(x, y, w, h);  }; 
	virtual void setAnchorPercent(float xPct, float yPct){ ofxCvContourFinder::setAnchorPercent(xPct, yPct); }
    virtual void setAnchorPoint(int x, int y) { ofxCvContourFinder::setAnchorPoint(x, y); };
	virtual void resetAnchor(){ofxCvContourFinder::resetAnchor(); };      
    
    void reset();
    
    int findConvexHulls();    
    vector <CvSeq *> convexHulls;

};

