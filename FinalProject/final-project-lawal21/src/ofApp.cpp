#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	SpawnMonsters();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	int upper_key = toupper(key);

	if (upper_key == 'A') {
		MovePlayer('A');
	}
	else if (upper_key == 'D') {
		MovePlayer('D');
	}
	else if (upper_key == 'W') {
		PlayerShoot();
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

//--------------------HELPER FUNCTIONS--------------------------
void SpawnMonsters() {

}

void MoveMonsters() {

}

void MovePlayer(char direction) {

}

void PlayerShoot() {

}
