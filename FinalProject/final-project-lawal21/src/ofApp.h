#pragma once

#include "ofMain.h"
#include "Monsters.h"
#include "Players.h"
#include "Bullets.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		void SpawnMonsters(); //Initial spawn of the monsters
		void MoveMonsters(); //Function used to move the monsters left/right and down at the edge
		void MovePlayer(char direction); //Moves the player based on user input
		void PlayerShoot(); //Called when the player shoots
		void EnemyShoot(); //Called pierodically on the most bottom monster in a column
		bool CheckValidMonsterMove(bool right); //Helps move monsters know when to move down
		
	private:
		bool move_right = true;
		Monsters monsters[5][10];
		Players player = Players();
};
