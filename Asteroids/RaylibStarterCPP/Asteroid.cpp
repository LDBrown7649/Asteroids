#include "Asteroid.h"

Asteroid::~Asteroid()
{
	// Unloads the asteroid image.
	UnloadTexture(img);
}

Asteroid::Asteroid()
{
	// Determines a random value from which other values will be generated.
	int randomValue = rand();

	// Loads one of the asteroid images (randomly chosen from the 3 options).
	std::string imgAddress = "Images/Asteroid" + std::to_string(randomValue % 3) + ".png";
	img = LoadTexture(imgAddress.c_str());

	// Chooses a random direction for the asteroid to travel in.
	float moveAngle = (float)(randomValue % 360) * DEG2RAD;
	// Chooses a random speed between minSpeed and maxSpeed
	float speed = minSpeed + (float)(randomValue % 100) / 100 * (maxSpeed - minSpeed);
	vel = { cos(moveAngle) * speed, sin(moveAngle) * speed };

	CalculateDirection(randomValue);

	// Sets the rotation, scale, and health of the asteroid.
	rotation = moveAngle * RAD2DEG;
	scale = 2.4f;
	health = 3;
	collided = false;
}

Asteroid::Asteroid(Asteroid* parent)
{
	// Determines a random value from which other values will be generated.
	int randomValue = rand();

	// Randomly determines the initial speed and direction for the new asteroid.
	float moveAngle = (float)(randomValue % 360) * DEG2RAD;
	rotation = moveAngle * RAD2DEG;
	Vector2 initDirection = { cos(moveAngle), sin(moveAngle) };


	// Sets the asteroid's position to be the parent's position.
	pos = parent->pos;

	// Determines the direction vector of the parent asteroid by dividing the velocity by the magnitude.
	float parentMagnitude = sqrt(parent->vel.x * parent->vel.x + parent->vel.y * parent->vel.y);
	Vector2 parentDirection = { parent->vel.x / parentMagnitude, parent->vel.y / parentMagnitude };


	// Sets the velocity, health, and collision status of the new asteroid.
	vel = CalculateDeflection(&parentDirection, &initDirection);
	health = parent->health - 1;
	collided = false;

	// Loads one of the asteroid images.
	std::string imgAddress = "Images/Asteroid" + std::to_string(randomValue % 3) + ".png";
	img = LoadTexture(imgAddress.c_str());

	// Sets the scale of the asteroid based on its remaining health.
	scale = health * 0.8f;
}

Vector2 Asteroid::CalculateDeflection(Vector2* parentVector, Vector2* deflectionVector) {
	float speed = minSpeed + (float)(rand() % 100) / 100 * (maxSpeed - minSpeed);

	// Find the dot product of the parent direction with the initial direction for the new asteroid.
	float vectorDotProduct = parentVector->x * deflectionVector->x + parentVector->y * deflectionVector->y;

	// Use the dot product to determine if the two direction vectors are facing in the same or opposite directions.
	if (vectorDotProduct < 0) {
		// Reverse the direction of the new vector if it faces away from the parent vector.
		*deflectionVector = { -deflectionVector->x, -deflectionVector->y };
	}

	// Gets the weighted average of the two direction vectors to determine the new direction of the asteroid.
	// A "deflection weighting" is applied to the new vector, and a "parent weighting" is applied to the parent's direction vector.
	// The ratio of these weights can be changed to modify how much the new direction is affected by the parent vs the new direction vector.
	Vector2 averageVector = {
		(deflectionVector->x * deflectionWeighting + parentVector->x * parentWeighting) / (deflectionWeighting * parentWeighting),
		(deflectionVector->y * deflectionWeighting + parentVector->y * parentWeighting) / (deflectionWeighting * parentWeighting)
	};

	// Normalises the average vector and applies the speed value calculated previously.
	float averageVecMag = sqrt(averageVector.x * averageVector.x + averageVector.y * averageVector.y);
	averageVector = { averageVector.x / averageVecMag * speed, averageVector.y / averageVecMag * speed };
	return averageVector;
}

void Asteroid::CalculateDirection(int randNum) {
	// Randomly chooses an edge for the asteroid to spawn at.
	en_Edges edgeBorder = (en_Edges)(randNum % 4);

	switch (edgeBorder) {
		// Places a new asteroid at a random location along the top edge.
	case en_Edges::Top:
		pos = { (float)(randNum % 600), -img.width * scale };
		// Ensures that the largest component of velocity is perpendicular to the screen edge rather than parallel.
		if (abs(vel.x) > abs(vel.y)) {
			vel = { vel.y, vel.x };
		}
		break;
		// Places a new asteroid at a random location along the bottom edge.
	case en_Edges::Bottom:
		pos = { (float)(randNum % 600), 600 + img.width * scale };
		if (abs(vel.x) > abs(vel.y)) {
			vel = { vel.y, vel.x };
		}
		break;
		// Places a new asteroid at a random location along the left edge.
	case en_Edges::Left:
		pos = { -img.width * scale, (float)(randNum % 600) };
		if (abs(vel.x) < abs(vel.y)) {
			vel = { vel.y, vel.x };
		}
		break;
		// Places a new asteroid at a random location along the right edge.
	case en_Edges::Right:
		pos = { 600 + img.width * scale, (float)(randNum % 600) };
		if (abs(vel.x) < abs(vel.y)) {
			vel = { vel.y, vel.x };
		}
		break;
	}
}
