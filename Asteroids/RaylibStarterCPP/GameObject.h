#pragma once

#include "raylib.h"
#include <math.h>


class GameObject
{
public:

	// A boolean reflecting whether or not a collision has occurred between two game objects.
	bool collided = false;

	// A method for drawing the game object to the screen.
	virtual void Draw();

	// A method for updating the game object's position.
	virtual void Update();

	// A function for calculating the draw offset.
	Vector2 DrawOffset();

	// A function for returning the object's centre point.
	Vector2 GetPos() { return pos; }

	// A function for setting the position of a game object.
	void SetPos(Vector2 value) { pos = value; }

	// A function for checking if this game object has collided with another game object.
	void CheckCollision(GameObject* other);

protected:
	// The image representing the game object.
	Texture img = Texture();

	// Stores the game object's current position in the world.
	Vector2 pos = { 0, 0 };

	// The vector representing the game object's velocity.
	Vector2 vel = { 0, 0 };

	// The rotation and scale of the game object
	float scale = 1;
	float rotation = 0;

	// Functions for getting the width and height of the game object on the screen.
	float GetWidth() { return scale * img.width; }
	float GetHeight() { return scale * img.height; }
};

