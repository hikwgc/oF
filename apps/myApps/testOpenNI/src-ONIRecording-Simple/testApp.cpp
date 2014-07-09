#include "ofApp.h"

class myUser : public ofxOpenNIUser {
public:
    void test(){
        cout << "test" << endl;
    }
};

//--------------------------------------------------------------
void ofApp::setup() {
    
 
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    openNIRecorder.setup();
    openNIRecorder.addDepthGenerator();
    openNIRecorder.addImageGenerator();
    openNIRecorder.setRegister(true);
    openNIRecorder.setMirror(true);
    openNIRecorder.addUserGenerator();
    openNIRecorder.setMaxNumUsers(2);
    openNIRecorder.start();

    openNIPlayer.setup();
	openNIPlayer.start();
    
    verdana.loadFont(ofToDataPath("verdana.ttf"), 24);
}

//--------------------------------------------------------------
void ofApp::update(){
    openNIRecorder.update();
    openNIPlayer.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255, 255, 255);
    
    ofPushMatrix();
    
    openNIRecorder.drawDebug(0, 0);
    openNIPlayer.drawDebug(0, 480);

    ofPushMatrix();
    
	ofSetColor(0, 255, 0);
	string msg = " MILLIS: " + ofToString(ofGetElapsedTimeMillis()) + " FPS: " + ofToString(ofGetFrameRate());
	verdana.drawString(msg, 20, 2 * 480 - 20);
}

//--------------------------------------------------------------
void ofApp::userEvent(ofxOpenNIUserEvent & event){
    ofLogNotice() << getUserStatusAsString(event.userStatus) << "for user" << event.id << "from device" << event.deviceID;
}

//--------------------------------------------------------------
void ofApp::gestureEvent(ofxOpenNIGestureEvent & event){
    ofLogNotice() << event.gestureName << getGestureStatusAsString(event.gestureStatus) << "from device" << event.deviceID << "at" << event.timestampMillis;
}

//--------------------------------------------------------------
void ofApp::exit(){
    openNIRecorder.stop();
    openNIPlayer.stop();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    int cloudRes = -1;
    switch (key) {
        case ' ':
            if(!openNIRecorder.isRecording()){
                openNIRecorder.startRecording(ofToDataPath("test.oni"));
            }else{
                openNIRecorder.stopRecording();
            }
            break;
        case 'p':
            openNIPlayer.startPlayer("test.oni");
            break;
        case '/':
            openNIPlayer.setPaused(!openNIPlayer.isPaused());
            break;
        case 'm':
            openNIPlayer.firstFrame();
            break;
        case '<':
        case ',':
            openNIPlayer.previousFrame();
            break;
        case '>':
        case '.':
            openNIPlayer.nextFrame();
            break;
        case 'x':
            openNIRecorder.stop();
            openNIPlayer.stop();
            break;
        case 't':
            openNIRecorder.toggleRegister();
            break;
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
void ofApp::windowResized(int w, int h){

}
