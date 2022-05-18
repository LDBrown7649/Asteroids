#include "Bullet.h"

Bullet::~Bullet()
{
	// Unloads the bullet image.
	UnloadTexture(img);
}

void Bullet::Update()
{
	GameObject::Update();
	// Increases the lifeExpended variable, indicating another frame passing.
	lifeExpended++;

	// Sets the remove flag to true if the bullet has existed for longer than maxLife allows.
	if (lifeExpended > maxLife) {
		collided = true;
	}
}

Bullet::Bullet(Vector2* shipPos, float shipRot)
{
	// Sets the rotation of this bullet to be relative to the ship's rotation.
	rotation = shipRot + 90;

	// Converts the ship's rotation from degrees to radians.
	float rotRad = shipRot * DEG2RAD;

	// Calculates the forward vector for this bullet based on the ship's rotation.
	vel = { -(float)sin(rotRad), -(float)cos(rotRad) };

	// Sets the position of this bullet to be the ship's front "nose-cone".
	pos = *shipPos;
	pos.x -= sin(rotRad) * 20.f;
	pos.y -= cos(rotRad) * 20.f;

	// Loads the image related to this bullet.
	img = LoadTexture("Images/Bullet.png");

	// Sets the correct velocity of the bullet.
	vel.x *= shootSpeed;
	vel.y *= shootSpeed;
}

void Bullet::Draw()
{
	// Draws the bullet to the screen in the correct position.
	DrawTextureEx(img, pos, -rotation, scale, WHITE);
}
