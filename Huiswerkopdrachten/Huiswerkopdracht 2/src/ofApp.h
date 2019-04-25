#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    
    ofxPanel gui;
    
    ofParameter<bool> drawGrid;
    ofParameter<bool> useLight;
    bool drawGui = true;
    
    ofLight light;
    ofEasyCam cam;
    
    ofParameter<float> rotateSpeedX;
    ofParameter<float> rotateSpeedY;
    ofParameter<float> rotateSpeedZ;
    
    ofParameter<bool> saveMatrix;
    
    // de huidige rotatie om de x, y en z assen
    float rotationX;
    float rotationY;
    float rotationZ;
};
