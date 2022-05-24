#include "GameObject.h"


void GameObject::Draw()
{
	// Calculates the centre of the image.
	Vector2 drawPos = this->DrawOffset();

	// Draws the game object onto the screen.
	DrawTextureEx(img, drawPos, -rotation, scale, Color{ 255, 255, 255, 200 });
}

void GameObject::Update()
{
	// Moves the game object according to its current velocity.
	pos.x += vel.x;
	pos.y += vel.y;

	// Makes the player appear on the opposite edge if they leave the screen bounds.
	if (pos.x > 600 + (float)img.height / 2 * scale) {
		pos.x -= (600 + (float)img.width * scale);
	}
	if (pos.x < (float)-img.height / 2 * scale) {
		pos.x += (600 + (float)img.width * scale);
	}
	if (pos.y > 600 + (float)img.height / 2 * scale) {
		pos.y -= (600 + (float)img.width * scale);
	}
	if (pos.y < (float)-img.height / 2 * scale) {
		pos.y += (600 + (float)img.width * scale);
	}
}

Vector2 GameObject::DrawOffset()
{
	// The distance from the edge of the object to the centre.
	float widthMoveDist = GetWidth() / 2;
	float heightMoveDist = GetHeight() / 2;

	// Moves the position of the object to be centred along the top edge.
	Vector2 centredVec = { 
		pos.x - (float)cos((rotation)*DEG2RAD) * widthMoveDist, 
		pos.y + (float)sin((rotation)*DEG2RAD) * widthMoveDist 
	};

	// Moves the position of the object to be centred along the side edge.
	centredVec.x -= (float)sin((rotation)*DEG2RAD) * heightMoveDist;
	centredVec.y -= (float)cos((rotation)*DEG2RAD) * heightMoveDist;

	return centredVec;
}


// A function for checking if collisions have occurred between any two game objects.
void GameObject::CheckCollision(GameObject* other)
{
	// Calculates the distance between the centres of both objects.
	Vector2 vectBetween = { pos.x - other->pos.x, pos.y - other->pos.y };
	float sqrDist = vectBetween.x * vectBetween.x + vectBetween.y * vectBetween.y;

	// Checks if the distance between the centres is less than the radii of the shapes.
	if (sqrDist < ((GetWidth() * GetWidth()) + (other->GetWidth() * other->GetWidth())) / 2) {

		// Sets the "collided" flag to true on both objects, indicating a collision.
		collided = true;
		other->collided = true;
	}
}