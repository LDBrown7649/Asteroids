#include "GameObject.h"

void GameObject::Draw()
{
	// Calculates the centre of the image.
	Vector2 drawPos = this->DrawOffset();

	// Draws the ship onto the screen.
	DrawTextureEx(img, drawPos, -rotation, scale, WHITE);
}

void GameObject::Update()
{
	// Moves in the direction of the bullet.
	pos.x += vel.x;
	pos.y += vel.y;

	// Allows the bullet to wrap around the screen and appear on the other side if it goes off screen.
	if (pos.x > 600 + img.height / 2 * scale) {
		pos.x -= (600 + img.width * scale);
	}
	if (pos.x < -img.height / 2 * scale) {
		pos.x += (600 + img.width * scale);
	}
	if (pos.y > 600 + img.height / 2 * scale) {
		pos.y -= (600 + img.width * scale);
	}
	if (pos.y < -img.height / 2 * scale) {
		pos.y += (600 + img.width * scale);
	}
}

Vector2 GameObject::DrawOffset()
{
	float moveDist = img.width * scale / 2;
	// Moves the position of the object to be centred along the top edge.
	Vector2 centredVec = { pos.x - cos((rotation)*DEG2RAD) * moveDist, pos.y + sin((rotation)*DEG2RAD) * moveDist };

	// Moves the position of the object to be centred along the side edge.
	centredVec.x -= sin((rotation)*DEG2RAD) * moveDist;
	centredVec.y -= cos((rotation)*DEG2RAD) * moveDist;

	return centredVec;
}

void GameObject::CheckCollision(GameObject* other)
{
	Vector2 vectBetween = { pos.x - other->pos.x, pos.y - other->pos.y };
	float sqrDist = vectBetween.x * vectBetween.x + vectBetween.y * vectBetween.y;
	if (sqrDist < (GetSize() + other->GetSize()) * (GetSize() + other->GetSize()) / 4) {
		collided = true;
		other->collided = true;
	}
}
