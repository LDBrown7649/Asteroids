#include "PlayerShip.h"
#include <math.h>

PlayerShip::PlayerShip()
{
	img = LoadTexture("Images/ShipBetter.png");
}

PlayerShip::~PlayerShip()
{
	UnloadTexture(img);
	delete activeBullet;
}

void PlayerShip::OnDraw()
{
	// Moves the position of the object to be centred along the top edge.
	Vector2 drawPos = { pos.x - cos(rotation * 0.0174533f) * img.width * scale / 2, pos.y + sin(rotation * 0.0174533f) * img.height * scale / 2 };

	// Moves the position of the object to be centred along the side edge.
	drawPos.x -= sin(rotation * 0.0174533f) * img.width * scale / 2;
	drawPos.y -= cos(rotation * 0.0174533f) * img.width * scale / 2;

	DrawTextureEx(img, drawPos, -rotation, scale, WHITE);
	if(activeBullet != nullptr)
	activeBullet->Draw();
}

void PlayerShip::OnUpdate()
{
	float Rad = rotation * 0.01745f;
	// Resets acceleration to 0.
	accel = { 0, 0 };

	if (IsKeyDown(KEY_A)) {
		rotation += rotSpeed;
	}
	if(IsKeyDown(KEY_D))  {
		rotation -= rotSpeed;
	}
	if (IsKeyDown(KEY_W)) {
		accel.y = cos(Rad) * accelSpeed;
		accel.x = sin(Rad) * accelSpeed;
	}
	else if (IsKeyDown(KEY_ENTER)) {
		accel.y = -cos(Rad) * accelSpeed;
		accel.x = -sin(Rad) * accelSpeed;
	}
	if (IsKeyPressed(KEY_SPACE)) {
		Shoot();
	}
	vel.y += accel.y;
	vel.x += accel.x;

	vel.x *= 0.99f;
	vel.y *= 0.99f;

	pos.y += vel.y;
	pos.x += vel.x;

	if (pos.x > 800) {
		pos.x -= 800;
	}
	if (pos.x < 0) {
		pos.x += 800;
	}
	if (pos.y > 800) {
		pos.y -= 800;
	}
	if (pos.y  < 0) {
		pos.y += 800;
	}
	if(activeBullet != nullptr)
	activeBullet->Update();
}

void PlayerShip::Shoot()
{
	delete activeBullet;
	activeBullet = new Bullet(&pos, rotation);
}
