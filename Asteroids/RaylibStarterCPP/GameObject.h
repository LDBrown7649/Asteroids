#pragma once

#include "raylib.h"
#include <math.h>


class GameObject
{
public:

	// A boolean tracking whether or not a collision has occurred between two game objects.
	bool collided = false;

	// Draws the game object to the screen.
	virtual void Draw();

	// Updates the game object's position and checks if it has gone out of bounds.
	virtual void Update();

	// A function for calculating the position a texture must be drawn from.
	Vector2 DrawOffset();

	// A function for checking if this game object has collided with another game object.
	void CheckCollision(GameObject* other);

protected:
	// The image representing the game object.
	Texture img = Texture();

	// Stores the game object's current position on the screen.
	Vector2 pos = { 0, 0 };

	// The vector representing the game object's velocity.
	Vector2 vel = { 0, 0 };

	// The scale the game object should be drawn at.
	float scale = 1;

	// The rotation of the game object's texture.
	float rotation = 0;

	// Returns the width of the scaled image
	float GetWidth();

	// Returns the height of the scaled image
	float GetHeight();
};

