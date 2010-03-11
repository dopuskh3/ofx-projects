
#include "ofxCvComplexBlob.h"


//------------------------------------------------------------------------------------
ofxCvComplexBlob::ofxCvComplexBlob(CvSeq *point_list) {
    points = point_list;
    bHullModified = true;
    bApproxModified = true;

    approxFactor = 0.005;

    // set points;
    CvSeqReader reader;
    cvStartReadSeq( points, &reader, 0 );

    CvPoint pt;
    // read hull shape points
    for (int j = 0; j < points->total; j++) {
        CV_READ_SEQ_ELEM( pt, reader);
        ofPoints.push_back( ofPoint((float)pt.x, (float)pt.y) );
    }

}


//----------------------------------------------------------------------------------
ofRectangle ofxCvComplexBlob::getBoundingBox(){
  CvRect bb; 
  
  bb = cvBoundingRect(points);
  return ofRectangle(bb.x, bb.y, bb.width, bb.height);
  
}
  
//----------------------------------------------------------------------------------
ofxCvComplexBlob::ofxCvComplexBlob(vector<ofPoint> of_points) {
    // FIXME Generate CvSeq from points list
    CvPoint *pt = new CvPoint();

    for (int i = 0; i < of_points.size(); i++) {
        pt->x = of_points[i].x;
        pt->y = of_points[i].y;

        cvSeqPush(points, pt);
    }

}

//----------------------------------------------------------------------------------
vector<ofPoint> ofxCvComplexBlob::getPoints() {
    return ofPoints;
}

//----------------------------------------------------------------------------------
vector<ofPoint> ofxCvComplexBlob::getHullPoints() {
    if (bHullModified) {
        CvMemStorage *stor = cvCreateMemStorage();
        CvPoint pt;
        vector <ofPoint> cvxShape;

        CvSeqReader reader;

        // 1 compute hull shape'
        convexHull =  cvConvexHull2(points, stor, CV_CLOCKWISE, 1);
        //approxChain = contours;
        cvStartReadSeq( convexHull, &reader, 0 );

        // read hull shape points
        for (int j = 0; j < convexHull->total; j++) {
            CV_READ_SEQ_ELEM( pt, reader);
            //cout<<"Adding "<<(float )pt.x<<" -- "<<(float )pt.y<<endl;
            cvxShape.push_back( ofPoint(pt.x, pt.y));
        }

        cvReleaseMemStorage(&stor);

        ofConvexPoints = cvxShape;

        bHullModified = false;
    }

    return ofConvexPoints;
}

//----------------------------------------------------------------------------------
void ofxCvComplexBlob::setApproxFactor(float approx) {
    approxFactor = approx;
}

//----------------------------------------------------------------------------------
vector<ofPoint> ofxCvComplexBlob::getApproxPoints() {
    // 1 comput approx points
    if (bApproxModified) {
        CvMemStorage *stor = cvCreateMemStorage();
        CvPoint pt;
        vector <ofPoint> cvxShape;
        CvSeqReader reader;

        // 1 compute hull shape'
        approxChain = cvApproxPoly(points, sizeof(CvContour), stor, CV_POLY_APPROX_DP, cvContourPerimeter(points)  * approxFactor, 0);

        //approxChain = contours;
        cvStartReadSeq( approxChain, &reader, 0 );

        // read hull shape points
        for (int j = 0; j < approxChain->total; j++) {
            CV_READ_SEQ_ELEM( pt, reader);
            cvxShape.push_back( ofPoint(pt.x, pt.y));
        }

        cvReleaseMemStorage(&stor);
        ofApproxPoints = cvxShape;
        bApproxModified = false;
    }

    return ofApproxPoints;
}

//---------------------------------------------------------------------
float ofxCvComplexBlob::getArea() {

    return fabs( cvContourArea( points, CV_WHOLE_SEQ) );
}


//----------------------------------------------------------------------
float ofxCvComplexBlob::getPerimeter() {
    return fabs( cvContourPerimeter( points) );
}

void ofxCvComplexBlob::clear() {};
