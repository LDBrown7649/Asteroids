#pragma once

#include <queue>
#include "Bullet.h"

class PlayerShip : public GameObject
{
public:
	// A constructor and destructor for the player ship class.
	PlayerShip();
	~PlayerShip();

	// A method of updating the ship's position and rotation based on player input.
	void Update();

	// A method for drawing the ship to the screen.
	void Draw();

	// A method for returning the queue of bullets.
	std::deque<Bullet*>* GetBullets() { return &bulletQueue; }

	// Resets the player's position to the centre of the screen.
	void Reset();

	// Returns the number of lives that the player currently has.
	int GetLives() { return lives; }

	// A boolean tracking if the ship is immune from collisions or not
	bool immune = false;

private:
	// A double-ended queue consisting of pointers to bullets.
	std::deque<Bullet*> bulletQueue;

	// A method for creating and storing bullets.
	void Shoot();

	// The image to show if the player is accelerating
	Texture MovingImage;

	// The maximum amount of bullets allowed on the screen at a time.
	int maxBullets = 3;

	// The player's acceleration vector.
	Vector2 accel = { 0.f, 0.f };

	// The speed at which the player can turn/accelerate
	float rotSpeed = 4.f;
	float accelSpeed = -0.2f;

	// A value representing the drag of the ship.
	float drag = 0.98f;

	// The amount of lives that the player has remaining. The game ends when lives = 0.
	int lives = 3;

	// A boolean for tracking when the player is accelerating.
	bool accelerating = false;

	short visibility = 255;
};

