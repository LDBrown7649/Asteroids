#pragma once
#include "Asteroid.h"
#include <vector>
class AsteroidHandler
{
private:
	// A vector of pointers to asteroid objects.
	std::vector<Asteroid*> asteroids;

	// The number of asteroids generated when new asteroids are required.
	int numAsteroids = 1;

	// The maximum number of asteroids that the game can create when no asteroids currently exist.
	int maxNumAsteroids = 6;

	// Tracks the amount of frames since there were asteroids in the screen.
	int timeSinceAsteroids = 0;

	// The maximum number of frames that can pass before the game repopulates the asteroid vector.
	int maxTimeSinceAsteroids = 60;

	// Splits an asteroid into smaller pieces, or destroys it completely depending on its size.
	void BreakAsteroid(int asteroidNum, int* numAsteroids);

public:
	// Updates the position and state of each asteroid.
	void Update();

	// Removes all asteroids from the scene.
	void Clear();

	// Draws the asteroids to the screen.
	void DrawAsteroids();

	// Draws and updates the asteroids without handling any collisions or game logic.
	void MenuAsteroidUpdate();

	// Returns a pointer to the asteroids in the asteroid handler.
	std::vector<Asteroid*>* GetAsteroids() { return &asteroids; }
};

