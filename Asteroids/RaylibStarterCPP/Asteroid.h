#pragma once

#include <random>
#include <time.h>
#include <string>
#include "GameObject.h"


class Asteroid : public GameObject
{
public:
	// An asteroid Constructor and Destructor
	~Asteroid();

	// An asteroid constructor for creating smaller asteroids when a larger asteroid is destroyed.
	Asteroid();

	// A constructor for making smaller asteroids based on larger asteroids.
	Asteroid(Asteroid* as);

	// A method for accessing the asteroid's current health.
	int GetHealth() {
		return health;
	}

	// Returns a score associated with this asteroid, calculated so that smaller asteroids award more points.
	int GetPoints() { return basePoints * (6 - health); }


private:
	// The max speed that the asteroid can travel at.
	int maxSpeed = 3;

	// The asteroid's current health, representing how many times it can be broken apart before being destroyed.
	int health = 3;

	// The base amount of points awarded for destroying an asteroid.
	int basePoints = 50;

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  ///// The following values are included to determine the direction of new asteroids that are	  /////
  ///// created when existing asteroids "split". The higher the value, the more that factor will  /////
  ///// effect the new asteroid's direction (as a weighted average).							  /////
  /////////////////////////////////////////////////////////////////////////////////////////////////////
																									 //
	// How much the new asteroid's direction should be affected by random factors.					 //
	int deflectionWeighting = 3;																	 //
																									 //
	// How much the parent's direction should affect the direction of the new asteroid.				 //
	int parentWeighting = 2;																		 //
  /////////////////////////////////////////////////////////////////////////////////////////////////////
};

