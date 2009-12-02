#include "ofxFft.h"

//#include "ofxFftBasic.h"
#include "ofxFftw.h"

ofxFft* ofxFft::create(int signalSize, fftWindowType windowType, fftImplementation implementation) {
	ofxFft* fft;
	if(implementation == OF_FFT_BASIC) {
		//fft = new ofxFftBasic();
	} else if(implementation == OF_FFT_FFTW) {
		fft = new ofxFftw();
	}
	fft->setup(signalSize, windowType);
	return fft;
}

void ofxFft::setup(int signalSize, fftWindowType windowType) {
	this->signalSize = signalSize;
	this->bins = signalSize / 2;

	signal = new float[signalSize];
	real = new float[bins];
	imag = new float[bins];
	amplitude = new float[bins];
	phase = new float[bins];

	polarReady = false;
	cartesianReady = false;
	signalReady = true;

	window = new float[signalSize];
	setWindowType(windowType);
}

int ofxFft::getBinSize() {
	return bins;
}

int ofxFft::getSignalSize() {
	return signalSize;
}

void ofxFft::setWindowType(fftWindowType windowType) {
	this->windowType = windowType;
	if(windowType == OF_FFT_RECTANGULAR) {
		for(int i = 0; i < signalSize; i++)
			window[i] = 1; // only used for windowSum
	} else if(windowType == OF_FFT_BARTLETT) {
		for (int i = 0; i < signalSize / 2; i++) {
			window[i] = (i / (signalSize / 2));
			window[i + (signalSize / 2)] = (1.0 - (i / (signalSize / 2)));
		}
	} else if(windowType == OF_FFT_HANN) {
		for(int i = 0; i < signalSize; i++)
			window[i] = .5 * (1 - cos((TWO_PI * i) / (signalSize - 1)));
	} else if(windowType == OF_FFT_HAMMING) {
		for(int i = 0; i < signalSize; i++)
			window[i] = .54 - .46 * cos((TWO_PI * i) / (signalSize - 1));
	} else if(windowType == OF_FFT_SINE) {
		for(int i = 0; i < signalSize; i++)
			window[i] = sin((PI * i) / (signalSize - 1));
	}

	windowSum = 0;
	for(int i = 0; i < signalSize; i++)
		windowSum += window[i];
}

ofxFft::~ofxFft() {
	delete[] window, signal, real, imag, amplitude, phase;
}

void ofxFft::draw(float x, float y) {
	draw(x, y, getWidth(), getHeight());
}

void ofxFft::draw(float x, float y, float width, float height) {
	ofPushStyle();
	ofPushMatrix();

	ofTranslate(x, y);
	ofNoFill();
	ofRect(0, 0, width, height);
	ofBeginShape();
	getAmplitude();
	for (int i = 0; i < bins; i++)
		ofVertex(i, amplitude[i] * height);
	ofEndShape();

	ofPopMatrix();
	ofPopStyle();
}

float ofxFft::getWidth() {
	return bins;
}

float ofxFft::getHeight() {
	return bins / 2;
}

void ofxFft::setSignal(float* signal) {
	memcpy(this->signal, signal, sizeof(float) * signalSize);
}

void ofxFft::setReal(float* real) {
	memcpy(this->real, real, sizeof(float) * bins);
}

void ofxFft::setImaginary(float* imag) {
	memcpy(this->imag, imag, sizeof(float) * bins);
}

void ofxFft::setAmplitude(float* amplitude) {
	memcpy(this->amplitude, amplitude, sizeof(float) * bins);
}

void ofxFft::setPhase(float* phase) {
	memcpy(this->phase, phase, sizeof(float) * bins);
}


float* ofxFft::getSignal() {
	if(!signalReady) {
		float normalizer = 2. / windowSum;
		for (int i = 0; i < bins; i++)
			signal[i] *= normalizer;
		signalReady = true;
	}
	return signal;
}

float* ofxFft::getReal() {
	if(!cartesianReady)
		updateCartesian();
	return real;
}

float* ofxFft::getImaginary() {
	if(!cartesianReady)
		updateCartesian();
	return imag;
}

float* ofxFft::getAmplitude() {
	if(!polarReady)
		updatePolar();
	return amplitude;
}

float* ofxFft::getPhase() {
	if(!polarReady)
		updatePolar();
	return phase;
}

void ofxFft::updateCartesian() {
	for(int i = 0; i < bins; i++) {
		real[i] = cos(phase[i]) * amplitude[i];
		phase[i] = sin(phase[i]) * amplitude[i];
	}
	cartesianReady = true;
}

void ofxFft::updatePolar() {
	float normalizer = 2. / windowSum;
	for(int i = 0; i < bins; i++) {
		amplitude[i] = cartesianToAmplitude(real[i], imag[i]) * normalizer;
		phase[i] = cartesianToPhase(real[i], imag[i]);
	}
	polarReady = true;
}
