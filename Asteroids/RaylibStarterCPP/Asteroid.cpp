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

	float speed = (float)((rand() % maxSpeed * 100) / 100 + 1);

	vel = { cos(moveAngle) * speed, sin(moveAngle) * speed };

	// Sets the rotation, scale, and health.
	rotation = moveAngle * RAD2DEG;

	scale = healthRemaining * 0.8f;

	health = healthRemaining;
}

void Asteroid::Draw()
{
	// Calculates the centre of the image.
	Vector2 drawPos = this->DrawOffset();

	// Draws the ship onto the screen.
	DrawTextureEx(img, drawPos, -rotation, scale, collided ? RED : WHITE);
	DrawCircle(pos.x, pos.y, 5, RED);
	collided = false;
}
