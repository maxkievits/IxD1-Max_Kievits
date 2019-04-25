#include "ofApp.h"

void ofApp::setup() {
    ofBackground(ofColor::black);
    
    gui.setup();
    
    gui.add(rotateSpeedX.set("X", 0, 0, 9.0));     // slider voor X toevoegen
    gui.add(rotateSpeedY.set("Y", 0, 0, 9.0));     // slider voor Y toevoegen
    gui.add(rotateSpeedZ.set("Z", 0, 0, 9.0));     // slider voor Z toevoegen
    gui.add(saveMatrix.set("save matrix", false)); // toggle: gebruik ofPushMatrix()/ofPopMatrix() per rotatie

    
    gui.add(drawGrid.set("Grid", false));
    gui.add(useLight.set("Light", true));
    
    light.setDirectional();
    light.setDiffuseColor(ofColor::white);
    light.enable();
}

void ofApp::update() {
    rotationX += rotateSpeedX;
    rotationY += rotateSpeedY;
    rotationZ += rotateSpeedZ;
}

void ofApp::draw() {
    
    ofEnableDepthTest();
    
    cam.setVFlip(true);
    cam.begin();
    
    if (useLight) {
        ofEnableLighting();
    } else {
        ofDisableLighting();
    }
    
    ofSetColor(ofColor::yellow);
    ofDrawSphere(0, 0, 0, 100);
    
    ofSetColor(ofColor::blue);
    ofDrawSphere(200, 0, 0, 50);
    
    if (drawGrid) ofDrawGrid(200);
    
    cam.end();
    ofDisableDepthTest();
    
    if (drawGui) {
        ofDisableLighting();
        gui.draw();
    }
}

void ofApp::keyPressed(int key) {
    if (key == 'l') useLight = !useLight;
    if (key == 'g') drawGrid = !drawGrid;
    if (key == ' ') drawGui = !drawGui;
}
