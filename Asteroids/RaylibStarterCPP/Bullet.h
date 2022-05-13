#pragma once
#include "raylib.h"
#include <math.h>
class Bullet
{
public:
	~Bullet();

	// A constructor for generating new bullets at the player's location.
	Bullet(Vector2* shipPos, float shipRot);
	
	// A flag for verifying if this object should be destroyed.
	bool remove = false;

	// Used for moving the bullets.
	void Update();

	// Used for drawing the bullet to the screen.
	void Draw();

	// A function for calculating the draw offset.
	Vector2 DrawOffset();

	// A function for returning the object's centre point.
	Vector2 GetPos() { return pos; }

	float GetSize() { return scale * img.width; }

private:
	// Stores the bullet's current position in the world.
	Vector2 pos = { 0, 0 };

	// The vector representing the bullet's velocity.
	Vector2 shootVector = {0, 0};

	// How fast the bullet should be travelling.
	float shootSpeed = 15;

	// The image representing the bullet.
	Texture img = Texture();

	// The rotation and scale of the bullet, used for rendering.
	float scale = 1.f;
	float rot = 0;

	// The amount of frames that the bullet has existed for, and how many frames it can exist for before being destroyed.
	int maxLife = 300;
	int lifeExpended = 0;


};

