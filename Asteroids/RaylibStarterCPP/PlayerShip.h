#pragma once

#include <queue>
#include "Bullet.h"

class PlayerShip : public GameObject
{
public:
	// A boolean tracking if the ship is immune from collisions or not
	bool immune = false;

	// A default PlayerShip constructor for loading both images and setting the scale and position of the ship.
	PlayerShip();

	// A PlayerShip destructor for unloading both images and clearing the bullet queue from memory.
	~PlayerShip();

	// Updates the player's velocity, position and other attributes.
	void Update();

	// Resets the player's velocity, position and other attributes to a default state.
	void Reset();

	// Draws the ship and all currently active bullets.
	void Draw();

	// Returns a pointer to the bullet queue
	std::deque<Bullet*>* GetBullets();

	// Returns the number of lives that the player currently has.
	int GetLives();

private:
	// A double-ended queue consisting of pointers to bullets.
	std::deque<Bullet*> bulletQueue;

	// The image to show if the player is accelerating
	Texture MovingImage;

	// The maximum amount of bullets allowed on the screen at a time.
	int maxBullets = 3;

	// The player's acceleration vector.
	Vector2 accel = { 0.f, 0.f };

	// The speed at which the player can rotate the ship.
	float rotSpeed = 4.f;

	// The speed at which the player can accelerate.
	float accelSpeed = -0.2f;

	// A value representing the drag experienced by the ship. Higher values mean less drag (between 0 and 1).
	float drag = 0.98f;

	// The amount of lives that the player has remaining. The game ends when lives = 0.
	int lives = 3;

	// A boolean for tracking when the player is accelerating.
	bool accelerating = false;

	// The RGBA value for the ship's texture. This value increases from 0 to 255 gradually after player respawn.
	short visibility = 255;

	// Updates the ship's rotation and acceleration based on player input.
	void CheckUserInput();

	// A method for creating and storing bullets.
	void Shoot();

	// A method for updating all bullets in the bullet queue.
	void UpdateBullets();
};

