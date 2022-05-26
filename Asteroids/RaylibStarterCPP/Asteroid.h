#pragma once

#include <random>
#include <string>
#include "GameObject.h"

class Asteroid : public GameObject
{
public:
	// An asteroid constructor for creating new asteroids along the screen edges.
	Asteroid();

	// A constructor for making smaller asteroids based on larger asteroids (after collisions).
	Asteroid(Asteroid* as);

	// An asteroid destructor. Unloads the asteroid image.
	~Asteroid();

	// A method for accessing the asteroid's current health.
	int GetHealth();

	// Returns a score associated with this asteroid, calculated so that smaller asteroids award more points.
	int GetPoints();


private:
	// The maximum speed of an asteroid
	float maxSpeed = 3.5f;

	// The minimum speed of the asteroid
	float minSpeed = 2.f;

	// An asteroid's current health, representing how many times it can be broken apart before being destroyed.
	int health = 3;

	// The base amount of points awarded for destroying an asteroid (before size modifiers change this value).
	int basePoints = 100;

	// Determines the initial position and direction of an asteroid.
	void CalculateInitialPosition();

	// An enum associating integer values with edges of the screen.
	enum class en_Edges {
		Top = 0,
		Bottom = 1,
		Left = 2,
		Right = 3
	};

	/// <summary>
	/// A function for determining the direction a smaller asteroid should travel in based on the direction of the previous, larger asteroid.
	/// The deflection vector is transformed to face in the same direction as the parent vector, and a weighted average of these two vectors
	/// is taken to determine the new direction of the asteroid.
	/// </summary>
	/// <param name="parentVector">: The existing asteroid's velocity direction vector</param>
	/// <param name="deflectionVector">: A second vector representing the "deflection" experienced by the new asteroid</param>
	/// <returns>A vector representing the "deflected" direction of the new asteroid, based on a weighted average of the two input vectors.</returns>
	Vector2 CalculateDeflection(Vector2* parentVector, Vector2* deflectionVector);

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  ////* The following values are used to influence the direction of new asteroids that are		    //
  ////* created when existing asteroids "split". The higher the value, the more influence that 		//
  ////* factor will have on the new asteroid's direction (as a weighted average).					//
  ////////////////////////////////////////////////////////////////////////////////////////////////////
																									//
	// How much the new asteroid's direction should be affected by the new direction.				//
	int deflectionWeighting = 4;																	//
																									//
	// How much the existing asteroid's direction should affect the direction of the new asteroid.	//
	int parentWeighting = 3;																		//
  ////////////////////////////////////////////////////////////////////////////////////////////////////
};

