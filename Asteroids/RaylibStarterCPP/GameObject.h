#pragma once

#include "raylib.h"
#include <math.h>


class GameObject
{
public:
	// A method for drawing the player to the screen.
	virtual void Draw();

	// A method for updating the player's position.
	virtual void Update();

	// A function for calculating the draw offset.
	Vector2 DrawOffset();

	// A function for returning the object's centre point.
	Vector2 GetPos() { return pos; }

	float GetSize() { return scale * img.width; }

protected:
	// The image representing the bullet.
	Texture img = Texture();

	// Stores the bullet's current position in the world.
	Vector2 pos = { 0, 0 };

	// The vector representing the bullet's velocity.
	Vector2 vel = { 0, 0 };

	// The rotation and scale of the bullet, used for rendering.
	float scale = 1.f;
	float rotation = 0;
};

