#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

int main() {
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 512 + 32, 256 + 32 + 16, OF_WINDOW);
	ofRunApp(new testApp());
}
