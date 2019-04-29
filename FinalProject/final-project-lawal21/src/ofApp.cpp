#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	SpawnMonsters();
	SpawnPlayer();
}

//--------------------------------------------------------------
void ofApp::update(){
	//Moving monsters each second
	if (ofGetFrameNum() % frame_rate == 0) {
		MoveMonsters();
	}

	if (ofGetFrameNum() % 1 == 0) {
		player_shoot_timer++;
	}
	
	//Moving bullets
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets.at(i).enemy) {
			bullets.at(i).LocationBottomRight.MoveDown(10);
			bullets.at(i).LocationTopLeft.MoveDown(10);
		}
		else {
			bullets.at(i).LocationBottomRight.MoveUp(10);
			bullets.at(i).LocationTopLeft.MoveUp(10);
		}
	}
	/*

	//Checking for bullet collision
	vector<int> bullets_to_remove;
	for (int i = 0; i < bullets.size(); i++) {
		//Indexing all bullets that have collided
		if (bullets.at(i).enemy) {
			if (bullets.at(i).PlayerCollision(player)) {
				bullets_to_remove.push_back(i);
			}
		}
		else {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 10; j++) {
					if (bullets.at(i).MonsterCollision(monsters[i][j])) {
						bullets_to_remove.push_back(i);
					}
				}
			}
		}
		//Removing these bullets so they are not drawn
		for (int i = 0; i < bullets_to_remove.size(); i++) {
			bullets.erase(bullets.begin() + i - 1);
		}
	}

	*/
}

//--------------------------------------------------------------
void ofApp::draw(){
	DrawMonsters();
	DrawPlayer();
	DrawBullets();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	int upper_key = toupper(key);

	if (upper_key == 'A' || key == OF_KEY_LEFT) {
		MovePlayer('A');
	}
	else if (upper_key == 'D' || key == OF_KEY_RIGHT) {
		MovePlayer('D');
	}
	else if (upper_key == 'W' || key == OF_KEY_UP || key == OF_KEY_RETURN) {
		if (player_shoot_timer >= 30) {
			PlayerShoot();
			player_shoot_timer = 0;
		}
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

//-----------------------HELPER FUNCTIONS-----------------------

//--------------------------------------------------------------
void ofApp::SpawnMonsters() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			monsters[i][j] = Monsters(i + 1);
			float x = (40 + monster_spacing_x) * j + initial_monster_offset;
			float y = (40 + monster_spacing_y) * i + initial_monster_offset;
			monsters[i][j].LocationBottomRight.SetX(x + 40);
			monsters[i][j].LocationBottomRight.SetY(y + 40);
			monsters[i][j].LocationTopLeft.SetX(x);
			monsters[i][j].LocationTopLeft.SetY(y);
			monsters[i][j].Monster.draw(x, y);
		}
	}
}

void ofApp::SpawnPlayer() {
	player.LocationBottomRight.SetX(screen_size_x / 2 + 2);
	player.LocationBottomRight.SetY(screen_size_y - 22);
	player.LocationTopLeft.SetX(screen_size_x / 2 - 2);
	player.LocationTopLeft.SetY(screen_size_y - 25);
	DrawPlayer();
}

//--------------------------------------------------------------
void ofApp::DrawMonsters() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			if (monsters[i][j].Monster.isAllocated()) {
				monsters[i][j].Monster.draw(monsters[i][j].LocationTopLeft.GetX(), monsters[i][j].LocationTopLeft.GetY());
			}
		}
	}
}

void ofApp::DrawPlayer() {
	if (player.Player.isAllocated()) {
		player.Player.draw(player.LocationTopLeft.GetX(), player.LocationTopLeft.GetY());
	}
}

void ofApp::DrawBullets() {
	for (int i = 0; i < bullets.size(); i++) {
		bullets.at(i).Bullet.draw(bullets.at(i).LocationTopLeft.GetX(), bullets.at(i).LocationTopLeft.GetY());
	}
}

//--------------------------------------------------------------
void ofApp::MoveMonsters() {
	bool move_down = false;
	
	if (!CheckValidMonsterMove(move_right)) {
		move_down = true;
		move_right = !move_right;
	}
	
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			if (move_down) {
				monsters[i][j].LocationBottomRight.MoveDown(40 + monster_spacing_y);
				monsters[i][j].LocationTopLeft.MoveDown(40 + monster_spacing_y);
			}
			else if (move_right) {
				monsters[i][j].LocationBottomRight.MoveRight(15);
				monsters[i][j].LocationTopLeft.MoveRight(15);
			}
			else {
				monsters[i][j].LocationBottomRight.MoveLeft(15);
				monsters[i][j].LocationTopLeft.MoveLeft(15);
			}	
		}
	}
}

void ofApp::MovePlayer(char direction) {
	if (direction == 'A') {
		player.LocationBottomRight.MoveLeft(10);
		player.LocationTopLeft.MoveLeft(10);
	}
	else if (direction == 'D') {
		player.LocationBottomRight.MoveRight(10);
		player.LocationTopLeft.MoveRight(10);
	}
}

//--------------------------------------------------------------
void ofApp::PlayerShoot() {
	Bullets	bullet = Bullets(false);
	
	bullet.LocationBottomRight = player.LocationTopLeft;
	bullet.LocationTopLeft = player.LocationTopLeft;
	
	bullet.LocationBottomRight.MoveUp();
	bullet.LocationBottomRight.MoveRight(19);
	bullet.LocationTopLeft.MoveUp(8);
	bullet.LocationTopLeft.MoveRight(12);

	bullets.push_back(bullet);
}

void ofApp::EnemyShoot(Monsters monster) {
	Bullets bullet = Bullets(true);

	bullet.LocationBottomRight = monster.LocationBottomRight;
	bullet.LocationTopLeft = monster.LocationBottomRight;

	bullet.LocationBottomRight.MoveLeft(5);
	bullet.LocationTopLeft.MoveLeft(5);
	
	bullet.LocationBottomRight.MoveDown();
	bullet.LocationTopLeft.MoveDown();

	bullets.push_back(bullet);
}

//--------------------------------------------------------------
bool ofApp::CheckValidMonsterMove(bool right) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			if (monsters[i][j].isAlive) {
				if (right) {
					if (monsters[i][j].LocationBottomRight.GetX() + 1 >= screen_size_x - 1 - initial_monster_offset) {
						return false;
					}
				}
				else {
					if (monsters[i][j].LocationBottomRight.GetX() - 1 <= initial_monster_offset) {
						return false;
					}
				}
			}
		}
	}
	return true;
}