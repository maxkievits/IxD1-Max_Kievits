#include "ofApp.h"

#define PIN_LED 12
#define PIN_BUTTON 11
#define PIN_POTMETER 1
#define PIN_LIGHTSENSOR 0

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(0, 0, 0);
    
    primitive1 = ofIcoSpherePrimitive(sphereRadius, 2);
    ofSetFrameRate(60);
    
    ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);
    
    // connect to the Arduino
    // use the same device name used in the Arduino IDE
    arduino.connect("/dev/cu.usbmodem14101");
    arduino.sendFirmwareVersionRequest(); // workaround for ofArduino/firmata bug
}

//--------------------------------------------------------------
void ofApp::update(){
    arduino.update();

    
    auto triangles = primitive1.getMesh().getUniqueFaces();
    
    
    for (int i = 0; i < triangles.size(); i++) {
        ofVec3f faceNormal = triangles[i].getFaceNormal();
        for (int j = 0; j < 3; j++) {
            triangles[i].setVertex(j, triangles[i].getVertex(j) + faceNormal * displacement);
        }
    }
    
    primitive1.getMesh().setFromTriangles(triangles);

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofTranslate(ofGetWidth() / 2, ofGetHeight()/2);
    
    primitive1.rotateDeg(spinX, 1, 0, 0);
    primitive1.rotateDeg(spinY, 0, 1, 0);
    
    
    if(drawWireframe) {
        primitive1.drawWireframe();
    } else {
        primitive1.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ') {
        drawWireframe = !drawWireframe;
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
    
    if(int(ofMap(arduino.getAnalog(PIN_POTMETER), 0, 1023, 0, 2)) == 0) {
        displacement = -1;
    }
    if(int(ofMap(arduino.getAnalog(PIN_POTMETER), 0, 1023, 0, 2)) == 1) {
        displacement = 0;
    }
    if(int(ofMap(arduino.getAnalog(PIN_POTMETER), 0, 1023, 0, 2)) == 2) {
        displacement = 1;
    }
    
    ofLog() << displacement;

    
    //ofLog() << ofMap(arduino.getAnalog(PIN_POTMETER), 0, 1023, 0, 20);
    
}
