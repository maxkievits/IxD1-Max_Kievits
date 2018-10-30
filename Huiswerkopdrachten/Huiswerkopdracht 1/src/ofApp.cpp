#include "ofApp.h"

#define PIN_LED 12
#define PIN_BUTTON 11
#define PIN_POTMETER 1
#define PIN_LIGHTSENSOR 0

void ofApp::setup() {
    // set listener - call ofApp::setupArduino when arduino is ready for use
    ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);
    
    // connect to the Arduino
    // use the same device name used in the Arduino IDE
    arduino.connect("/dev/cu.usbmodem14101");
    arduino.sendFirmwareVersionRequest(); // workaround for ofArduino/firmata bug
    
    x = ofRandom(0, ofGetWidth());
    y = ofRandom(0, ofGetHeight());
    
    
    speedX = ofRandom(-10, 10);
    speedY = ofRandom(-10, 10);
    
    radius = 40;
    color = ofColor::red;
    mySound.load("ping_new.mp3");

}

void ofApp::update() {
    arduino.update();
        //ofLog() << "isArduinoReady" << arduino.isArduinoReady() << endl;
    
    if (x < 0) {
        x = 0;
        speedX = -speedX;
        collision();
    }
    
    if (x > ofGetWidth()) {
        x = ofGetWidth();
        speedX = -speedX;
        collision();
    }
    if (y < 0) {
        y = 0;
        speedY = -speedY;
        collision();
    }
    
    if (y > ofGetHeight
        ()) {
        y = ofGetHeight();
        speedY = -speedY;
        collision();
    }
    
    x += speedX;
    y += speedY;
}

void ofApp::collision() {
    if (arduino.getDigital(PIN_LED) == 1) {
        arduino.sendDigital(PIN_LED, ARD_LOW);
    } else {
        arduino.sendDigital(PIN_LED, ARD_HIGH);
    }
    mySound.play();
}

void ofApp::draw() {
    ofSetColor(color);
    ofDrawCircle(x, y, radius);
    
    if(arduino.getAnalog(PIN_LIGHTSENSOR) < 200) {
        ofSetBackgroundColor(0, 0, 0);
    } else {
        int value = ofMap(arduino.getAnalog(PIN_LIGHTSENSOR), 100, 500, 0, 255);
        ofSetBackgroundColor(value, value, value);
    }
    
}

void ofApp::setupArduino(const int& version) {
    // remove listener because we don't need it anymore
    ofRemoveListener(arduino.EInitialized, this, &ofApp::setupArduino);
    
    // print firmware name and version to the console
    ofLog() << "Arduino firmware found: " << arduino.getFirmwareName()
    << " v" << arduino.getMajorFirmwareVersion() << "." << arduino.getMinorFirmwareVersion();
    
    arduino.sendDigitalPinMode(PIN_LED, ARD_OUTPUT);
    arduino.sendDigitalPinMode(PIN_BUTTON, ARD_INPUT);
    arduino.sendDigitalPinMode(7, ARD_OUTPUT);
    arduino.sendDigitalPinMode(3, ARD_INPUT);

    arduino.sendAnalogPinReporting(PIN_LIGHTSENSOR, ARD_ANALOG);
    arduino.sendAnalogPinReporting(PIN_POTMETER, ARD_ANALOG);
    
    // set listeners for pin events
    ofAddListener(arduino.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
    ofAddListener(arduino.EAnalogPinChanged, this, &ofApp::analogPinChanged);
    
    arduino.sendDigital(7, ARD_HIGH);
    
}

void ofApp::digitalPinChanged(const int& pinNum) {
    // get value with arduino.getDigital(pinNum)
    //ofLogNotice() << "Digital Pin " << pinNum << " value: " << arduino.getDigital(pinNum) << endl;

}

void ofApp::analogPinChanged(const int& pinNum) {
    // get value with arduino.getAnalog(pinNum));
    ofLogNotice() << "Analog Pin " << pinNum << " value: " << arduino.getAnalog(pinNum) << endl;

    //ofMap(arduino.getAnalog(PIN_POTMETER), 0, 1023, 0, 255);
    color = ofColor(ofMap(arduino.getAnalog(PIN_POTMETER), 0, 1023, 0, 255), 255 - (ofMap(arduino.getAnalog(PIN_POTMETER), 0, 1023, 0, 255)), 0);
    
    //ofLog() << ofMap(arduino.getAnalog(PIN_POTMETER), 0, 1023, 0, 20);

}


void ofApp::mousePressed(int x, int y, int button) {
    // switch the LED on
    arduino.sendDigital(PIN_LED, ARD_HIGH);
}

void ofApp::mouseReleased(int x, int y, int button) {
    // switch the LED off
    arduino.sendDigital(PIN_LED, ARD_LOW);
}

void ofApp::keyPressed(int key) {
    arduino.sendDigital(PIN_LED, ARD_HIGH);

}

void ofApp::keyReleased(int key) {
    arduino.sendDigital(PIN_LED, ARD_LOW);

}


