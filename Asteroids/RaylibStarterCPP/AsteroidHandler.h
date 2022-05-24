#pragma once
#include "Asteroid.h"
#include <vector>
class AsteroidHandler
{
private:
	// A vector of pointers to asteroid objects.
	std::vector<Asteroid*> asteroids;
	int numAsteroids = 1;
	int maxNumAsteroids = 6;
	int timeSinceAsteroids = 0;
	int maxTimeSinceAsteroids = 60;
	void BreakAsteroid(int asteroidNum, int* numAsteroids);

public:
	void Update();
	void Clear();
	void DrawAsteroids();
	void MenuAsteroidUpdate();
	std::vector<Asteroid*>* GetAsteroids() { return &asteroids; }
};

