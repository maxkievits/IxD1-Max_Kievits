#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    grabber.setup(GRABBER_WIDTH, GRABBER_HEIGHT);
    
    rgbImage.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
    hsvImage.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
    hueImage.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
    satImage.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
    valImage.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    grabber.update();
    
    if (grabber.isFrameNew()) {
        rgbImage.setFromPixels(grabber.getPixels());
        rgbImage.mirror(false, true);
        
        hsvImage = rgbImage;
        hsvImage.convertRgbToHsv();
        hsvImage.convertToGrayscalePlanarImages(hueImage, satImage, valImage);
        
    }

}

//--------------------------------------------------------------
void ofApp::draw(){

    rgbImage.draw(0,0, ofGetWidth(), ofGetHeight());
    
    hsvImage.draw(0,0);
    hueImage.draw(0,GRABBER_HEIGHT);
    satImage.draw(GRABBER_WIDTH,GRABBER_HEIGHT);
    hueImage.draw(GRABBER_WIDTH * 2,GRABBER_HEIGHT);

    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}
