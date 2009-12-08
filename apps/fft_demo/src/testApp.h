//-------------------------------------------------------------------------------------
//
// \file testApp.h
// \brief 
//
// \author Francois Visconte <f.visconte@gmail.com> 
// http://digitalork.blogspot.com, http://github.com/dopuskh3
//
//------------------------------------------------------------------------------------ 

#ifndef _TEST_APP
#define _TEST_APP

#define LIVE_MUSIC

#include "ofMain.h"
#include "ParticleSystem.h"

#ifdef LIVE_MUSIC
#include "ofxFft.h"
#endif

class testApp : public ofSimpleApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed  (int key);
		void keyReleased (int key);
		
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();
		
        ParticleSystem psys; 		

        ofSoundPlayer music;

        float *fftList;  
        float *fftSmoothed;     
        int bands;
        float amort;
        int tbands;
#ifdef LIVE_MUSIC
	ofxFft* fft;

	float* audioInput;

    void audioReceived(float* input, int bufferSize, int nChannels);
#endif

//        ofxGui *gui;
};

#endif
