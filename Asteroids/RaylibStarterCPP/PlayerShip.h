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
	Vector2 pos = { 300, 300 };
	Vector2 vel = { 0.f, 0.f };
	Vector2 accel = { 0.f, 0.f };

	Texture img;

	float rotation = 0;
	float rotSpeed = 1.5f;
	float accelSpeed = -0.1f;

	float scale = 0.5f;

	int lives = 3;
};

