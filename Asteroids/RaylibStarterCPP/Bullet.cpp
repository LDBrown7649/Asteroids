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
	pos.x += shootDirection.x;
	pos.y += shootDirection.y;
}

Bullet::Bullet(Vector2* shipPos, float shipRot)
{
	rot = shipRot;
	shipRot *= 0.0174533;
	pos = *shipPos;
	pos.x += cos(shipRot) * 12.5f;
	pos.y -= sin(shipRot) * 12.5f;
	img = LoadTexture("Images/Bullet.png");
	shootDirection = { -(float)sin(shipRot), -(float)cos(shipRot) };
	shootDirection.x *= shootSpeed;
	shootDirection.y *= shootSpeed;
}

void Bullet::Draw()
{
	DrawTextureEx(img, pos, -rot + 90, scale, WHITE);
}
