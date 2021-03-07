#include "ofApp.h"

ofFbo fbo;

ofVideoPlayer video;
ofVideoGrabber camera;

float soundLevel;
ofSoundStream micInput;

float elapsedTime;

int video1Alpha;
int video2Alpha;

//--------------------------------------------------------------
void ofApp::setup() {
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
    
    elapsedTime = ofGetElapsedTimef();
    
    ofSetWindowTitle("Video thingies");
    ofSetWindowShape(1280, 720);
    ofSetFrameRate(30);
    ofBackground(ofColor::white);
    
    video.load("een.mov");
    video.play();
    
    camera.setDeviceID(0);
    camera.setDesiredFrameRate(30);
    camera.initGrabber(1280, 720);
    
    video1Alpha = 100;
    video2Alpha = 100;
    
    soundLevel = 0;
    
    ofSoundStreamSettings settings;
    auto devices = micInput.getMatchingDevices("default");
    if(!devices.empty()){
        settings.setInDevice(devices[0]);
    }
    settings.setInListener(this);
    settings.sampleRate = 44100;
    settings.numOutputChannels = 0;
    settings.numInputChannels = 1;
    settings.bufferSize = 44100;
    micInput.setup(settings);
}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();
    if (camera.isInitialized()) camera.update();
    
    video1Alpha = (int)(255 * ofNoise(0.2 * elapsedTime, 1));
    video2Alpha = (int)soundLevel % 255;
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
}

void ofApp::audioIn(ofSoundBuffer & buffer) {
    double rms = 0;
    
    for (int i = 0; i < buffer.size(); i++) {
        float sample = buffer.getSample(i, 1);
        rms += sample * sample;
    }
    //std::printf("value: %f\n", rms);
    soundLevel = rms;
}

void ofApp::exit() {
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
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
