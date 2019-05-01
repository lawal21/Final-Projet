#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0, 0, 0);
	SpawnMonsters();
	SpawnPlayer();
}

//--------------------------------------------------------------
void ofApp::update(){
	
	//Updating which frame the monster is being displayed
	if (current_state != PAUSED) {
		if (ofGetFrameNum() % (frame_rate / 2) == 0) {
			is_first_frame = !is_first_frame;
		}
	}
	
	if (current_state == IN_PROGRESS) {
		
		//Updating the high score
		if (high_score < player.points) {
			high_score = player.points;
		}
		
		//Checking if the game has been beaten
		if (MonstersDefeated() == true) {
			current_state = FINISHED;
			bullets.clear();
			return;
		}

		//Checking for bullet collision
		for (int i = 0; i < bullets.size(); i++) {
			//Enemy bullet collision with player
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
			//Player bullet collision with enemy
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
							player.points += (5 - row) * 100;
						}
					}
				}
			}
		}
		
		//Checking for collision between monster and player
		for (int row = 0; row < 5; row++) {
			for (int column = 0; column < 10; column++) {
				if (Collision(player.LocationTopLeft, player.LocationBottomRight,
					monsters[row][column].LocationTopLeft, monsters[row][column].LocationBottomRight)) {
					player.isAlive = false;
					current_state = FINISHED;
				}
			}
		}
		
		//Moving monsters each second
		if (ofGetFrameNum() % frame_rate == 0) {
			MoveMonsters();
		}


		//Updating the timer for which a player can shoot/move
		if (ofGetFrameNum() % 1 == 0) {
			player_shoot_timer++;
			player_move_timer++;
		}

		//Moving player
		if (player_moving_left) {
			if (player_move_timer > 1) {
				MovePlayer('A');
				player_move_timer = 0;
			}
		}
		else if (player_moving_right) {
			if (player_move_timer > 1) {
				MovePlayer('D');
				player_move_timer = 0;
			}
		}

		//Monster shooting bullets
		if (ofGetFrameNum() % (frame_rate / 2) == 0) {
			int column = rand() % 9;

			int lowestMonster = LowestMonster(column);

			while (lowestMonster < 0) {
				column = rand() % 9;
				lowestMonster = LowestMonster(column);
			}

			MonsterShoot(monsters[lowestMonster][column]);
		}

		//Ignoring bullets that go off the screen
		for (int i = 0; i < bullets.size(); i++) {
			if (bullets.at(i).LocationBottomRight.GetY() < 0 
				|| bullets.at(i).LocationTopLeft.GetY() > screen_size_y) {
				bullets.at(i).isAlive = false;
			}
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
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	DrawMonsters();
	DrawPlayer();
	DrawBullets();
	if (current_state == PAUSED) {
		DrawGamePaused();
	}
	else if (current_state == FINISHED) {
		DrawGameFinished();
	}
	else if (current_state == STARTED) {
		DrawGameStarted();
	}
	if (current_state != STARTED) {
		DrawPoints();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	//Any key to start the game
	if (current_state == STARTED) {
		current_state = IN_PROGRESS;
		return;
	}

	int upper_key = toupper(key);

	//Handling player movement
	if (upper_key == 'A' || key == OF_KEY_LEFT) {
		if (current_state == IN_PROGRESS || PAUSED) {
			player_moving_right = false;
			player_moving_left = true;
		}
	}
	else if (upper_key == 'D' || key == OF_KEY_RIGHT) {
		if (current_state == IN_PROGRESS || PAUSED) {
			player_moving_left = false;
			player_moving_right = true;
		}
	}
	//Handling player shooting
	else if (upper_key == 'W' || key == OF_KEY_UP || upper_key == ' ') {
		if (player_shoot_timer >= 30 && current_state == IN_PROGRESS) {
			PlayerShoot();
			player_shoot_timer = 0;
		}
	}
	//Pausing the board
	//Code borrowed from ofSnake application
	else if (upper_key == 'P' && current_state != FINISHED) {
		current_state = (current_state == IN_PROGRESS) ? PAUSED : IN_PROGRESS;
	}
	//Resetting the board
	else if (upper_key == 'R') {
		SpawnMonsters();
		SpawnPlayer();
		bullets.clear();
		player.points = 0;
		current_state = STARTED;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	
	int upper_key = toupper(key);

	//Stopping movement
	if (upper_key == 'A' || key == OF_KEY_LEFT) {
		player_moving_left = false;
		player_move_timer = 1;
	}
	else if (upper_key == 'D' || key == OF_KEY_RIGHT) {
		player_moving_right = false;
		player_move_timer = 1;
	}
}

//-----------------------HELPER FUNCTIONS-----------------------
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
	player.LocationBottomRight.SetX(screen_size_x / 2 + 15);
	player.LocationBottomRight.SetY(screen_size_y - 4);
	player.LocationTopLeft.SetX(screen_size_x / 2 - 16);
	player.LocationTopLeft.SetY(screen_size_y - 28);
	DrawPlayer();
}

//--------------------------------------------------------------

void ofApp::DrawMonsters() {
	for (int row = 0; row < 5; row++) {
		for (int column = 0; column < 10; column++) {
			if (is_first_frame) {
				if (monsters[row][column].isAlive) {
					monsters[row][column].Monster.draw(monsters[row][column].LocationTopLeft.GetX(), 
						monsters[row][column].LocationTopLeft.GetY());
				}
			}
			else {
				if (monsters[row][column].isAlive) {
					monsters[row][column].Monster1.draw(monsters[row][column].LocationTopLeft.GetX(), 
						monsters[row][column].LocationTopLeft.GetY());
				}
			}
		}
	}
}

void ofApp::DrawPlayer() {
	if (player.isAlive) {
		player.Player.draw(player.LocationTopLeft.GetX(), player.LocationTopLeft.GetY());
	}
}

void ofApp::DrawBullets() {
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets.at(i).isAlive) {
			bullets.at(i).Bullet.draw(bullets.at(i).LocationTopLeft.GetX(), bullets.at(i).LocationTopLeft.GetY());
		}
	}
}

void ofApp::DrawGameStarted() {
	string start_message = "Press Any Key to Continue!\nLeft = A or Left Arrow\nRight = D or Right Arrow\nShoot = W or Up Arrow or Space\nPause = P\nRestart = R\nExit = Esc";
	ofSetColor(0, 255, 255);
	ofDrawBitmapString(start_message, ofGetWindowWidth() / 2 - 100, ofGetWindowHeight() / 2);
	ofSetColor(255, 255, 255);
}

void ofApp::DrawGamePaused() {
	string pause_message = "Game Paused. Press P to Unpause!";
	ofDrawBitmapString(pause_message, ofGetWindowWidth() / 2 - 100, ofGetWindowHeight() / 2);
}

void ofApp::DrawGameFinished() {
	if (player.isAlive) {
		string win_message = "You Won! Press R to Play Again!";
		ofSetColor(0, 255, 0);
		ofDrawBitmapString(win_message, ofGetWindowWidth() / 2 - 100, ofGetWindowHeight() / 2);
	}
	else {
		string lost_message = "You Lost! Press R to Try Again!";
		ofSetColor(255, 0, 0);
		ofDrawBitmapString(lost_message, ofGetWindowWidth() / 2 - 100, ofGetWindowHeight() / 2);
	}
	ofSetColor(255, 255, 255);
}

void ofApp::DrawPoints() {
	string points_message = "Points: " + to_string(player.points);
	string high_score_message = "High Score: " + to_string(high_score);
	ofSetColor(0, 255, 255);
	ofDrawBitmapString(points_message, 10, 10);
	ofDrawBitmapString(high_score_message, screen_size_x - 150, 10);
	ofSetColor(255, 255, 255);
}

//--------------------------------------------------------------

void ofApp::MoveMonsters() {
	
	bool move_down = false;
	
	//Checking whether the monsters are at the end near a wall
	if (!CheckValidMonsterMove(monsters_move_right)) {
		move_down = true;
		monsters_move_right = !monsters_move_right;
	}
	
	for (int row = 0; row < 5; row++) {
		for (int column = 0; column < 10; column++) {
			if (move_down) {
				monsters[row][column].LocationBottomRight.MoveDown(40 + monster_spacing_y);
				monsters[row][column].LocationTopLeft.MoveDown(40 + monster_spacing_y);
			}
			else if (monsters_move_right) {
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
	if (direction == 'A' && player.LocationTopLeft.GetX() > 0) {
		player.LocationBottomRight.MoveLeft(10);
		player.LocationTopLeft.MoveLeft(10);
	}
	else if (direction == 'D' && player.LocationBottomRight.GetX() < screen_size_x) {
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
	
	//Checking if one corner is within the bounds, meaning there is a collision
	if (PixelWithinBounds(LocationTopLeft, tlBound, brBound) ||
		PixelWithinBounds(LocationBottomRight, tlBound, brBound) ||
		PixelWithinBounds(LocationTopRight, tlBound, brBound) ||
		PixelWithinBounds(LocationBottomLeft, tlBound, brBound)) {
		return true;
	}
}

//--------------------------------------------------------------

bool ofApp::CheckValidMonsterMove(bool move_right) {
	for (int row = 0; row < 5; row++) {
		for (int column = 0; column < 10; column++) {
			if (monsters[row][column].isAlive) {
				if (move_right) {
					if (monsters[row][column].LocationBottomRight.GetX() + 1 >= screen_size_x - 1 - initial_monster_offset_x) {
						return false;
					}
				}
				else {
					if (monsters[row][column].LocationTopLeft.GetX() - 1 <= initial_monster_offset_x) {
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