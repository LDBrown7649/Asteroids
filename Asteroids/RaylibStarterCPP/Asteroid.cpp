#include "Asteroid.h"


Asteroid::~Asteroid()
{
	// Unloads the asteroid image.
	UnloadTexture(img);
}

Asteroid::Asteroid(int healthRemaining, int seed)
{
	// Seeds the random generation based on the seed received.
	srand(seed);
	// Loads the default asteroid image.
	std::string imgAddress = "Images/Asteroid" + std::to_string(rand() % 3) + ".png";
	img = LoadTexture(imgAddress.c_str());

	// Randomly generates the values of the asteroid.
	pos = { (float)(rand() % 800), (float)(rand() % 800) };

	float moveAngle = (float)(rand() % 360) * DEG2RAD;

	float speed = (rand() % maxSpeed * 100) / 100 + 1;

	vel = { cos(moveAngle) * speed, sin(moveAngle) * speed };

	// Sets the rotation, scale, and health.
	rotation = moveAngle * RAD2DEG;

	scale = pow(2, healthRemaining) * 0.25f;

	health = healthRemaining;
}

void Asteroid::Draw()
{
	// Draws the asteroid to the screen
	DrawTextureEx(img, pos, -rotation, scale, WHITE);
}

void Asteroid::Update()
{
	// Moves in the direction of the bullet.
	pos.x += vel.x;
	pos.y += vel.y;

	// Allows the asteroid to wrap around the screen and appear on the other side if it goes off screen.
	if (pos.x > 800) {
		pos.x -= 800;
	}
	if (pos.x < 0) {
		pos.x += 800;
	}
	if (pos.y > 800) {
		pos.y -= 800;
	}
	if (pos.y < 0) {
		pos.y += 800;
	}
}
