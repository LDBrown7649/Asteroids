#include "PlayerShip.h"

PlayerShip::PlayerShip()
{
	// Loads the associated image of the ship.
	ResetPosition();
	scale = 0.25f;
	MovingImage = LoadTexture("Images/shipThrusting.png");
	img = LoadTexture("Images/ship.png");
}

PlayerShip::~PlayerShip()
{
	// Unloads the ship texture from memory.
	UnloadTexture(img);

	UnloadTexture(MovingImage);

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
	// Calculates the centre of the image.
	Vector2 drawPos = this->DrawOffset();

	for (int i = 0; i < lives; i++) {
		DrawTextureEx(img, { (30.f * i), 30 }, 0, scale / 2, WHITE);
	}

	// Draws the ship onto the screen.
	DrawTextureEx(accelerating ? MovingImage : img, drawPos, -rotation, scale, WHITE);
	DrawCircle(pos.x, pos.y, 5, RED);

	// Draws each bullet to the screen (if there are bullets to draw).
	if (!bulletQueue.empty()) {
		for (Bullet* bullet : bulletQueue) {
			bullet->Draw();
		}
	}
}

void PlayerShip::ResetPosition()
{
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
		accel.y = cos(Rad) * accelSpeed;
		accel.x = sin(Rad) * accelSpeed;
		accelerating = true;
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
		int size = bulletQueue.size();
		for (int i = 0; i < size; i++) {
			if (bulletQueue[i]->collided) {

				// Replaces this value with the value at the end of the queue
				delete bulletQueue[i];
				bulletQueue[i] = bulletQueue.back();

				// Removes the end value.
				bulletQueue.pop_back();

				// Notes the decrease in the size of the array.
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

	if (collided) {
		collided = false;
		ResetPosition();
		lives--;
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
