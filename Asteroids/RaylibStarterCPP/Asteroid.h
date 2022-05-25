#pragma once

#include <random>
#include <string>
#include "GameObject.h"

// An enum associating integer values with edges of the screen.
enum class en_Edges {
	Top = 0,
	Bottom = 1,
	Left = 2,
	Right = 3
};

class Asteroid : public GameObject
{
public:
	// An asteroid Constructor and Destructor
	~Asteroid();

	// An asteroid constructor for creating new asteroids.
	Asteroid();

	// A constructor for making smaller asteroids based on larger asteroids (after collisions).
	Asteroid(Asteroid* as);

	// A method for accessing the asteroid's current health.
	int GetHealth() { return health; }

	// Returns a score associated with this asteroid, calculated so that smaller asteroids award more points.
	int GetPoints() { return basePoints * (4 - health); }


private:
	// The min and max speeds that the asteroid can travel at.
	float maxSpeed = 3.5f;
	float minSpeed = 2.f;

	// The asteroid's current health, representing how many times it can be broken apart before being destroyed.
	int health = 3;

	// The base amount of points awarded for destroying an asteroid.
	int basePoints = 100;

	Vector2 CalculateDeflection(Vector2* parentVector, Vector2* deflectionVector);

	void CalculateDirection(int randNum);

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  ///// The following values are used to determine the direction of new asteroids that are		  /////
  ///// created when existing asteroids "split". The higher the value, the more that factor will  /////
  ///// impact the new asteroid's direction (as a weighted average).							  /////
  /////////////////////////////////////////////////////////////////////////////////////////////////////
																									 //
	// How much the new asteroid's direction should be affected by the randomly chosen direction.	 //
	int deflectionWeighting = 4;																	 //
																									 //
	// How much the parent's direction should affect the direction of the new asteroid.				 //
	int parentWeighting = 3;																		 //
  /////////////////////////////////////////////////////////////////////////////////////////////////////
};

