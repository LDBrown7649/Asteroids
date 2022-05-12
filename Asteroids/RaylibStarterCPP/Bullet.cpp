#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
	UnloadTexture(img);
}

void Bullet::Update()
{
	pos.x += shootVector.x;
	pos.y += shootVector.y;

	if (pos.x > 600) {
		pos.x -= 600;
	}
	if (pos.x < 0) {
		pos.x += 600;
	}
	if (pos.y > 600) {
		pos.y -= 600;
	}
	if (pos.y < 0) {
		pos.y += 600;
	}
}

Bullet::Bullet(Vector2* shipPos, float shipRot)
{
	rot = shipRot;
	shipRot *= 0.0174533;
	pos = *shipPos;
	pos.x -= sin(shipRot) * 12.5f;
	pos.y -= cos(shipRot) * 12.5f;
	img = LoadTexture("Images/Bullet.png");
	shootVector = { -(float)sin(shipRot), -(float)cos(shipRot) };
	shootVector.x *= shootSpeed;
	shootVector.y *= shootSpeed;
}

void Bullet::Draw()
{
	DrawTextureEx(img, pos, -rot + 90, scale, WHITE);
}
