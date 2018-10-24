#include "ofApp.h"

#define PIN_POTMETER 1
#define PIN_PRESSURESENSOR 3
#define PIN_BUTTON_1 2
#define PIN_BUTTON_2 4


void ofApp::setup() {
    // set listener - call ofApp::setupArduino when arduino is ready for use
    ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);
    
    // connect to the Arduino
    // use the same device name used in the Arduino IDE
    arduino.connect("/dev/cu.usbmodem14101");
    arduino.sendFirmwareVersionRequest(); // workaround for ofArduino/firmata bug
    
    sound1.load("Test2-Sound1.mp3");
    sound1.setLoop(true);
    sound2.load("Test2-Sound2.mp3");
    sound2.setLoop(true);
    sound3.load("Test2-Sound3.mp3");
    sound3.setLoop(true);
    sound4.load("Test2-Sound4.mp3");
    sound4.setLoop(true);
    sound5.load("Test2-Sound5.mp3");
    sound5.setLoop(true);
    sound6.load("Test2-Sound6.mp3");
    sound6.setLoop(true);
    sound7.load("Test2-Sound7.mp3");
    sound7.setLoop(true);
    sound8.load("Test2-Sound8.mp3");
    sound8.setLoop(true);
    
    logo1.load("communicanetis_logo2.png");

}

void ofApp::update() {
    arduino.update();
    //ofLog() << "isArduinoReady" << arduino.isArduinoReady() << endl;
}

void ofApp::draw() {
    //ofSetColor(color);
    ofSetBackgroundColor(ofColor::white);
    
    //checkerboard 1536 ^2
    
    //1455, 972
    logo1.draw((ofGetWidth() / 2) - 250, (ofGetHeight() / 2) - 250, 500, 500);
    
    //checkerboard.draw(0, 0, ofGetHeight(), ofGetHeight());
}

void ofApp::setupArduino(const int& version) {
    // remove listener because we don't need it anymore
    ofRemoveListener(arduino.EInitialized, this, &ofApp::setupArduino);
    
    // print firmware name and version to the console
    ofLog() << "Arduino firmware found: " << arduino.getFirmwareName()
    << " v" << arduino.getMajorFirmwareVersion() << "." << arduino.getMinorFirmwareVersion();
    
    arduino.sendDigitalPinMode(PIN_BUTTON_1, ARD_INPUT);
    arduino.sendDigitalPinMode(PIN_BUTTON_2, ARD_INPUT);
    
    arduino.sendAnalogPinReporting(PIN_PRESSURESENSOR, ARD_ANALOG);
    arduino.sendAnalogPinReporting(PIN_POTMETER, ARD_ANALOG);
    
    
    // set listeners for pin events
    ofAddListener(arduino.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
    ofAddListener(arduino.EAnalogPinChanged, this, &ofApp::analogPinChanged);
}

void ofApp::digitalPinChanged(const int& pinNum) {
    // get value with arduino.getDigital(pinNum)
    ofLogNotice() << "Digital Pin " << pinNum << " value: " << arduino.getDigital(pinNum) << endl;
    
    if (pinNum == 2) {
        
        if (arduino.getDigital(pinNum) == 1) {
            sound1.play();
            sound2.play();
            sound3.play();
            sound4.play();
            sound5.play();
            sound6.play();
            sound7.play();
            sound8.play();

        } else {
            sound1.stop();
            sound2.stop();
            sound3.stop();
            sound4.stop();
            sound5.stop();
            sound6.stop();
            sound7.stop();
            sound8.stop();
        }
        
    }
}

void ofApp::analogPinChanged(const int& pinNum) {
    // get value with arduino.getAnalog(pinNum));
    ofLogNotice() << "Analog Pin " << pinNum << " value: " << arduino.getAnalog(pinNum) << endl;
    
    //ofMap(arduino.getAnalog(PIN_POTMETER), 0, 1023, 0, 255);
    color = ofColor(ofMap(arduino.getAnalog(PIN_PRESSURESENSOR), 0, 730, 0, 255), 255 - (ofMap(arduino.getAnalog(PIN_PRESSURESENSOR), 0, 730, 0, 255)), 0);
    
    soundSelection = ofMap(arduino.getAnalog(PIN_PRESSURESENSOR), 0, 730, 1, 8);
    
    ofLog() << "Sound: " << soundSelection;
    
    sound1.setVolume(0);
    sound2.setVolume(0);
    sound3.setVolume(0);
    sound4.setVolume(0);
    sound5.setVolume(0);
    sound6.setVolume(0);
    sound7.setVolume(0);
    sound8.setVolume(0);

    if (soundSelection == 1) {
        sound1.setVolume(1.0);
    }
    if (soundSelection == 2) {
        sound2.setVolume(1.0);
    }
    if (soundSelection == 3) {
        sound3.setVolume(1.0);
    }
    if (soundSelection == 4) {
        sound4.setVolume(1.0);
    }
    if (soundSelection == 5) {
        sound5.setVolume(1.0);
    }
    if (soundSelection == 6) {
        sound6.setVolume(1.0);
    }
    if (soundSelection == 7) {
        sound7.setVolume(1.0);
    }
    if (soundSelection == 8) {
        sound8.setVolume(1.0);
    }
}
