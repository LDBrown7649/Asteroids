#include "Bullet.h"

Bullet::~Bullet()
{
	// Unloads the bullet image.
	UnloadTexture(img);
}

void Bullet::Update()
{
	// Moves in the direction of the bullet.
	pos.x += shootVector.x;
	pos.y += shootVector.y;

	// Allows the bullet to wrap around the screen and appear on the other side if it goes off screen.
	if (pos.x > 800 + img.height / 2 * scale) {
		pos.x -= 800;
	}
	if (pos.x < -img.height / 2 * scale) {
		pos.x += 800;
	}
	if (pos.y > 800 + img.height / 2 * scale) {
		pos.y -= 800;
	}
	if (pos.y < -img.height / 2 * scale) {
		pos.y += 800;
	}

	// Increases the lifeExpended variable, indicating another frame passing.
	lifeExpended++;

	// Sets the remove flag to true if the bullet has existed for longer than maxLife allows.
	if (lifeExpended > maxLife) {
		remove = true;
	}
}

Bullet::Bullet(Vector2* shipPos, float shipRot)
{
	// Sets the rotation of this bullet to be relative to the ship's rotation.
	rot = shipRot + 90;

	// Converts the ship's rotation from degrees to radians.
	float rotRad = shipRot * DEG2RAD;

	// Calculates the forward vector for this bullet based on the ship's rotation.
	shootVector = { -(float)sin(rotRad), -(float)cos(rotRad) };

	// Sets the position of this bullet to be the ship's front "nose-cone".
	pos = *shipPos;
	pos.x -= sin(rotRad) * 20.f;
	pos.y -= cos(rotRad) * 20.f;

	// Loads the image related to this bullet.
	img = LoadTexture("Images/Bullet.png");

	// Sets the correct velocity of the bullet.
	shootVector.x *= shootSpeed;
	shootVector.y *= shootSpeed;
}

void Bullet::Draw()
{
	Vector2 drawPos = DrawOffset();
	// Draws the bullet to the screen in the correct position.
	DrawTextureEx(img, pos, -rot, scale, WHITE);
	DrawCircle(pos.x, pos.y, 2, RED);
}

Vector2 Bullet::DrawOffset()
{
	// Moves the position of the object to be centred along the top edge.
	Vector2 centredVec = { pos.x - cos((rot) * DEG2RAD) * img.width * scale / 2, pos.y + sin((rot) * DEG2RAD) * img.height * scale / 2 };

	// Moves the position of the object to be centred along the side edge.
	centredVec.x -= sin((rot) * DEG2RAD) * img.width * scale / 2;
	centredVec.y -= cos((rot) * DEG2RAD) * img.width * scale / 2;

	return centredVec;
}
