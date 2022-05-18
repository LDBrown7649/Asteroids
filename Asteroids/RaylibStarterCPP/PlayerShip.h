#pragma once

#include <queue>
#include "Bullet.h"
#include "GameObject.h"

class PlayerShip : public GameObject
{
public:
	// A constructor and destructor for the player ship class.
	PlayerShip();
	~PlayerShip();

	void Update();

	void Draw();

	// A method for returning the queue of bullets.
	std::deque<Bullet*>* GetBullets() { return &bulletQueue; }

private:
	// A double-ended queue, allowing for access to all bullets currently on the screen.
	std::deque<Bullet*> bulletQueue;

	// A method for creating and storing bullets.
	void Shoot();

	Texture MovingImage;

	int maxBullets = 3;
	Vector2 accel = { 0.f, 0.f };

	// The speed at which the player can turn/accelerate
	float rotSpeed = 4.f;
	float accelSpeed = -0.2f;

	// A value representing the drag of the ship, slowing the ship down.
	float drag = 0.98f;

	// The amount of lives that the player has remaining. The game ends when lives = 0.
	int lives = 3;

	bool thrusting = false;
};

