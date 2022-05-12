#pragma once
#include "raylib.h"
#include <math.h>
class Bullet
{
public:
	// Bullet constructors and a destructor.
	Bullet();
	~Bullet();
	Bullet(Vector2* shipPos, float shipRot);

	// Used for moving the bullets.
	void Update();

	// Used for drawing the bullet to the screen.
	void Draw();

private:
	// Stores the bullet's current position in the world.
	Vector2 pos = { 0, 0 };

	// The vector representing the bullet's velocity.
	Vector2 shootVector = {0, 0};

	// How fast the bullet should be travelling.
	float shootSpeed = 11.f;
	Texture img;
	float scale = 0.5f;

	float rot;

};

