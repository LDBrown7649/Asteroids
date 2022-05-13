#include "GameObject.h"

void GameObject::Draw()
{
	// Calculates the centre of the image.
	Vector2 drawPos = this->DrawOffset();

	// Draws the ship onto the screen.
	DrawTextureEx(img, drawPos, -rotation, scale, WHITE);
	DrawCircle(pos.x, pos.y, 5, RED);
}

void GameObject::Update()
{
	// Moves in the direction of the bullet.
	pos.x += vel.x;
	pos.y += vel.y;

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
}

Vector2 GameObject::DrawOffset()
{
	// Moves the position of the object to be centred along the top edge.
	Vector2 centredVec = { pos.x - cos((rotation)*DEG2RAD) * img.width * scale / 2, pos.y + sin((rotation)*DEG2RAD) * img.height * scale / 2 };

	// Moves the position of the object to be centred along the side edge.
	centredVec.x -= sin((rotation)*DEG2RAD) * img.width * scale / 2;
	centredVec.y -= cos((rotation)*DEG2RAD) * img.width * scale / 2;

	return centredVec;
}
