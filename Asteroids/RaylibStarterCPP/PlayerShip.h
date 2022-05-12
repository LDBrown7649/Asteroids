#pragma once

#include "raylib.h"'
#include "Bullet.h"

class PlayerShip
{
public:
	PlayerShip();
	~PlayerShip();

	void OnDraw();
	void OnUpdate();

private:
	Bullet* activeBullet;
	void Shoot();
	Vector2 pos = { 400, 400 };
	Vector2 vel = { 0.f, 0.f };
	Vector2 accel = { 0.f, 0.f };

	Texture img;

	float rotation = 0;
	float rotSpeed = 2.f;
	float accelSpeed = -0.15f;

	float scale = 0.25f;

	int lives = 3;
};

