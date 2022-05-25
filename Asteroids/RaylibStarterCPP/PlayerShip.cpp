#include "PlayerShip.h"

PlayerShip::PlayerShip()
{
	// Resets the ship's position to the centre of the screen.
	Reset();
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
	// Controls how visible the ship is to allow for a "fade-in" effect after respawning.
	Color drawColor = { visibility, visibility, visibility, visibility };
	// Calculates the centre of the image.
	Vector2 drawPos = this->DrawOffset();

	// Draws the player's lives to the screen in the form of miniature ships in the top left.
	for (int i = 0; i < lives; i++) {
		DrawTextureEx(img, { (30.f * i), 30 }, 0, scale / 2, WHITE);
	}

	// Draws the ship's texture to the screen, choosing which one to draw based on if the ship is accelerating or not.
	DrawTextureEx(accelerating ? MovingImage : img, drawPos, -rotation, scale, drawColor);

	// Draws each bullet to the screen (if there are bullets to draw).
	if (!bulletQueue.empty()) {
		for (Bullet* bullet : bulletQueue) {
			bullet->Draw();
		}
	}
}

void PlayerShip::Reset()
{
	// Sets the ship's velocity, position, and rotation to default values.
	vel = { 0,0 };
	pos = { 300, 300 };
	rotation = 0;

	// Sets the collision and invincibility information to default states.
	collided = false;
	immune = true;

	// Sets the ship's visibility to fully transparent
	visibility = 0;
}

void PlayerShip::Update()
{
	// Resets acceleration to 0.
	accel = { 0, 0 };
	accelerating = false;

	// Continuously increases the visibility of the ship until it is fully visible.
	if (visibility != 255) {
		visibility += 5;
	}
	// Make the ship immune if it is not fully visible.
	else {
		immune = false;
	}
	CheckUserInput();
	// Applies acceleration to velocity.
	vel.y += accel.y;
	vel.x += accel.x;
	// Applies drag to velocity.
	vel.x *= drag;
	vel.y *= drag;

	// Applies velocity to position and checks for screen wrapping.
	GameObject::Update();

	// Updates the bullets' positions if the bullet queue is not empty.
	if (!bulletQueue.empty()) {
		UpdateBullets();
	}
	// If the ship has collided with an asteroid, reset its position to 0 and lose one health.
	if (collided) {
		Reset();
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

void PlayerShip::CheckUserInput() {
	// Converts the rotation from degrees to radians.
	float Rad = rotation * DEG2RAD;

	// Adds to or subtracts from rotation if the A or D key is pressed.
	if (IsKeyDown(KEY_A)) {
		rotation += rotSpeed;
	}
	if (IsKeyDown(KEY_D)) {
		rotation -= rotSpeed;
	}

	// Accelerates forwards if the W key is pressed.
	if (IsKeyDown(KEY_W)) {
		accel.y = (float)cos(Rad) * accelSpeed;
		accel.x = (float)sin(Rad) * accelSpeed;
		accelerating = true;
	}

	// Fires a bullet from the front of the player's ship.
	if (IsKeyPressed(KEY_SPACE)) {
		Shoot();
	}
}

void PlayerShip::UpdateBullets() {
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
