
#pragma once

#include "ofxFft.h"
#include "ofTypes.h"


class ofxFftBasic : public ofxFft{
public:

	~ofxFftBasic();

	void setup(int _bins, fftWindowType _windowType);
	void fft(float* input, float* output);
	void ifft(float* input, float* output) {};


	/* Calculate the power spectrum */
	void powerSpectrum(int start, int half, float *data, int bins,float *magnitude,float *phase, float *power, float *avg_power);
	/* ... the inverse */
	void inversePowerSpectrum(int start, int half, int bins, float *finalOut,float *magnitude,float *phase);

private:

    void FFT(int bins, bool InverseTransform, float *RealIn, float *ImagIn, float *RealOut, float *ImagOut);
    void RealFFT(int bins, float *RealIn, float *RealOut, float *ImagOut);
    void FastPowerSpectrum(int bins, float *In, float *Out);

    bool ready;

};
