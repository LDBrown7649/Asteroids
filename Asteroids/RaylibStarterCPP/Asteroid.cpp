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

	int edgeBorder = rand() % 4;

	switch (edgeBorder) {
	// Places a new rock along the top edge.
	case 0:
		pos.x = rand() % 600;
		pos.y = -img.width * scale;
		break;
	// Places a new rock along the bottom edge.
	case 1:
		pos.x = rand() % 600;
		pos.y = 600 + img.width * scale;
		break;
	// Places a new rock along the left edge.
	case 2:
		pos.x = -img.width * scale;
		pos.y = rand() % 600;
		break;
	// Places a new rock along the right edge.
	case 3:
		pos.x = 600 + img.width * scale;
		pos.y = rand() % 600;
		break;
	}

	

	float moveAngle = (float)(rand() % 360) * DEG2RAD;

	float speed = (float)((maxSpeed * (rand() % 5)) / 4 + 1);

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
	float speed = (float)((maxSpeed * (rand() % 5)) / 4 + 1);
	// Sets the rotation, scale, and health.
	rotation = moveAngle * RAD2DEG;
	vel = { cos(moveAngle) * speed, sin(moveAngle) * speed };
	health = as->health - 1;
	collided = false;

	std::string imgAddress = "Images/Asteroid" + std::to_string(rand() % 3) + ".png";
	img = LoadTexture(imgAddress.c_str());

	scale = health * 0.8f;
}
