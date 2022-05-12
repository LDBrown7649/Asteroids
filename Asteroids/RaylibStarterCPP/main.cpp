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

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"

int main(int argc, char* argv[])
{
    // The dimensions of the screen.
    int screenWidth = 800;
    int screenHeight = 800;

    srand(time(nullptr));

    InitWindow(screenWidth, screenHeight, "ASTEROIDS!");
    
    // Limits the game to running at 60 fps.
    SetTargetFPS(60);

    // Creates the ship that the player controls.
    PlayerShip ship = PlayerShip();

    // Creates instances of asteroids.
    Asteroid a1 = Asteroid(3, rand());
    Asteroid a2 = Asteroid(2, rand());
    Asteroid a3 = Asteroid(1, rand());
    Asteroid a4 = Asteroid(2, rand());
    Asteroid a5 = Asteroid(3, rand());

    // Continuously updates and draws the ship until the game should close.
    while (!WindowShouldClose())
    {
        ship.OnUpdate();
        a1.Update();
        a2.Update();
        a3.Update();
        a4.Update();
        a5.Update();
        BeginDrawing();

        ClearBackground(BLACK);

        ship.OnDraw();
        a1.Draw();
        a2.Draw();
        a3.Draw();
        a4.Draw();
        a5.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}