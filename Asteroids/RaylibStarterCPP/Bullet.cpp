#include "Bullet.h"

Bullet::~Bullet()
{
	// Unloads the bullet image.
	UnloadTexture(img);
}

void Bullet::Update()
{
	// Update the bullet's position based on its current velocity
	GameObject::Update();

	// Increase the lifeExpended variable, indicating another frame passing.
	lifeExpended++;

	// Set the collided flag to true if the bullet has existed for longer than maxLife allows, informing the program to remove the bullet.
	if (lifeExpended > maxLife) {
		collided = true;
	}
}

Bullet::Bullet(Vector2* shipPos, float shipRot)
{
	// Set the rotation of this bullet to be relative to the ship's rotation.
	rotation = shipRot + 90;

	// Convert the ship's rotation from degrees to radians.
	float rotRad = shipRot * DEG2RAD;

	// Calculate the forward vector for this bullet based on the ship's rotation.
	vel = { -(float)sin(rotRad), -(float)cos(rotRad) };

	// Set the position of this bullet to be the ship's front "nose-cone".
	pos = *shipPos;
	pos.x -= sin(rotRad) * 20;
	pos.y -= cos(rotRad) * 20;

	// Load the image related to this bullet.
	img = LoadTexture("Images/Bullet.png");

	// Set the correct velocity of the bullet.
	vel.x *= shootSpeed;
	vel.y *= shootSpeed;
}

void Bullet::Draw()
{
	// Draws the bullet to the screen in the correct position.
	DrawTextureEx(img, pos, -rotation, scale, WHITE);
}
