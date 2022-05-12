#pragma once

#include <queue>
#include "raylib.h"'
#include "Bullet.h"
#include <math.h>

class PlayerShip
{
public:
	// A constructor and destructor for the player ship class.
	PlayerShip();
	~PlayerShip();

	// A method for drawing the player to the screen.
	void OnDraw();

	// A method for updating the player's position.
	void OnUpdate();

private:
	// A double-ended queue, allowing for access to all bullets currently on the screen.
	std::deque<Bullet*> bulletQueue;

	// A method for creating and storing bullets.
	void Shoot();

	int maxBullets = 5;

	// Vectors representing the ship's position, velocity, and acceleration.
	Vector2 pos = { 400, 400 };
	Vector2 vel = { 0.f, 0.f };
	Vector2 accel = { 0.f, 0.f };

	// The image representing the player's ship.
	Texture img;

	// The rotation and scale of the player's ship.
	float rotation = 0;
	float scale = 0.2f;

	// The speed at which the player can turn/accelerate
	float rotSpeed = 2.f;
	float accelSpeed = -0.12f;

	// A value representing the drag of the ship, slowing the ship down.
	float drag = 0.99f;

	// The amount of lives that the player has remaining. The game ends when lives = 0.
	int lives = 3;
};

