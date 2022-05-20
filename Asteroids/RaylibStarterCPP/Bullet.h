#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	~Bullet();

	// A constructor for generating new bullets at the player's location.
	Bullet(Vector2* shipPos, float shipRot);

	// Used for moving the bullets.
	void Update();

	// Used for drawing the bullet to the screen.
	void Draw();

private:
	// How fast the bullet should be travelling.
	float shootSpeed = 15;

	// The amount of frames that the bullet has existed for, and how many frames it can exist for before being destroyed.
	int maxLife = 45;
	int lifeExpended = 0;
};

