#include "testApp.h"

void testApp::setup() {
	plotHeight = 128;
	bufferSize = 512;

	fft = ofxFft::create(bufferSize, OF_FFT_HAMMING, OF_FFT_FFTW);

	// 0 output channels,
	// 1 input channel
	// 44100 samples per second
	// [bins] samples per buffer
	// 4 num buffers (latency)

	ofSoundStreamSetup(0, 1, this, 44100, bufferSize, 4);

	audioInput = new float[bufferSize];
	fftOutput = NULL;

	mode = SINE;
	appWidth = ofGetWidth();
	appHeight = ofGetHeight();

	ofBackground(0, 0, 0);
}

void testApp::draw() {

	ofSetColor(0xffffff);

	ofPushMatrix();
	glTranslatef(16, 16, 0);
	plot(audioInput, bufferSize, plotHeight / 2, 0);
	ofDrawBitmapString("Audio Input", 0, 0);

	if(fftOutput != NULL) {
		glTranslatef(0, plotHeight + 16, 0);
		plot(fftOutput, fft->getBinSize(), -plotHeight, plotHeight / 2);
		ofDrawBitmapString("FFT", 0, 0);
		ofPopMatrix();
	}

	string msg = ofToString((int) ofGetFrameRate()) + " fps";
	ofDrawBitmapString(msg, appWidth - 80, appHeight - 20);
}

void testApp::plot(float* array, int length, float scale, float offset) {
	ofNoFill();
	ofRect(0, 0, length, plotHeight);
	glPushMatrix();
	glTranslatef(0, plotHeight / 2 + offset, 0);
	ofBeginShape();
	for (int i = 0; i < length; i++)
		ofVertex(i, array[i] * scale);
	ofEndShape();
	glPopMatrix();
}

void testApp::audioReceived(float* input, int bufferSize, int nChannels) {
	if (mode == MIC) {
		// store input in audioInput buffer
		memcpy(audioInput, input, sizeof(float) * bufferSize);
	} else if (mode == NOISE) {
		for (int i = 0; i < bufferSize; i++)
			audioInput[i] = ofRandom(-1, 1);
	} else if (mode == SINE) {
		for (int i = 0; i < bufferSize; i++)
			audioInput[i] = sinf(PI * i * mouseX / appWidth);
	}
	// compute fft given audioInput
	fftOutput = fft->fft(audioInput);
}

void testApp::keyPressed(int key) {
	switch (key) {
	case 'm':
		mode = MIC;
		break;
	case 'n':
		mode = NOISE;
		break;
	case 's':
		mode = SINE;
		break;
	}
}

testApp::~testApp() {
	ofSoundStreamStop();
	delete[] audioInput;
	delete fft;
}
