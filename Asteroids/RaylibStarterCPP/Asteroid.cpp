#include "Asteroid.h"

Asteroid::Asteroid()
{
	// Determines a random value from which other values will be generated.
	int randomValue = rand();

	// Loads one of the asteroid images (randomly chosen from the 3 options).
	std::string imgAddress = "Images/Asteroid" + std::to_string(randomValue % 3) + ".png";
	img = LoadTexture(imgAddress.c_str());

	// Chooses a random direction for the asteroid to travel in.
	float moveAngle = (float)(randomValue % 360) * DEG2RAD;
	// Determines rotation independent of moveAngle so that two asteroids travelling in the same direction will have different rotations.
	rotation = (float)(rand() % 360);

	// Chooses a random speed between minSpeed and maxSpeed
	float speed = minSpeed + (float)(randomValue % 100) / 100 * (maxSpeed - minSpeed);
	
	// Uses the moveAngle and speed values to determine the asteroid's 2D velocity.
	vel = { cos(moveAngle) * speed, sin(moveAngle) * speed };

	// Determines the initial position of the asteroid.
	CalculateInitialPosition();

	// Sets the health and scale of the asteroid.
	health = 3;
	scale = 2.4f;
}

Asteroid::Asteroid(Asteroid* parent)
{
	// Determines a random value from which other values will be generated.
	int randomValue = rand();

	// Loads one of the asteroid images.
	std::string imgAddress = "Images/Asteroid" + std::to_string(randomValue % 3) + ".png";
	img = LoadTexture(imgAddress.c_str());

	// Randomly determines the initial direction for the new asteroid (chosen at random).
	float moveAngle = (float)(randomValue % 360) * DEG2RAD;
	// Determines rotation independent of moveAngle so that two asteroids travelling in the same direction will have different rotations.
	rotation = (float)(rand() % 360);
	Vector2 randomDirection = { cos(moveAngle), sin(moveAngle) };

	// Sets the asteroid's position to be the same as the parent's position.
	pos = parent->pos;

	// Determines the normalised direction vector of the parent asteroid by dividing the velocity by the magnitude.
	float parentMagnitude = sqrt(parent->vel.x * parent->vel.x + parent->vel.y * parent->vel.y);
	Vector2 parentDirection = { parent->vel.x / parentMagnitude, parent->vel.y / parentMagnitude };

	// Determines the direction of the asteroid based on the existing asteroid's direction and a random "deflection" direction.
	Vector2 newDirection = CalculateDeflection(&parentDirection, &randomDirection);

	// Determines the speed of the asteroid as a value between minSpeed and maxSpeed.
	float speed = minSpeed + (float)(rand() % 100) / 100 * (maxSpeed - minSpeed);

	// Sets the velocity based on the new direction.
	vel = { newDirection.x * speed, newDirection.y * speed };

	// Sets this asteroid to have one less health than the parent asteroid had.
	health = parent->health - 1;

	// Sets the scale of the asteroid based on its remaining health.
	scale = health * 0.8f;
}

Asteroid::~Asteroid()
{
	// Unloads the asteroid image.
	UnloadTexture(img);
}

int Asteroid::GetHealth()
{
	return health;
}

int Asteroid::GetPoints()
{
	// Determines how many points should be awarded based on the size of the asteroid.
	// Smaller asteroids award more points.
	return basePoints * (4 - health);
}

void Asteroid::CalculateInitialPosition() {

	// Randomly chooses an edge for the asteroid to spawn at.
	int randNum = rand();
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

Vector2 Asteroid::CalculateDeflection(Vector2* parentVector, Vector2* deflectionVector) {

	// Find the dot product of the parent direction with the initial direction for the new asteroid.
	float vectorDotProduct = parentVector->x * deflectionVector->x + parentVector->y * deflectionVector->y;

	// If the dot product is less than 0, the vectors must be facing away from each other.
	if (vectorDotProduct < 0) {
		// Reverse the direction of the new vector if it faces away from the parent vector.
		*deflectionVector = { -deflectionVector->x, -deflectionVector->y };
	}

	// Gets the weighted average of the two direction vectors to determine the new direction of the asteroid.
	// A "deflection weighting" is applied to the new vector, and a "parent weighting" is applied to the parent's direction vector.
	// The ratio of these weights can be changed to modify the influence the parent or the new direction vector has on the new direction.
	Vector2 averageVector = {
		(deflectionVector->x * deflectionWeighting + parentVector->x * parentWeighting) / (deflectionWeighting * parentWeighting),
		(deflectionVector->y * deflectionWeighting + parentVector->y * parentWeighting) / (deflectionWeighting * parentWeighting)
	};

	// Normalises the average vector and returns this value.
	float averageVecMag = sqrt(averageVector.x * averageVector.x + averageVector.y * averageVector.y);
	averageVector = { averageVector.x / averageVecMag, averageVector.y / averageVecMag };
	return averageVector;
}
