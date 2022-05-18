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
	Asteroid(int healthRemaining);

	Asteroid(Asteroid* as);

	// A method for accessing the asteroid's current health.
	int GetHealth() {
		return health;
	}

	int GetPointValue() { return pointValue; }

private:
	// The max speed that the asteroid can travel at.
	int maxSpeed = 3;

	// The asteroid's current health, representing how many times it can be broken apart before being destroyed.
	int health = 3;

	int pointValue = 500;
};

