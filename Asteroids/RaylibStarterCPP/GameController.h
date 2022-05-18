#pragma once

#include <vector>
#include "Asteroid.h"
#include "PlayerShip.h"
#include "UFO.h"
#include <fstream>
#include <random>
#include <time.h>
#include "raylib.h"

class GameController
{
private:
	int currentScore = 0;

	int numAsteroids = 1;
	int maxNumAsteroids = 8;

	int timeSinceAsteroids = 0;
	int maxTimeSinceAsteroids = 60;

	int screenWidth = 600;
	int screenHeight = 600;

	std::vector<Asteroid*> asteroids;

	PlayerShip* ship;

public:
	GameController();
	~GameController();
	void PlayGame();

	void Setup();
	void Update();
	void Draw();
	void Shutdown();

	void CheckAsteroids();
	void SplitAsteroid(int asteroidIndex, int* numAsteroids);
	int GetScreenWidth() { return screenWidth; }
	int GetScreenHeight() { return screenHeight; }
	void CheckCollisions();
};

