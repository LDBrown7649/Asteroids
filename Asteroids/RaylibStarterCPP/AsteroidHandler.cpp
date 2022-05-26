#include "AsteroidHandler.h"


void AsteroidHandler::BreakAsteroid(int asteroidNum, int* numAsteroids)
{
    // Checks if the asteroid has enough health to "split"
    if (asteroids[asteroidNum]->GetHealth() > 1) {
        // Adds a new asteroid to the end of the vector (based on the old asteroid).
        asteroids.push_back(new Asteroid(asteroids[asteroidNum]));
        // Creates a new asteroid based on the old asteroid values.
        Asteroid* tempAsteroid = new Asteroid(asteroids[asteroidNum]);
        // Deletes the existing asteroid and replaces it with the newly created one.
        delete asteroids[asteroidNum];
        asteroids[asteroidNum] = tempAsteroid;
    }
    else {
        // Deletes the existing asteroid.
        delete asteroids[asteroidNum];
        // Replaces the pointer at this index with the one at the end of the array.
        asteroids[asteroidNum] = asteroids[*numAsteroids - 1];
        // Removes the asteroid array's final value (after it is copied into the empty position in the vector).
        asteroids.pop_back();
    }
}

void AsteroidHandler::AddAsteroids()
{
    // Adds new asteroids to the scene until the correct number have been added
    for (int i = 0; i < numAsteroids; i++) {
        asteroids.push_back(new Asteroid());
    }
    // Increases the number of asteroids that will be created next time unless the maximum value has been reached.
    if (numAsteroids < maxNumAsteroids) {
        numAsteroids++;
    }
    // Resets the timer tracking how many frames have elapsed since asteroids were in the scene.
    framesSinceAsteroids = 0;
}

void AsteroidHandler::UpdateAsteroids()
{
    // Check the number of asteroids in the scene.
    int size = asteroids.size();
    if (size == 0) {
        if (framesSinceAsteroids >= maxFramesSinceAsteroids) {
            // If there have been no asteroids for a specified number of frames, add new asteroids.
            AddAsteroids();
        }
        else {
            // If there are no asteroids, but the required time period has not yet elapsed, 
            // increase the number of frames elapsed since asteroids were in the scene.
            framesSinceAsteroids++;
        }
    }
    else {
        // Check how many asteroids were previously collided with and should therefore "break".
        for (int i = 0; i < size; i++) {
            if (asteroids[i]->collided) {
                BreakAsteroid(i, &size);
                size = asteroids.size();
            }
            // Update the asteroids that did not break.
            else {
                asteroids[i]->Update();
            }
        }
    }
}

void AsteroidHandler::ClearAsteroids()
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
    // Draws each asteroid to the screen.
    for (Asteroid* asteroid : asteroids) {
        asteroid->Draw();
    }
}

void AsteroidHandler::MenuAsteroidUpdate()
{
    // Adds new background asteroids until at least 5 are in the scene.
    while (asteroids.size() < 5) {
        asteroids.push_back(new Asteroid());
    }

    // Moves and draws the asteroids.
    for (Asteroid* asteroid : asteroids) {
        asteroid->Update();
        asteroid->Draw();
    }
}

std::vector<Asteroid*>* AsteroidHandler::GetAsteroids()
{
    // Returns a pointer to the asteroids in this asteroid handler.
    return &asteroids;
}
