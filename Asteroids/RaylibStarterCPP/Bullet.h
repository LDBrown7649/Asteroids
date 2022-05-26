#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	/// <summary> A constructor for generating new bullets at the player's location. </summary>
	/// <param name = "shipPos">: The position of the ship that is firing the bullet.</param>
	/// <param name = "shipRot">: The rotation of the ship that is firing the bullet.</param>
	Bullet(Vector2* shipPos, float shipRot);

	// A bullet destructor for unloading the bullet image.
	~Bullet();

	// Used for moving the bullets and checking if they have exceeded their lifespan.
	void Update();

private:
	// The speed of the bullet object.
	float shootSpeed = 15;

	// How many frames the bullet can exist for before being destroyed.
	int maxLifetime = 45;

	// The amount of frames that the bullet has existed for.
	int lifeExpended = 0;
};