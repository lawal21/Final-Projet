#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0, 0, 0);
	SpawnMonsters();
	SpawnPlayer();
}

//--------------------------------------------------------------
void ofApp::update(){
	if (current_state == IN_PROGRESS) {
		
		//Checking if the game has been beated
		if (MonstersDefeated() == true) {
			current_state = FINISHED;
			bullets.clear();
			return;
		}
		
		//Moving monsters each second
		if (ofGetFrameNum() % frame_rate == 0) {
			MoveMonsters();
		}

		//Updating the timer for which a player can shoot
		if (ofGetFrameNum() % 1 == 0) {
			player_shoot_timer++;
		}

		//Monster shooting bullets
		if (ofGetFrameNum() % (frame_rate / 2) == 0) {
			int column = rand() % 9;

			int lowestMonster = LowestMonster(column);

			while (LowestMonster(column) < 0) {
				column = rand() % 9;
				lowestMonster = LowestMonster(column);
			}

			MonsterShoot(monsters[lowestMonster][column]);
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

		//Ignoring bullets that go off the screen
		for (int i = 0; i < bullets.size(); i++) {
			if (bullets.at(i).LocationBottomRight.GetY() < 0 || bullets.at(i).LocationTopLeft.GetY() > screen_size_y) {
				bullets.at(i).isAlive = false;
			}
		}

		//Checking for bullet collision
		for (int i = 0; i < bullets.size(); i++) {
			if (bullets.at(i).enemy) {
				if (!bullets.at(i).isAlive) {
					continue;
				}
				if (Collision(bullets.at(i).LocationTopLeft, bullets.at(i).LocationBottomRight,
					player.LocationTopLeft, player.LocationBottomRight)) {
					player.isAlive = false;
					current_state = FINISHED;
				}
			}
			else {
				for (int row = 0; row < 5; row++) {
					for (int column = 0; column < 10; column++) {
						if (!monsters[row][column].isAlive || !bullets.at(i).isAlive) {
							continue;
						}
						if (Collision(bullets.at(i).LocationTopLeft, bullets.at(i).LocationBottomRight,
							monsters[row][column].LocationTopLeft, monsters[row][column].LocationBottomRight)) {
							monsters[row][column].isAlive = false;
							bullets.at(i).isAlive = false;
						}
					}
				}
			}
		}
	}

	
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (current_state == PAUSED) {
		DrawGamePaused();
	}
	if (current_state == FINISHED) {
		DrawGameFinished();
	}
	DrawMonsters();
	DrawPlayer();
	DrawBullets();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	int upper_key = toupper(key);

	if (upper_key == 'A' || key == OF_KEY_LEFT) {
		if (current_state == IN_PROGRESS) {
			MovePlayer('A');
		}
	}
	else if (upper_key == 'D' || key == OF_KEY_RIGHT) {
		if (current_state == IN_PROGRESS) {
			MovePlayer('D');
		}
	}
	else if (upper_key == 'W' || key == OF_KEY_UP || upper_key == ' ') {
		if (player_shoot_timer >= 30) {
			PlayerShoot();
			player_shoot_timer = 0;
		}
	}
	//Code borrowed from ofSnake application
	else if (upper_key == 'P' && current_state != FINISHED) {
		current_state = (current_state == IN_PROGRESS) ? PAUSED : IN_PROGRESS;
	}
	else if (upper_key == 'R') {
		SpawnMonsters();
		SpawnPlayer();
		bullets.clear();
		current_state = IN_PROGRESS;
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
	for (int row = 0; row < 5; row++) {
		for (int column = 0; column < 10; column++) {
			monsters[row][column] = Monsters(row + 1);
			monsters[row][column].isAlive = true;
			float x = (40 + monster_spacing_x) * column + initial_monster_offset_x;
			float y = (40 + monster_spacing_y) * row + initial_monster_offset_y;
			monsters[row][column].LocationBottomRight.SetX(x + 40);
			monsters[row][column].LocationBottomRight.SetY(y + 40);
			monsters[row][column].LocationTopLeft.SetX(x);
			monsters[row][column].LocationTopLeft.SetY(y);
			monsters[row][column].Monster.draw(x, y);
		}
	}
}

void ofApp::SpawnPlayer() {
	player.isAlive = true;
	player.LocationBottomRight.SetX(screen_size_x / 2 + 2);
	player.LocationBottomRight.SetY(screen_size_y - 22);
	player.LocationTopLeft.SetX(screen_size_x / 2 - 2);
	player.LocationTopLeft.SetY(screen_size_y - 25);
	DrawPlayer();
}

//--------------------------------------------------------------
void ofApp::DrawMonsters() {
	for (int row = 0; row < 5; row++) {
		for (int column = 0; column < 10; column++) {
			if (monsters[row][column].Monster.isAllocated() && monsters[row][column].isAlive) {
				monsters[row][column].Monster.draw(monsters[row][column].LocationTopLeft.GetX(), monsters[row][column].LocationTopLeft.GetY());
			}
		}
	}
}

void ofApp::DrawPlayer() {
	if (player.Player.isAllocated() && player.isAlive) {
		player.Player.draw(player.LocationTopLeft.GetX(), player.LocationTopLeft.GetY());
	}
}

void ofApp::DrawBullets() {
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets.at(i).Bullet.isAllocated() && bullets.at(i).isAlive) {
			bullets.at(i).Bullet.draw(bullets.at(i).LocationTopLeft.GetX(), bullets.at(i).LocationTopLeft.GetY());
		}
	}
}

void ofApp::DrawGamePaused() {
	string pause_message = "Game Paused. Press P to Unpause!";
	ofSetColor(255, 255, 255);
	ofDrawBitmapString(pause_message, ofGetWindowWidth() / 2 - 100, ofGetWindowHeight() / 2);
}

void ofApp::DrawGameFinished() {
	if (player.isAlive) {
		string win_message = "You Won! Press R to Play Again!";
		ofSetColor(255, 255, 255);
		ofDrawBitmapString(win_message, ofGetWindowWidth() / 2 - 100, ofGetWindowHeight() / 2);
	}
	else {
		string lost_message = "You Lost! Press R to Try Again!";
		ofSetColor(255, 255, 255);
		ofDrawBitmapString(lost_message, ofGetWindowWidth() / 2 - 100, ofGetWindowHeight() / 2);
	}
}

//--------------------------------------------------------------
void ofApp::MoveMonsters() {
	bool move_down = false;
	
	if (!CheckValidMonsterMove(move_right)) {
		move_down = true;
		move_right = !move_right;
	}
	
	for (int row = 0; row < 5; row++) {
		for (int column = 0; column < 10; column++) {
			if (move_down) {
				monsters[row][column].LocationBottomRight.MoveDown(40 + monster_spacing_y);
				monsters[row][column].LocationTopLeft.MoveDown(40 + monster_spacing_y);
			}
			else if (move_right) {
				monsters[row][column].LocationBottomRight.MoveRight(15);
				monsters[row][column].LocationTopLeft.MoveRight(15);
			}
			else {
				monsters[row][column].LocationBottomRight.MoveLeft(15);
				monsters[row][column].LocationTopLeft.MoveLeft(15);
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

void ofApp::MonsterShoot(Monsters monster) {
	Bullets bullet = Bullets(true);

	bullet.LocationBottomRight = monster.LocationBottomRight;
	bullet.LocationTopLeft = monster.LocationBottomRight;

	bullet.LocationBottomRight.MoveDown(16);
	bullet.LocationBottomRight.MoveLeft(16);

	bullet.LocationTopLeft.MoveDown();
	bullet.LocationTopLeft.MoveLeft(23);

	bullets.push_back(bullet);
}

//--------------------------------------------------------------
bool ofApp::PixelWithinBounds(Location pixel, Location tlBound, Location brBound) {
	if ((pixel.GetX() >= tlBound.GetX() && pixel.GetX() <= brBound.GetX()) &&
		pixel.GetY() >= tlBound.GetY() && pixel.GetY() <= brBound.GetY()) {
		return true;
	}
	return false;
}

bool ofApp::Collision(Location LocationTopLeft, Location LocationBottomRight, Location tlBound, Location brBound) {
	Location LocationTopRight = Location(LocationBottomRight.GetX(), LocationTopLeft.GetY());
	Location LocationBottomLeft = Location(LocationTopLeft.GetX(), LocationBottomRight.GetY());
	if (PixelWithinBounds(LocationTopLeft, tlBound, brBound) ||
		PixelWithinBounds(LocationBottomRight, tlBound, brBound) ||
		PixelWithinBounds(LocationTopRight, tlBound, brBound) ||
		PixelWithinBounds(LocationBottomLeft, tlBound, brBound)) {
		return true;
	}
}

//--------------------------------------------------------------
bool ofApp::CheckValidMonsterMove(bool right) {
	for (int row = 0; row < 5; row++) {
		for (int column = 0; column < 10; column++) {
			if (monsters[row][column].isAlive) {
				if (right) {
					if (monsters[row][column].LocationBottomRight.GetX() + 1 >= screen_size_x - 1 - initial_monster_offset_x) {
						return false;
					}
				}
				else {
					if (monsters[row][column].LocationBottomRight.GetX() - 1 <= initial_monster_offset_x) {
						return false;
					}
				}
			}
		}
	}
	return true;

	
}

int ofApp::LowestMonster(int column) {
	for (int i = 4; i >= 0; i--) {
		if (monsters[i][column].isAlive) {
			return i;
		}
	}
	return -1;
}

bool ofApp::MonstersDefeated() {
	for (int row = 0; row < 5; row++) {
		for (int column = 0; column < 10; column++) {
			if (monsters[row][column].isAlive) {
				return false;
			}
		}
	}
	return true;
}