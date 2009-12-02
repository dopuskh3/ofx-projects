#pragma once

#include "ofxFft.h"
#include "fftw3.h"

class ofxFftw : public ofxFft{
public:
	ofxFftw();
	~ofxFftw();

	void setup(int signalSize, fftWindowType windowType);
	float* fft(float* input, fftMode mode);
	float* ifft(float* input);
	float* ifft(float* a, float* b, fftMode mode);

private:
	float *fftIn, *fftOut, *ifftIn, *ifftOut;
	fftwf_plan fftPlan, ifftPlan;
};
