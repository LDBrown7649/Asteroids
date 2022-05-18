#include "GameController.h"

void GameController::PlayGame()
{
    // Setup the required game features.
    Setup();

    // Continuously update and draw the game objects until the player closes the window or presses escape.
    while (!WindowShouldClose()) {
        Update();
        Draw();
    }

    // End the play loop and free any used memory.
    Shutdown();
}

void GameController::Setup()
{
    // Opens the window with the current screen width and height.
    InitWindow(screenWidth, screenHeight, "ASTEROIDS!");

    // Seeds the random generator.
    srand((int)time(nullptr));

    // Limits the game to running at 60 fps.
    SetTargetFPS(60);

    // Creates the ship that the player controls.
    ship = new PlayerShip();
}

void GameController::Update()
{
    // Checks which objects have collided with each other.
    CheckCollisions();
    // Checks which asteroids need to split or be removed.
    CheckAsteroids();

    // Updates each asteroid in the scene
    for (Asteroid* asteroid : asteroids) {
        asteroid->Update();
    }

    // Updates the ship (and the attached bullet objects)
    ship->Update();
}

void GameController::Draw()
{
    BeginDrawing();

    // Draws the player's current score to the screen and sets the background to be Black.
    ClearBackground(BLACK);
    DrawText(std::to_string(currentScore).c_str(), 20, 20, 20, WHITE);

    // Draws each asteroid, the ship, and the bullets (as part of the ship drawing process).
    for (Asteroid* asteroid : asteroids) {
        asteroid->Draw();
    }
    ship->Draw();


    EndDrawing();
}

void GameController::Shutdown()
{
    CloseWindow();

    // Deletes the ship and asteroids, and sets each pointer to the null pointer.
    delete ship;
    ship = nullptr;
    for(Asteroid * asteroid : asteroids) {
        delete asteroid;
        asteroid = nullptr;
    }
}

/// <summary>
/// Checks every asteroid in the scene, assessing whether more should be added or if existing asteroids should "break".
/// </summary>
void GameController::CheckAsteroids()
{
    // Checks the number of asteroids in the scene.
    int size = asteroids.size();
    if (size == 0) {
        // If there have been no asteroids for a specified period of frames, add new asteroids.
        if (timeSinceAsteroids >= maxTimeSinceAsteroids) {

            // Adds either the current number of asteroids or the maximum number (whichever is smaller).
            for (int i = 0; i < (numAsteroids < maxNumAsteroids ? numAsteroids : maxNumAsteroids); i++) {
                asteroids.push_back(new Asteroid());
            }
            // Increases the number of asteroids that will be created next time.
            numAsteroids++;

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
        }
    }
}

/// <summary>
/// Removes the asteroid at the specified index from the scene. If it had sufficient health, replace it with two
/// smaller "children" asteroids. Increases or decreases the number of existing asteroids to reflect the result.
/// </summary>
/// <param name="asteroidIndex">The index of the asteroid to be removed</param>
/// <param name="numAsteroids">A reference to the current number of existing asteroids.</param>
void GameController::BreakAsteroid(int asteroidIndex, int* numAsteroids)
{
    // Checks if the asteroid has any health remaining
    if (asteroids[asteroidIndex]->GetHealth() > 1) {
        // Adds a new asteroid to the end of the vector.
        asteroids.push_back(new Asteroid(asteroids[asteroidIndex]));

        // Creates a new asteroid pointer
        Asteroid* tempAsteroid = new Asteroid(asteroids[asteroidIndex]);

        // Deletes the existing asteroid and replaces it with the one currently at the end of the array.
        delete asteroids[asteroidIndex];
        asteroids[asteroidIndex] = asteroids[(*numAsteroids) - 1];

        // Sets the asteroid at the end of the array to the new asteroid pointer.
        asteroids[(*numAsteroids) - 1] = tempAsteroid;

        // Shows that the total number of asteroids in the scene has increased by 1
        (*numAsteroids)++;
    }

    else {
        // Deletes the existing asteroid.
        delete asteroids[asteroidIndex];

        // Replaces the pointer at this index with the one at the end of the array.
        asteroids[asteroidIndex] = asteroids[*numAsteroids - 1];

        // Removes the asteroid array's final value (after it is moved to fill the empty place).
        asteroids.pop_back();

        // Shows that the total number of asteroids in the scene has decreased by 1
        (*numAsteroids)--;
    }
}

/// <summary>
/// Calls the "Check Collision" function between each asteroid/bullet and each asteroid/ship.
/// </summary>
void GameController::CheckCollisions()
{
    // Retrieves the list of bullets from the ship object.
    std::deque<Bullet*>* bullets = ship->GetBullets();

    for (Asteroid* asteroid : asteroids) {
        for (Bullet* bullet : *bullets) {
            // Checks collisions between each asteroid and bullet.
            bullet->CheckCollision(asteroid);
        }

        // Checks collisions between each asteroid and the ship.
        ship->CheckCollision(asteroid);
    }
}