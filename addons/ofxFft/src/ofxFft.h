#pragma once

#include "ofMain.h"

enum fftWindowType {
	OF_FFT_RECTANGULAR,
	OF_FFT_BARTLETT,
	OF_FFT_HANN,
	OF_FFT_HAMMING,
	OF_FFT_SINE};

enum fftImplementation {
	OF_FFT_BASIC,
	OF_FFT_FFTW};

enum fftMode {
	OF_FFT_CARTESIAN,
	OF_FFT_POLAR};

class ofxFft : public ofBaseDraws {
public:
	// create and destroy fft
	static ofxFft* create(
		int signalSize = 512,
		fftWindowType windowType = OF_FFT_HAMMING,
		fftImplementation implementation = OF_FFT_BASIC);
	virtual ~ofxFft();

	// forward fft
	virtual float* fft(float* input, fftMode mode = OF_FFT_POLAR) = 0;
	int getBinSize();
	float* getReal();
	float* getImaginary();
	float* getAmplitude();
	float* getPhase();
	// float* getPowerSpectrum();
	// float* getPower();

	// inverse fft
	virtual float* ifft(float* input) = 0;
	virtual float* ifft(float* a, float* b, fftMode mode = OF_FFT_POLAR) = 0;
	int getSignalSize();
	float* getSignal();

	// ofBaseDraws
	void draw(float x, float y);
	void draw(float x, float y, float width, float height);
	float getWidth();
	float getHeight();

protected:
	virtual void setup(int bins, fftWindowType windowType);

	// time domain data and methods
	fftWindowType windowType;
	float windowSum;
	float *window, *signal;

	bool signalReady;
	void setSignal(float* signal);
	void setWindowType(fftWindowType windowType);
	inline void runWindow(float* signal) {
		if(windowType != OF_FFT_RECTANGULAR)
			for(int i = 0; i < signalSize; i++)
				signal[i] *= window[i];
	}

	// frequency domain data and methods
	int signalSize, bins;
	float *real, *imag, *amplitude, *phase;

	void setReal(float* real);
	void setImaginary(float* imag);
	void setAmplitude(float* amplitude);
	void setPhase(float* phase);

	bool polarReady, cartesianReady;
	void updateCartesian();
	void updatePolar();

	inline float cartesianToAmplitude(float x, float y) {
		return sqrtf(x * x + y * y);
	}

	inline float cartesianToPhase(float x, float y) {
		return atan2f(y, x);
	}
};
