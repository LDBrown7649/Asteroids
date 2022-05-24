#include "AsteroidHandler.h"

/// <param name="asteroidIndex">The index of the asteroid to be removed</param>
/// <param name="numAsteroids">A reference to the current number of existing asteroids.</param>
void AsteroidHandler::BreakAsteroid(int asteroidNum, int* numAsteroids)
{
    // Checks if the asteroid has any health remaining
    if (asteroids[asteroidNum]->GetHealth() > 1) {
        // Adds a new asteroid to the end of the vector.
        asteroids.push_back(new Asteroid(asteroids[asteroidNum]));

        // Creates a new asteroid pointer
        Asteroid* tempAsteroid = new Asteroid(asteroids[asteroidNum]);

        // Deletes the existing asteroid and replaces it with the one currently at the end of the array.
        delete asteroids[asteroidNum];
        asteroids[asteroidNum] = asteroids[(*numAsteroids) - 1];

        // Sets the asteroid at the end of the array to the new asteroid pointer.
        asteroids[(*numAsteroids) - 1] = tempAsteroid;

        // Shows that the total number of asteroids in the scene has increased by 1
        (*numAsteroids)++;
    }

    else {
        // Deletes the existing asteroid.
        delete asteroids[asteroidNum];

        // Replaces the pointer at this index with the one at the end of the array.
        asteroids[asteroidNum] = asteroids[*numAsteroids - 1];

        // Removes the asteroid array's final value (after it is moved to fill the empty place).
        asteroids.pop_back();

        // Shows that the total number of asteroids in the scene has decreased by 1
        (*numAsteroids)--;
    }
}

void AsteroidHandler::Update()
{
    int size = asteroids.size();
    if (size == 0) {
        // If there have been no asteroids for a specified number of frames, add new asteroids.
        if (timeSinceAsteroids >= maxTimeSinceAsteroids) {

            // Adds new asteroids to the scene until the correct number have been added
            for (int i = 0; i < numAsteroids; i++) {
                asteroids.push_back(new Asteroid());
            }
            // Increases the number of asteroids that will be created next time unless the maximum value has been reached.
            if (numAsteroids < maxNumAsteroids) {
                numAsteroids++;
            }
            // Resets the timer tracking how many frames have elapsed since asteroids were in the scene.
            timeSinceAsteroids = 0;
        }
        // Otherwise, increase the number of frames elapsed since asteroids were in the scene.
        else {
            timeSinceAsteroids++;
        }
    }
    else {
        // Check how many asteroids were previously collided with and should therefore "break".
        for (int i = 0; i < size; i++) {
            if (asteroids[i]->collided) {
                BreakAsteroid(i, &size);
            }
            // Update the asteroid if it did not break.
            else {
                asteroids[i]->Update();
            }
        }
    }
}

void AsteroidHandler::Clear()
{
    // Deletes each asteroid before clearing the asteroid vector.
    for (Asteroid* asteroid : asteroids) {
        delete asteroid;
        asteroid = nullptr;
    }
    asteroids.clear();
    numAsteroids = 1;
}

void AsteroidHandler::DrawAsteroids()
{
    for (Asteroid* asteroid : asteroids) {
        asteroid->Draw();
    }
}

void AsteroidHandler::MenuAsteroidUpdate()
{
    // Adds new background asteroids until 5 are in the scene.
    while (asteroids.size() < 5) {
        asteroids.push_back(new Asteroid());
    }

    // Moves and draws the asteroids.
    for (Asteroid* asteroid : asteroids) {
        asteroid->Update();
        asteroid->Draw();
    }
}
