#include "PlayerShip.h"

PlayerShip::PlayerShip()
{
	// Loads the associated image of the ship.
	img = LoadTexture("Images/Ship.png");
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

void PlayerShip::OnDraw()
{
	// Moves the position of the object to be centred along the top edge.
	Vector2 drawPos = { pos.x - cos(rotation * 0.0174533f) * img.width * scale / 2, pos.y + sin(rotation * 0.0174533f) * img.height * scale / 2 };

	// Moves the position of the object to be centred along the side edge.
	drawPos.x -= sin(rotation * 0.0174533f) * img.width * scale / 2;
	drawPos.y -= cos(rotation * 0.0174533f) * img.width * scale / 2;

	// Draws the ship onto the screen.
	DrawTextureEx(img, drawPos, -rotation, scale, WHITE);

	// Draws each bullet to the screen (if there are bullets to draw).
	if (!bulletQueue.empty()) {
		for (Bullet* bullet : bulletQueue) {
			bullet->Draw();
		}
	}
}

void PlayerShip::OnUpdate()
{
	// Converts the rotation from degrees to radians.
	float Rad = rotation * 0.01745f;

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

	// Applies velocity to position.
	pos.y += vel.y;
	pos.x += vel.x;

	// Allows the ship to wrap around the screen if it goes out of bounds.
	if (pos.x > 800 + img.height / 2 * scale) {
		pos.x -= 800;
	}
	if (pos.x < -img.height / 2 * scale) {
		pos.x += 800;
	}
	if (pos.y > 800 + img.height / 2 * scale) {
		pos.y -= 800;
	}
	if (pos.y  < -img.height / 2 * scale) {
		pos.y += 800;
	}

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
