#include "PlayerShip.h"

PlayerShip::PlayerShip()
{
	// Resets the ship's position to the centre of the screen.
	ResetPosition();
	scale = 0.25f;
	// Loads both images associated with the ship (when accelerating and when not accelerating).
	MovingImage = LoadTexture("Images/shipThrusting.png");
	img = LoadTexture("Images/ship.png");
}

PlayerShip::~PlayerShip()
{
	// Unloads the ship textures from memory.
	UnloadTexture(img);
	UnloadTexture(MovingImage);

	// Deletes all bullets in the queue and clears it.
	for (Bullet* bullet : bulletQueue) {
		delete bullet;
		bullet = nullptr;
	}
	bulletQueue.clear();
}

void PlayerShip::Draw()
{
	// Calculates the centre of the image.
	Vector2 drawPos = this->DrawOffset();

	for (int i = 0; i < lives; i++) {
		DrawTextureEx(img, { (30.f * i), 30 }, 0, scale / 2, WHITE);
	}

	// Draws the ship's texture to the screen, choosing which one to draw based on if the ship is accelerating or not.
	DrawTextureEx(accelerating ? MovingImage : img, drawPos, -rotation, scale, WHITE);

	// Draws each bullet to the screen (if there are bullets to draw).
	if (!bulletQueue.empty()) {
		for (Bullet* bullet : bulletQueue) {
			bullet->Draw();
		}
	}
}

void PlayerShip::ResetPosition()
{
	// Sets the ship's velocity, position, and rotation to default values.
	vel = { 0,0 };
	pos = { 300, 300 };
	rotation = 0;
}

void PlayerShip::Update()
{
	// Converts the rotation from degrees to radians.
	float Rad = rotation * DEG2RAD;

	// Resets acceleration to 0.
	accel = { 0, 0 };
	accelerating = false;

	// Adds to or subtracts from rotation if the A or D key is pressed.
	if (IsKeyDown(KEY_A)) {
		rotation += rotSpeed;
	}
	if(IsKeyDown(KEY_D))  {
		rotation -= rotSpeed;
	}

	// Accelerates forwards if the W key is pressed.
	if (IsKeyDown(KEY_W)) {
		accel.y = (float)cos(Rad) * accelSpeed;
		accel.x = (float)sin(Rad) * accelSpeed;
		accelerating = true;
	}
	
	// Applies acceleration to velocity.
	vel.y += accel.y;
	vel.x += accel.x;

	// Applies drag to velocity.
	vel.x *= drag;
	vel.y *= drag;

	// Applies velocity to position
	GameObject::Update();

	// Fires a bullet from the front of the player's ship.
	if (IsKeyPressed(KEY_SPACE)) {
		Shoot();
	}

	// Checks if there are bullets in the queue.
	if (!bulletQueue.empty()) {
		int size = bulletQueue.size();
		for (int i = 0; i < size; i++) {
			if (bulletQueue[i]->collided) {

				// Replaces this value with the value at the end of the queue
				delete bulletQueue[i];
				bulletQueue[i] = bulletQueue.back();

				// Removes the end value.
				bulletQueue.pop_back();

				// Decreases the size value to reflect the queue losing a value.
				size--;

				// Decrements i, ensuring that the new value will be checked before moving on in the for loop.
				i--;
			}
		}
		// Updates each remaining bullet's position.
		for (Bullet* bullet : bulletQueue) {
			bullet->Update();
		}
		
	}

	// If the ship has collided with an asteroid, reset its position to 0 and lose one health.
	if (collided) {
		collided = false;
		ResetPosition();
		lives--;
	}
}

void PlayerShip::Shoot()
{
	// Removes the first bullet in the queue if the queue is full
	if ((int)bulletQueue.size() >= maxBullets) {
		delete bulletQueue.front();
		bulletQueue.front() = nullptr;
		bulletQueue.pop_front();
	}

	// Creates a new bullet and adds it to the queue.
	bulletQueue.push_back(new Bullet(&pos, rotation));
}
