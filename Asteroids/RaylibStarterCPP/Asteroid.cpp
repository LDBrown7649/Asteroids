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
	Vector2 drawPos = this->DrawOffset();
	// Draws the asteroid to the screen.
	// A red filter is currently applied to indicate collisions since asteroid breaking/player respawning is not yet implemented.
	DrawTextureEx(img, drawPos, -rotation, scale, collided ? RED : WHITE);
	DrawCircle(pos.x, pos.y, 5, RED);
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

	// Resets the collided flag, indicating that no collision is detected.
	collided = false;
}

Vector2 Asteroid::DrawOffset()
{
	// Moves the position of the object to be centred along the top edge.
	Vector2 centredVec = { pos.x - cos(rotation * DEG2RAD) * img.width * scale / 2, pos.y + sin(rotation * DEG2RAD) * img.height * scale / 2 };

	// Moves the position of the object to be centred along the side edge.
	centredVec.x -= sin(rotation * DEG2RAD) * img.width * scale / 2;
	centredVec.y -= cos(rotation * DEG2RAD) * img.width * scale / 2;

	return centredVec;
}
