#define CATCH_CONFIG_MAIN
#include "Catch.h"
#include "C:\Users\djlaw\source\repos\final-project-lawal21\FinalProject\final-project-lawal21\src\ofApp.h"

ofApp app;


TEST_CASE("SpawnMonsters") {
	//REQUIRE();
}

TEST_CASE("MoveMonsters") {
	app.SpawnMonsters();

	//REQUIRE();
}

TEST_CASE("MovePlayerLeft") {
	app.player.LocationBottomRight.SetX(4);
	app.player.LocationBottomRight.SetY(4);
	app.player.LocationTopLeft.SetX(2);
	app.player.LocationTopLeft.SetY(2);
	app.MovePlayer('A');
	REQUIRE(app.player.LocationBottomRight.GetX == 3);
	REQUIRE(app.player.LocationBottomRight.GetY == 4);
	REQUIRE(app.player.LocationTopLeft.GetX == 1);
	REQUIRE(app.player.LocationTopLeft.GetY == 2);
}

TEST_CASE("MovePlayerRight") {
	app.player.LocationBottomRight.SetX(4);
	app.player.LocationBottomRight.SetY(4);
	app.player.LocationTopLeft.SetX(2);
	app.player.LocationTopLeft.SetY(2);
	app.MovePlayer('D');
	REQUIRE(app.player.LocationBottomRight.GetX == 5);
	REQUIRE(app.player.LocationBottomRight.GetY == 4);
	REQUIRE(app.player.LocationTopLeft.GetX == 3);
	REQUIRE(app.player.LocationTopLeft.GetY == 1);
}

TEST_CASE("CheckValidMonsterMoveSimple") {
	//REQUIRE();
}

TEST_CASE("CheckValidMonsterMoveHard") {
	//REQUIRE();
}

TEST_CASE("LocationInBounds") {
	
}

TEST_CASE("LocationOutOfBounds") {

}