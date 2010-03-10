/*

 FIXME:
   - add convexity deffects use

   
*/

#ifndef OFXCVCOMPLEXBLOB_H
#define OFXCVCOMPLEXBLOB_H

#include "ofxOpenCv.h"


class ofxCvComplexBlob
{
  
    private:
    
    bool bApproxModified;
    bool bHullModified; 
 
  public:
    CvSeq *points; 
    vector<ofPoint> ofPoints;
    
    CvSeq *convexHull;
    vector<ofPoint> ofConvexPoints;
    
    CvSeq *approxChain;
    vector<ofPoint> ofApproxPoints;
    
    float approxFactor; 
    
    
    #define BLOB_AREA_APPROX 1
    #define BLOB_AREA 2
    #define BLOB_AREA_HULL 3
    
   //------------------------------------------------------------------------------------
    ofxCvComplexBlob(CvSeq *point_list);
    ofxCvComplexBlob(vector<ofPoint> of_points);
    vector<ofPoint> getPoints();
    vector<ofPoint> getHullPoints();
    void setApproxFactor(float approx);
    vector<ofPoint> getApproxPoints();
    float getArea();
    float getPerimeter();
    void clear();
  
};

#endif // OFXCVCOMPLEXBLOB_H
