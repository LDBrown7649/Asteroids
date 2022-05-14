#include "Asteroid.h"


Asteroid::~Asteroid()
{
	// Unloads the asteroid image.
	UnloadTexture(img);
}

Asteroid::Asteroid(int healthRemaining)
{
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

	collided = false;
}

Asteroid::Asteroid(Asteroid* as)
{
	pos = as->pos;
	float moveAngle = (float)(rand() % 360) * DEG2RAD;
	float speed = (float)((rand() % maxSpeed * 100) / 100 + 1);
	// Sets the rotation, scale, and health.
	rotation = moveAngle * RAD2DEG;
	vel = { cos(moveAngle) * speed, sin(moveAngle) * speed };
	health = as->health - 1;
	collided = false;

	std::string imgAddress = "Images/Asteroid" + std::to_string(rand() % 3) + ".png";
	img = LoadTexture(imgAddress.c_str());

	scale = health * 0.8f;
}
