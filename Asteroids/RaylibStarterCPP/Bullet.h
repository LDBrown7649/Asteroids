#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	// A bullet destructor
	~Bullet();

	// A constructor for generating new bullets at the player's location.
	Bullet(Vector2* shipPos, float shipRot);

	// Used for moving the bullets and checking if they should be removed.
	void Update();

private:
	// How fast the bullet should be travelling.
	float shootSpeed = 15;

	// The amount of frames that the bullet has existed for.
	int maxLifetime = 45;
	// How many frames the bullet can exist for before being destroyed.
	int lifeExpended = 0;
};

