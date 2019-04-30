#pragma once

#include "ofMain.h"
#include "Monsters.h"
#include "Players.h"
#include "Bullets.h"
#include <vector>
#include <random>

//Enum to represent the current state of the game
//Code borrowed from ofSnake appliation
enum GameState {
	IN_PROGRESS = 0,
	PAUSED,
	FINISHED,
	STARTED,
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		int screen_size_x = 1028;
		int screen_size_y = 768;
		int frame_rate = 30;
		int initial_monster_offset_x = 20;
		int initial_monster_offset_y = 50;


	//private:
		GameState current_state = STARTED;
		
		//Initial spawning
		void SpawnMonsters(); 
		void SpawnPlayer(); 

		bool CheckValidMonsterMove(bool right); //Helps move monsters know when to move down
		void MoveMonsters(); //Function used to move the monsters left/right and down at the edge
		void MovePlayer(char direction); //Moves the player based on user input

		void PlayerShoot(); //Called when the player shoots
		void MonsterShoot(Monsters monster); //Called pierodically on the most bottom monster in a column
		int LowestMonster(int column); //Finds the lowest monster in a column
		bool MonstersDefeated(); //Checks whether all the monsters have been defeated

		bool PixelWithinBounds(Location pixel, Location tlBound, Location brBound);
		bool Collision(Location LocationTopLeft, Location LocationBottomRight, 
			Location tlBound, Location brBound); //Checks whether an object collides with another

		//Helper functions to draw each object
		void DrawGameStarted();
		void DrawGamePaused();
		void DrawGameFinished();
		void DrawMonsters();
		void DrawPlayer();
		void DrawBullets();
		
		bool move_right = true;

		int monster_spacing_x = 20;
		int monster_spacing_y = 8;
		int player_shoot_timer = 30;

		Monsters monsters[5][10];
		Players player = Players();
		vector<Bullets> bullets;
};
