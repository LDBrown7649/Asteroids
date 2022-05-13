#pragma once

#include <random>
#include <time.h>
#include <string>
#include "GameObject.h"


class Asteroid : public GameObject
{
public:
	// An asteroid Constructor and Destructor
	~Asteroid();

	// An asteroid constructor for creating smaller asteroids when a larger asteroid is destroyed.
	Asteroid(int healthRemaining, int seed);

	void Draw();

	// A method for accessing the asteroid's current health.
	int GetHealth() {
		return health;
	}

	// A boolean for tracking if a collision has occurred.
	bool collided = false;

private:
	// The max speed that the asteroid can travel at.
	int maxSpeed = 2;

	// The asteroid's current health, representing how many times it can be broken apart before being destroyed.
	int health = 3;
};

