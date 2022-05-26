#pragma once
#include "Asteroid.h"
#include <vector>
class AsteroidHandler
{
private:
	// A vector of pointers to asteroid objects.
	std::vector<Asteroid*> asteroids;

	// Tracks the amount of frames since there were asteroids in the screen.
	int framesSinceAsteroids = 0;

	// The maximum number of frames that can pass before the game repopulates the asteroid vector.
	int maxFramesSinceAsteroids = 60;

	// The number of asteroids generated when new asteroids are required.
	int numAsteroids = 1;

	// The maximum number of asteroids that the game can generate when new asteroids are required.
	int maxNumAsteroids = 8;

	/// <summary> Splits an asteroid into smaller pieces or destroys it completely depending on its size.</summary>
	/// <param name="asteroidIndex">The index of the asteroid to be removed</param>
	/// <param name="numAsteroids">A reference to the current number of existing asteroids.</param>
	void BreakAsteroid(int asteroidNum, int* numAsteroids);

	// Adds new asteroids to the scene if sufficient time has passed
	void AddAsteroids();

public:
	// Updates the position of each asteroid and handles collisions.
	void UpdateAsteroids();

	// Removes all asteroids from the scene.
	void ClearAsteroids();

	// Draws the asteroids to the screen.
	void DrawAsteroids();

	// Manages the asteroids in the background of the menus, updating their position and adding new ones if there are insufficient asteroids.
	void MenuAsteroidUpdate();

	// Allows other classes to access the asteroids inside the asteroid handler.
	std::vector<Asteroid*>* GetAsteroids();
};

