#include "PlayerShip.h"

PlayerShip::PlayerShip()
{
	// Resets the ship's position to the centre of the screen.
	Reset();

	visibility = 255;

	// Sets the scale of the ship object to 1/4 of the standard size.
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

void PlayerShip::Update()
{
	// Resets acceleration to 0.
	accel = { 0, 0 };
	accelerating = false;

	// Continuously increases the visibility of the ship until it is fully visible.
	if (visibility != 255) {
		visibility += 5;
	}
	else {
		// Set the immune bool to false if the ship is fully visible.
		immune = false;
	}

	// Checks for user input, updating acceleration and rotation accordingly.
	CheckUserInput();

	// Applies acceleration and drag to velocity.
	vel.y += accel.y;
	vel.x += accel.x;
	vel.x *= drag;
	vel.y *= drag;

	// Applies velocity to position.
	GameObject::Update();

	// Updates the bullets' positions if the bullet queue is not empty.
	if (!bulletQueue.empty()) {
		UpdateBullets();
	}
	// If the ship has collided with an asteroid, reset it and lose one health.
	if (collided) {
		Reset();
		lives--;
	}
}

void PlayerShip::Reset()
{
	// Sets the ship's velocity, position, and rotation to default values.
	vel = { 0,0 };
	pos = { 300, 300 };
	rotation = 0;

	// Sets the collision and immunity booleans to default states.
	collided = false;
	immune = true;

	// Sets the ship's visibility to 0 (fully transparent)
	visibility = 0;
}

void PlayerShip::Draw()
{
	// Controls the colour and transparency of the ship to allow for a "fade-in" effect after respawning.
	// After respawning, the visibility value will gradually increase from 0 (transparent and black) to 255 (opaque and white).
	Color drawColor = { visibility, visibility, visibility, visibility };

	// Draws the player's lives to the screen in the form of miniature ships in the top left.
	for (int i = 0; i < lives; i++) {
		DrawTextureEx(img, { (30.f * i), 30 }, 0, scale / 2, WHITE);
	}

	// Calculates the offset to begin drawing the texture from.
	Vector2 drawPos = this->DrawOffset();

	// Draws the ship's texture to the screen, choosing which one to draw based on if the ship is accelerating or not.
	DrawTextureEx(accelerating ? MovingImage : img, drawPos, -rotation, scale, drawColor);

	// Draws each bullet to the screen (if there are bullets to draw).
	if (!bulletQueue.empty()) {
		for (Bullet* bullet : bulletQueue) {
			bullet->Draw();
		}
	}
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

	// Accelerates in the direction of the ship's forward vector if the W key is pressed.
	if (IsKeyDown(KEY_W)) {
		accel.y = (float)cos(Rad) * accelSpeed;
		accel.x = (float)sin(Rad) * accelSpeed;
		accelerating = true;
	}

	// Fires a bullet from the front of the player's ship if the SPACE key is pressed.
	if (IsKeyPressed(KEY_SPACE)) {
		Shoot();
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

void PlayerShip::UpdateBullets() {
	int size = bulletQueue.size();
	for (int i = 0; i < size; i++) {
		// Checks if any of the bullets has been collided with.
		if (bulletQueue[i]->collided) {

			// Replaces this value with the value at the end of the queue
			delete bulletQueue[i];
			bulletQueue[i] = bulletQueue.back();

			// Removes the end value.
			bulletQueue.pop_back();

			// Reduces the value of size by 1 (since a value has been removed from the queue).
			size--;
		}
	}
	// Updates each remaining bullet's position.
	for (Bullet* bullet : bulletQueue) {
		bullet->Update();
	}
}

std::deque<Bullet*>* PlayerShip::GetBullets()
{
	return &bulletQueue;
}

int PlayerShip::GetLives()
{
	return lives;
}
