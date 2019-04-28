#define CATCH_CONFIG_MAIN
#include "Catch.h"
#include "C:\Users\djlaw\source\repos\final-project-lawal21\FinalProject\final-project-lawal21\src\ofApp.h"

ofApp app;


TEST_CASE("SpawnMonsters") {
	REQUIRE();
}

TEST_CASE("MoveMonsters") {
	app.SpawnMonsters();

	REQUIRE();
}

TEST_CASE("MovePlayerLeft") {
	app.player.locationBR.SetX(4);
	app.player.locationBR.SetY(4);
	app.player.locationTL.SetX(2);
	app.player.locationTL.SetY(2);
	app.MovePlayer('A');
	REQUIRE(app.player.locationBR.GetX == 3);
	REQUIRE(app.player.locationBR.GetY == 4);
	REQUIRE(app.player.locationTL.GetX == 1);
	REQUIRE(app.player.locationTL.GetY == 2);
}

TEST_CASE("MovePlayerRight") {
	app.player.locationBR.SetX(4);
	app.player.locationBR.SetY(4);
	app.player.locationTL.SetX(2);
	app.player.locationTL.SetY(2);
	app.MovePlayer('D');
	REQUIRE(app.player.locationBR.GetX == 5);
	REQUIRE(app.player.locationBR.GetY == 4);
	REQUIRE(app.player.locationTL.GetX == 3);
	REQUIRE(app.player.locationTL.GetY == 1);
}

TEST_CASE("CheckValidMonsterMoveSimple") {
	REQUIRE();
}

TEST_CASE("CheckValidMonsterMoveHard") {
	REQUIRE();
}
