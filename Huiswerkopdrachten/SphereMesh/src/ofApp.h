#pragma once

#include "ofMain.h"
#include "ofEvents.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
    
    ofIcoSpherePrimitive primitive1;
    
    float spinX = 1;
    float spinY = 2;
    float sphereRadius = 100;
    float displacement;
    
    bool drawWireframe = true;
    
private:
    ofArduino arduino;
    
    void setupArduino(const int& version);
    
    void digitalPinChanged(const int& pinNum);
    
    void analogPinChanged(const int& pinNum);
};
