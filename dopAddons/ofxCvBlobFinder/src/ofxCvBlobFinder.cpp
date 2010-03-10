
#ifndef OFXCVBLOBFINDER_H
#define OFXCVBLOBFINDER_H

#include "ofxCvBlobFinder.h"

//----------------------------------------------------------------------------------
ofxCvBlobFinder::ofxCvBlobFinder()
{
    approxFactor = 0.005;
}
//----------------------------------------------------------------------------------
void ofxCvBlobFinder::findBlobs(ofxCvGrayscaleImage image) {

    CvMemStorage *stor = cvCreateMemStorage();
    IplImage *img = image.getCvImage();
    CvSeq *contours;

    // CV_RETR_EXTERNAL to not find holes
    cvFindContours(img, stor, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);


    blobz.clear();
    while (contours) {
        ofxCvComplexBlob b =  ofxCvComplexBlob(contours);
        b.setApproxFactor(approxFactor);
        b.getApproxPoints();
        b.getHullPoints();

        blobz.push_back( b );

        contours = contours->h_next;
    }
}
//----------------------------------------------------------------------------------
void ofxCvBlobFinder::draw(float x, float y, float w, float h) {

    // draw blobs
    //ofxCvContourFinder::draw(x, y, w, h);
    // scale blob
    float scalex = 0.0f;
    float scaley = 0.0f;

    if (_width != 0) {
        scalex = w / _width;
    }
    else {
        scalex = 1.0f;
    }

    if (_height != 0) {
        scaley = h / _height;
    }
    else {
        scaley = 1.0f;
    }


    ofSetPolyMode(OF_POLY_WINDING_NONZERO);
    // apply transformation
    glPushMatrix();
    glTranslatef(x, y, 0.0);
    glScalef(scalex, scaley, 0.0);


#define DRAW_BLOB_VECTOR(points) do{ \
        ofBeginShape(); \
        for(int i = 0; i < (points).size(); i++){ \
          ofVertex((points[i]).x, (points[i]).y); \
        } \
        ofEndShape(true); \
      } while(0)

    ofNoFill();
    for (int j = 0; j < blobz.size(); j++) {
        ofSetColor(0xFF0000);

        DRAW_BLOB_VECTOR( blobz[j].getPoints());

        ofSetColor(0x00FF00);
        DRAW_BLOB_VECTOR(blobz[j].getHullPoints());

        ofSetColor(0x0000FF);
        DRAW_BLOB_VECTOR( blobz[j].getApproxPoints());

    }

    glPopMatrix();
}

void ofxCvBlobFinder::reset() {
    blobz.clear();
}

#endif
