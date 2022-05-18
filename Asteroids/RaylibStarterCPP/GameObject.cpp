#include "GameObject.h"


void GameObject::Draw()
{
	// Calculates the centre of the image.
	Vector2 drawPos = this->DrawOffset();

	// Draws the ship onto the screen.
	DrawTextureEx(img, drawPos, -rotation, scale, Color{ 255, 255, 255, 200 });
}

void GameObject::Update()
{
	// Moves in the direction of the bullet.
	pos.x += vel.x;
	pos.y += vel.y;

	// Allows the game object to wrap around the screen and appear on the other side if it goes off screen.
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


// A function for checking if collisions have occurred between any two game objects (using circle collision logic).
void GameObject::CheckCollision(GameObject* other)
{
	// Calculates the distance between the centres of both objects.
	Vector2 vectBetween = { pos.x - other->pos.x, pos.y - other->pos.y };
	float sqrDist = vectBetween.x * vectBetween.x + vectBetween.y * vectBetween.y;

	// Checks if the distance between the centres is less than the radii of the shapes.
	if (sqrDist < (GetSize() + other->GetSize()) * (GetSize() + other->GetSize()) / 4) {

		// Sets the collided flag to true on both objects, indicating a collision.
		collided = true;
		other->collided = true;
	}
}