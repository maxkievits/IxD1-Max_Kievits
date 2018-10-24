#pragma once

#include "ofMain.h"
#include "ofEvents.h"


class ofApp : public ofBaseApp{

public:
    
    void setup();
    
    void update();
    
    void draw();
    
    ofSoundPlayer sound1;
    ofSoundPlayer sound2;
    ofSoundPlayer sound3;
    ofSoundPlayer sound4;
    ofSoundPlayer sound5;
    ofSoundPlayer sound6;
    ofSoundPlayer sound7;
    ofSoundPlayer sound8;
    
    ofImage logo1;
    ofImage checkerboard;

    
    int soundSelection;
    
private:
    ofArduino arduino;
    
    void setupArduino(const int& version);
    
    void digitalPinChanged(const int& pinNum);
    
    void analogPinChanged(const int& pinNum);

    ofColor color;
		
};
