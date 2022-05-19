#pragma once

#include <vector>
#include "Asteroid.h"
#include "PlayerShip.h"
#include "UFO.h"
#include <fstream>

enum class GameMode {
	Menu,
	Game,
	Score,
	Quit
};

class GameController
{
private:

	GameMode gamestate = GameMode::Menu;
	// The player's current score.
	int currentScore = 0;

	// The number of asteroids that should be spawned into the scene.
	int numAsteroids = 1;

	// A limit on the amount of asteroids that can be present in any scene.
	int maxNumAsteroids = 6;

	// Tracks how many frames have elapsed since the game had asteroids present.
	int timeSinceAsteroids = 0;

	// The maximum number of elapsed frames before more asteroids should be added.
	int maxTimeSinceAsteroids = 60;

	// The dimensions of the game window.
	int screenWidth = 600;
	int screenHeight = 600;

	int highscore = 0;

	std::string playerName = "Lachlan";

	std::string highscoreName = "";

	// A vector of pointers to asteroids.
	std::vector<Asteroid*> asteroids;

	// The player's ship that they control in the game.
	PlayerShip* ship;

	// Performs the necessary operations to set up for the game to begin 
	//(such as opening the game window, seeding the random generator, and setting the target fps).
	void Setup();

	// Checks for collisions or changes in the scene before moving each game object to its new location.
	void GameUpdate();

	// Draws each game object to the screen
	void GameDraw();

	void LoadMenu();

	void UpdateScores();

	void Scoreboard();

	// Frees any allocated memory that needs to be freed, and closes the game window.
	void Shutdown();

	// Checks for collisions between game objects (such as asteroids, bullets, and ships).
	void CheckCollisions();

	// Checks that the scene has the correct amount of asteroids, adding more or breaking existing ones as required.
	void CheckAsteroids();

	// Splits or removes asteroids from the scene when they are damaged.
	void BreakAsteroid(int asteroidIndex, int* numAsteroids);

	void GetScores();

	bool endgame = false;

	int scores[5] = {0,0,0,0,0};

	std::string names[5] = {"","","","",""};

	void ClearAsteroids();
	void ResetGame();

public:
	// Holds all game functionality.
	void PlayGame();
};

