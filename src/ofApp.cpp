#include "ofApp.h"

ofFbo fbo;

ofVideoPlayer video;
ofVideoGrabber camera;

bool showGui;

ofxPanel gui;
ofxGuiGroup mixerGroup;
ofxFloatSlider video1Alpha, video2Alpha;

//--------------------------------------------------------------
void ofApp::setup() {
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    
    ofSetWindowTitle("Video thingies");
    ofSetWindowShape(1280, 720);
    ofSetFrameRate(60);
    ofBackground(ofColor::white);
    
    gui.loadFromFile("settings.xml");
    showGui = true;
    
    video.load("een.mov");
    video.play();
    
    camera.setDeviceID(0);
    camera.setDesiredFrameRate(30);
    camera.initGrabber(1280, 720);

    gui.setup("Mixer", "settings.xml");
    gui.setName("Mixer");
    
    mixerGroup.setup("Mixer");
    mixerGroup.setHeaderBackgroundColor(ofColor::blue);
    mixerGroup.setBorderColor(ofColor::blue);
    mixerGroup.add(video1Alpha.setup("Een", 100, 0, 255));
    mixerGroup.add(video2Alpha.setup("Twee", 100, 0, 255));
    
    gui.add(&mixerGroup);
}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();
    if (camera.isInitialized()) camera.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.begin();
    ofDisableSmoothing();
    ofSetColor(255, video1Alpha);
    video.draw(0, 0, ofGetWidth(), ofGetHeight());
    if (camera.isInitialized()) {
        ofSetColor(255, video2Alpha);
        camera.draw(0, 0, ofGetWidth(), ofGetHeight());
    }
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    fbo.end();
    
    ofSetColor(255);
    fbo.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    if (showGui) gui.draw();
}

void ofApp::exit() {
    gui.saveToFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'z') {
        showGui = !showGui;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
