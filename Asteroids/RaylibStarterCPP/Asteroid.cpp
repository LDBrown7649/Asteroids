#include "Asteroid.h"

// An enum associating integer values with edges of the screen.
enum en_Edges {
	Top = 0,
	Bottom = 1,
	Left = 2,
	Right = 3
};

Asteroid::~Asteroid()
{
	// Unloads the asteroid image.
	UnloadTexture(img);
}

Asteroid::Asteroid()
{
	// Loads one of the asteroid images (randomly chosen from the 3 options).
	std::string imgAddress = "Images/Asteroid" + std::to_string(rand() % 3) + ".png";
	img = LoadTexture(imgAddress.c_str());

	int randomValue = rand();

	// Chooses a random direction for the asteroid to travel in.
	float moveAngle = (float)(randomValue % 360) * DEG2RAD;

	// Chooses a random speed between 1 and maxSpeed
	float speed = (float)(randomValue % maxSpeed + 1);

	// Uses the direction and speed calculated to determine the velocity vector for this object.
	vel = { cos(moveAngle) * speed, sin(moveAngle) * speed };

	// Randomly chooses 
	int edgeBorder = randomValue % 4;

	switch (edgeBorder) {
	// Places a new asteroid along the top edge.
	case Top:
		pos.x = (float)(randomValue % 600);
		pos.y = -img.width * scale;

		// Ensures that the largest component of velocity is perpendicular to the screen edge rather than parallel.
		if (abs(vel.x) > abs(vel.y)) {
			vel = { vel.y, vel.x };
		}
		break;

	// Places a new asteroid along the bottom edge.
	case Bottom:
		pos.x = (float)(randomValue % 600);
		pos.y = 600 + img.width * scale;

		// Ensures that the largest component of velocity is perpendicular to the screen edge rather than parallel.
		if(abs(vel.x) > abs(vel.y)) {
			vel = { vel.y, vel.x };
		}
		break;

	// Places a new asteroid along the left edge.
	case Left:
		pos.x = -img.width * scale;
		pos.y = (float)(randomValue % 600);

		// Ensures that the largest component of velocity is perpendicular to the screen edge rather than parallel.
		if (abs(vel.x) < abs(vel.y)) {
			vel = { vel.y, vel.x };
		}
		break;

		// Places a new asteroid along the right edge.
	case Right:
		pos.x = 600 + img.width * scale;
		pos.y = (float)(randomValue % 600);

		// Ensures that the largest component of velocity is perpendicular to the screen edge rather than parallel.
		if (abs(vel.x) < abs(vel.y)) {
			vel = { vel.y, vel.x };
		}
		break;
	}

	// Sets the rotation, scale, and health.
	rotation = moveAngle * RAD2DEG;

	scale = 2.4f;

	health = 3;

	collided = false;
}

Asteroid::Asteroid(Asteroid* parent)
{
	int randomValue = rand();

	// Sets the asteroid's position to be the parent's position.
	pos = parent->pos;

	// Determines the direction vector of the parent asteroid by dividing the velocity by the magnitude.
	float parentMagnitude = sqrt(parent->vel.x * parent->vel.x + parent->vel.y * parent->vel.y);
	Vector2 parentDirection = { parent->vel.x / parentMagnitude, parent->vel.y / parentMagnitude };

	// Randomly determines the initial speed and direction for the new asteroid.
	float moveAngle = (float)(randomValue % 360) * DEG2RAD;
	float speed = (float)(randomValue % maxSpeed + 1.5f);
	rotation = moveAngle * RAD2DEG;
	Vector2 initDirection = { cos(moveAngle), sin(moveAngle) };

	// Find the dot product of the parent direction with the initial direction.
	float vectorDotProduct = parentDirection.x * initDirection.x + parentDirection.y * initDirection.y;

	// Use the dot product to determine if the two direction vectors are facing in the same or opposite directions.
	if (vectorDotProduct < 0) {
		// Reverse the direction if it is moving away from the parent's direction vector.
		initDirection = { -initDirection.x, -initDirection.y };
	}

	// Gets the weighted average of the two direction vectors to determine the new direction of the asteroid.
	// A "deflection weighting" is applied to the "initial" vector, and a "parent weighting" is applied to the parent's direction.
	// The ratio of these weights can be changed to modify how much the new direction is affected by the parent vs the initial direction.
	Vector2 averageVector = { 
		(initDirection.x * deflectionWeighting + parentDirection.x * parentWeighting) / (deflectionWeighting * parentWeighting), 
		(initDirection.y * deflectionWeighting + parentDirection.y * parentWeighting) / (deflectionWeighting * parentWeighting) 
	};

	// Normalises the average vector.
	float averageVecMag = sqrt(averageVector.x * averageVector.x + averageVector.y * averageVector.y);
	averageVector = { averageVector.x / averageVecMag * speed, averageVector.y / averageVecMag * speed };

	// Sets the velocity, health, and collision status of the new asteroid.
	vel = averageVector;
	health = parent->health - 1;
	collided = false;

	// Loads one of the asteroid images.
	std::string imgAddress = "Images/Asteroid" + std::to_string(randomValue % 3) + ".png";
	img = LoadTexture(imgAddress.c_str());

	// Sets the scale of the asteroid based on its remaining health.
	scale = health * 0.8f;
}
