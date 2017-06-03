#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

	yolo.setup();
	grabber.initGrabber(640, 480);

}

//--------------------------------------------------------------
void ofApp::update(){


	grabber.update();
	if (grabber.isFrameNew()) {
		lastResults = yolo.detect(grabber.getPixels());
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	grabber.draw(ofVec2f(0, 0));

	ofNoFill();

	for (auto& r : lastResults) {
		ofDrawRectangle(r.x, r.y, r.w, r.h);
		ofDrawBitmapString(yolo.getName(r.obj_id) + " - " + ofToString(r.prob) ,r.x,r.y);
	}
	

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
