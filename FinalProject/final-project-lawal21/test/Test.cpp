//#define CATCH_CONFIG_MAIN
#include "Catch.h"
#include "C:\Users\djlaw\source\repos\final-project-lawal21\FinalProject\final-project-lawal21\src\ofApp.h"
/*
ofApp app;

TEST_CASE("LocationMoveUp") {
	Location location = Location(5, 5);
	location.MoveUp(5);
	REQUIRE(location.GetY() == 10);
}

TEST_CASE("LocationMoveDown") {
	Location location = Location(5, 5);
	location.MoveUp(5);
	REQUIRE(location.GetY() == 0);
}

TEST_CASE("LocationMoveLeft") {
	Location location = Location(5, 5);
	location.MoveLeft(5);
	REQUIRE(location.GetX() == 0);
}

TEST_CASE("LocationMoveRight") {
	Location location = Location(5, 5);
	location.MoveLeft(5);
	REQUIRE(location.GetX() == 10);
}

TEST_CASE("MovePlayerLeft") {
	app.player.LocationBottomRight.SetX(4);
	app.player.LocationBottomRight.SetY(4);
	app.player.LocationTopLeft.SetX(2);
	app.player.LocationTopLeft.SetY(2);
	app.MovePlayer('A');
	REQUIRE(app.player.LocationBottomRight.GetX() == 3);
	REQUIRE(app.player.LocationBottomRight.GetY() == 4);
	REQUIRE(app.player.LocationTopLeft.GetX() == 1);
	REQUIRE(app.player.LocationTopLeft.GetY() == 2);
}

TEST_CASE("MovePlayerRight") {
	app.player.LocationBottomRight.SetX(4);
	app.player.LocationBottomRight.SetY(4);
	app.player.LocationTopLeft.SetX(2);
	app.player.LocationTopLeft.SetY(2);
	app.MovePlayer('D');
	REQUIRE(app.player.LocationBottomRight.GetX() == 5);
	REQUIRE(app.player.LocationBottomRight.GetY() == 4);
	REQUIRE(app.player.LocationTopLeft.GetX() == 3);
	REQUIRE(app.player.LocationTopLeft.GetY() == 1);
}

TEST_CASE("CheckValidMonsterMoveRight") {
	app.SpawnMonsters();
	REQUIRE(true == app.CheckValidMonsterMove(app.monsters_move_right));
}

TEST_CASE("CheckValidMonsterMoveLeft") {
	app.SpawnMonsters();
	for (int i = 0; i < 10; i++) {
		app.MoveMonsters();
	}
	app.monsters_move_right = false;
	REQUIRE(true == app.CheckValidMonsterMove(app.monsters_move_right));
}

TEST_CASE("CheckValidMonsterMoveFalse") {
	app.SpawnMonsters();
	app.monsters_move_right = false;
	REQUIRE(false == app.CheckValidMonsterMove(app.monsters_move_right));
}

TEST_CASE("LocationInBounds") {
	Location pixel = Location(5, 5);
	Location bound1 = Location(3, 4);
	Location bound2 = Location(7, 9);
	REQUIRE(app.PixelWithinBounds(pixel, bound1, bound2));
}

TEST_CASE("LocationOutOfBounds") {
	Location pixel = Location(10, 5);
	Location bound1 = Location(3, 4);
	Location bound2 = Location(7, 9);
	REQUIRE(app.PixelWithinBounds(pixel, bound1, bound2));
}
*/