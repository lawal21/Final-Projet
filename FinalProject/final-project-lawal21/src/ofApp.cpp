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
	if (ofGetFrameNum() % 30 == 0) {
		MoveMonsters();
	}
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
void ofApp::SpawnMonsters() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			monsters[i][j].locationBR.SetX(15 * j + 20);
			monsters[i][j].locationBR.SetY(12 * i + 20);
			monsters[i][j].locationTL.SetY(15 * j + 10);
			monsters[i][j].locationTL.SetY(12 * i + 10);
		}
	}
}

void ofApp::MoveMonsters() {
	bool move_down = false;
	
	if (!CheckValidMonsterMove(move_right)) {
		move_down = true;
		move_right = !move_right;
	}
	
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			if (move_down) {
				monsters[i][j].locationBR.MoveDown();
				monsters[i][j].locationTL.MoveDown();
			}
			else {
				if (move_right) {
					monsters[i][j].locationBR.MoveRight();
					monsters[i][j].locationTL.MoveRight();
				}
				else {
					monsters[i][j].locationBR.MoveLeft();
					monsters[i][j].locationTL.MoveLeft();
				}
			}	
		}
	}
}

void ofApp::MovePlayer(char direction) {
	if (direction == 'A') {
		player.locationBR.MoveLeft();
		player.locationTL.MoveLeft();
	}
	else if (direction == 'D') {
		player.locationBR.MoveRight();
		player.locationTL.MoveRight();
	}
}

void ofApp::PlayerShoot() {
	Bullets	bullet = Bullets(false);
	
	bullet.locationBR = player.locationTL;
	bullet.locationTL = player.locationTL;
	
	bullet.locationBR.MoveUp();
	bullet.locationBR.MoveRight();
	bullet.locationTL.MoveUp();
	bullet.locationTL.MoveRight();
}

void ofApp::EnemyShoot() {
	Bullets bullet = Bullets(true);
}

bool ofApp::CheckValidMonsterMove(bool right) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			if (monsters[i][j].isAlive) {
				if (right) {
					if (monsters[i][j].locationBR.x + 1 > 320) {
						return false;
					}
				}
				else {
					if (monsters[i][j].locationBR.x - 1 < 0) {
						return false;
					}
				}
			}
		}
	}
	return true;
}