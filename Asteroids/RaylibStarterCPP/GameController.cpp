#include "GameController.h"



void GameController::PlayGame()
{
    Setup();

    while (!WindowShouldClose()) {
        Update();
        Draw();
    }

    Shutdown();
}

GameController::GameController()
{
}

GameController::~GameController()
{
    delete ship;
}

void GameController::Setup()
{
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
    CheckCollisions();
    CheckAsteroids();
    for (int i = 0; i < asteroids.size(); i++) {
        asteroids[i]->Update();
    }
    ship->Update();
}

void GameController::Draw()
{
    BeginDrawing();

    ClearBackground(BLACK);

    for (Asteroid* asteroid : asteroids) {
        asteroid->Draw();
    }
    ship->Draw();

    EndDrawing();
}

void GameController::Shutdown()
{
    CloseWindow();
    for(Asteroid * asteroid : asteroids) {
        delete asteroid;
        asteroid = nullptr;
    }
}

void GameController::CheckAsteroids()
{
    int size = asteroids.size();
    if (size == 0) {
        if (timeSinceAsteroids >= maxTimeSinceAsteroids) {
            for (int i = 0; i < numAsteroids; i++) {
                asteroids.push_back(new Asteroid(3));
            }
            numAsteroids++;
            timeSinceAsteroids = 0;
        }
        else {
            timeSinceAsteroids++;
        }
    }
    else {
        int size = asteroids.size();
        for (int i = 0; i < size; i++) {
            if (asteroids[i]->collided) {
                SplitAsteroid(i, &size);
            }
        }
    }
}

void GameController::SplitAsteroid(int asteroidIndex, int* numAsteroids)
{
    if (asteroids[asteroidIndex]->GetHealth() > 1) {
        asteroids.push_back(new Asteroid(asteroids[asteroidIndex]));
        Asteroid* tempAsteroid = new Asteroid(asteroids[asteroidIndex]);
        delete asteroids[asteroidIndex];
        asteroids[asteroidIndex] = asteroids[(*numAsteroids) - 1];
        asteroids[(*numAsteroids) - 1] = tempAsteroid;
        (*numAsteroids)++;
    }
    else {
        delete asteroids[asteroidIndex];
        asteroids[asteroidIndex] = asteroids[*numAsteroids - 1];
        asteroids.pop_back();
        (*numAsteroids)--;
    }
}

void GameController::CheckCollisions()
{
    // Retrieves the list of bullets from the ship object.
    std::deque<Bullet*>* bullets = ship->GetBullets();

    for (Asteroid* asteroid : asteroids) {
        for (Bullet* bullet : *bullets) {
            bullet->CheckCollision(asteroid);
        }

        ship->CheckCollision(asteroid);
    }
}
