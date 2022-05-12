#pragma once
#include "raylib.h"
#include <math.h>
class Bullet
{
public:
	Bullet();
	~Bullet();
	void Update();
	Bullet(Vector2* shipPos, float shipRot);
	void Draw();

private:
	Vector2 pos = { 400.f, 225.f };
	Vector2 shootDirection = {0, 0};
	float shootSpeed = 2.5f;
	Texture img;
	float scale = 0.5f;

	float rot;

};

