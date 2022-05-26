#include "Bullet.h"

Bullet::Bullet(Vector2* shipPos, float shipRot)
{
	// Set the rotation of this bullet to be relative to the ship's rotation.
	rotation = shipRot + 90;

	// Convert the ship's rotation from degrees to radians.
	float rotRadians = shipRot * DEG2RAD;

	// Calculate the forward vector for this bullet based on the ship's rotation.
	vel = { -(float)sin(rotRadians), -(float)cos(rotRadians) };

	// Set the position of this bullet to be the ship's front "nose-cone".
	pos = *shipPos;
	pos.x -= sin(rotRadians) * 20;
	pos.y -= cos(rotRadians) * 20;

	// Load the image related to this bullet.
	img = LoadTexture("Images/Bullet.png");

	// Set the correct velocity of the bullet.
	vel.x *= shootSpeed;
	vel.y *= shootSpeed;
}

Bullet::~Bullet()
{
	// Unloads the bullet image.
	UnloadTexture(img);
}

void Bullet::Update()
{
	// Update the bullet's position based on its velocity.
	GameObject::Update();

	// Increase the lifeExpended variable, indicating another frame passing.
	lifeExpended++;

	// Set the collided flag to true if the bullet has existed for longer than maxLife allows, informing the program to remove the bullet.
	if (lifeExpended > maxLifetime) {
		collided = true;
	}
}