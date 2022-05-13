/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
#include "raylib.h"
#include <iostream>
#include "PlayerShip.h"
#include "Asteroid.h"
#include <time.h>
#include <random>
#include <vector>


void CheckCollisions(PlayerShip* ship, Asteroid* asteroid) {
   // Retrieves the list of bullets from the ship object.
   std::deque<Bullet*>* bullets = ship->GetBullets();

   float asteroidSize = asteroid->GetSize() / 2.f;

   // Retrieves the position of the asteroid.
   Vector2 asteroidPos = asteroid->GetPos();

   for (Bullet* bullet : *bullets) {
       // Retrieves the position of the bullet.
       Vector2 bulletPos = bullet->GetPos();

       // Calculates the distance between the asteroid's centre and the bullet. If this distance is less than a threshold, a collision has occurred.
       Vector2 bulletToAsteroid = { bulletPos.x - asteroidPos.x, bulletPos.y - asteroidPos.y };
       float distance = sqrt(bulletToAsteroid.x * bulletToAsteroid.x + bulletToAsteroid.y * bulletToAsteroid.y);
       if (distance < asteroidSize + bullet->GetSize() / 2.f) {
           asteroid ->collided = true;
       }
   }

   // Calculates if a collision has occurred between the ship and the asteroid by checking the distance between the object's centres.
   Vector2 shipPos = ship->GetPos();
   Vector2 shipToAsteroid = { shipPos.x - asteroidPos.x, shipPos.y - asteroidPos.y };
   float distance = sqrt(shipToAsteroid.x * shipToAsteroid.x + shipToAsteroid.y * shipToAsteroid.y);
   if (distance < asteroidSize + ship->GetSize() / 2.f) {
       asteroid->collided = true;
   }
}

int main(int argc, char* argv[])
{
    // Creates a vector of all asteroids.
    std::vector<Asteroid*> asteroids;

    // The dimensions of the screen.
    int screenWidth = 800;
    int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "ASTEROIDS!");

    // Seeds the random generator.
    srand((int)time(nullptr));
    
    // Limits the game to running at 60 fps.
    SetTargetFPS(60);

    // Creates the ship that the player controls.
    PlayerShip ship = PlayerShip();

    // Creates instances of asteroids.
    for (int i = 0; i < 1; i++) {
        asteroids.push_back(new Asteroid(3, rand()));
    }

    // Continuously updates and draws the ship until the game should close.
    while (!WindowShouldClose())
    {
        // Updates the ship and each asteroid in the scene.
        for (Asteroid* as : asteroids) {
            as->Update();
            CheckCollisions(&ship, as);
        }
        ship.Update();

        BeginDrawing();

        ClearBackground(BLACK);

        // Draws the ship and each asteroid to the screen.
        for (Asteroid* as : asteroids) {
            as->Draw();
        }
        ship.Draw();

        EndDrawing();
    }

    CloseWindow();


    // Removes each asteroid from memory.
    for (Asteroid* as : asteroids) {
        delete as;
        as = nullptr;
    }

    return 0;
}