#pragma once

#include "raylib.h"
#include <iostream>
#include <random>
#include <time.h>
#include <string>
#include <math.h>


class Asteroid
{
public:
	// An asteroid Constructor and Destructor
	~Asteroid();

	// An asteroid constructor for creating smaller asteroids when a larger asteroid is destroyed.
	Asteroid(int healthRemaining, int seed);

	// A method for drawing the asteroid to the screen.
	void Draw();

	// A method for moving the asteroids.
	void Update();

	// A method for accessing the asteroid's current health.
	int GetHealth() {
		return health;
	}

	// A boolean for tracking if a collision has occurred.
	bool collided = false;

	// A function for calculating the draw offset.
	Vector2 DrawOffset();

	// A function for returning the object's centre point.
	Vector2 GetPos() { return pos; }

	float GetSize() { return scale * img.width; }

private:
	// The position and velocity of the asteroid.
	Vector2 pos = { 0, 0 };
	Vector2 vel = { 0, 0 };

	// The image representing the asteroid model.
	Texture img = Texture();

	// The rotation and scale of the asteroid, used for drawing the asteroid.
	float rotation = 0;
	float scale = 0.5f;

	// The max speed that the asteroid can travel at.
	int maxSpeed = 2;

	// The asteroid's current health, representing how many times it can be broken apart before being destroyed.
	int health = 3;
};

