#include "PlayerShip.h"

PlayerShip::PlayerShip()
{
	// Loads the associated image of the ship.
	img = LoadTexture("Images/Ship.png");
	pos = { 400, 400 };
	scale = 0.2f;
}

PlayerShip::~PlayerShip()
{
	// Unloads the ship texture from memory.
	UnloadTexture(img);

	// Removes all of the bullets in the queue from memory.
	for (Bullet* bullet : bulletQueue) {
		delete bullet;
		bullet = nullptr;
	}
	// Clears the queue.
	bulletQueue.clear();
}

void PlayerShip::Draw()
{
	GameObject::Draw();

	// Draws each bullet to the screen (if there are bullets to draw).
	if (!bulletQueue.empty()) {
		for (Bullet* bullet : bulletQueue) {
			bullet->Draw();
		}
	}
}

void PlayerShip::Update()
{
	// Converts the rotation from degrees to radians.
	float Rad = rotation * DEG2RAD;

	// Resets acceleration to 0.
	accel = { 0, 0 };

	// Adds to or subtracts from rotation if the A or D key is pressed.
	if (IsKeyDown(KEY_A)) {
		rotation += rotSpeed;
	}
	if(IsKeyDown(KEY_D))  {
		rotation -= rotSpeed;
	}

	// Accelerates forwards if the W key is pressed.
	if (IsKeyDown(KEY_W)) {
		accel.y = cos(Rad) * accelSpeed;
		accel.x = sin(Rad) * accelSpeed;
	}

	// Accelerates backwards if the S key is pressed
	else if (IsKeyDown(KEY_S)) {
		accel.y = -cos(Rad) * accelSpeed;
		accel.x = -sin(Rad) * accelSpeed;
	}
	
	// Applies acceleration to velocity.
	vel.y += accel.y;
	vel.x += accel.x;

	// Applies drag to velocity.
	vel.x *= drag;
	vel.y *= drag;

	GameObject::Update();

	// Fires a bullet from the front of the player's ship.
	if (IsKeyPressed(KEY_SPACE)) {
		Shoot();
	}

	// Checks if there are bullets in the queue.
	if (!bulletQueue.empty()) {

		// Removes every bullet in the queue that has existed for too long.
		while (bulletQueue.front()->remove) {
			delete bulletQueue.front();
			bulletQueue.front() = nullptr;
			bulletQueue.pop_front();

			// Ends the loop if the bullet queue is empty.
			if (bulletQueue.empty()) {
				break;
			}
		}
		// Updates each remaining bullet's position.
		for (Bullet* bullet : bulletQueue) {
			bullet->Update();
		}
		
	}
}

void PlayerShip::Shoot()
{
	// Removes the first bullet in the queue if the queue is full
	if (bulletQueue.size() >= maxBullets) {
		delete bulletQueue.front();
		bulletQueue.front() = nullptr;
		bulletQueue.pop_front();
	}

	// Creates a new bullet and adds it to the queue.
	bulletQueue.push_back(new Bullet(&pos, rotation));
}
