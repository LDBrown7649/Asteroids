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

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"

int main(int argc, char* argv[])
{
    int screenWidth = 600;
    int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "ASTEROIDS!");

    SetTargetFPS(60);
    PlayerShip ship = PlayerShip();
    Texture img2 = LoadTexture("Images/asteroid2.png");
    Texture img3 = LoadTexture("Images/asteroid3.png");
    
    while (!WindowShouldClose())
    {
        ship.OnUpdate();
        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("ASTEROIDS!", 190, 200, 20, LIGHTGRAY);
        Vector2 pos2 = Vector2();
        Vector2 pos3 = Vector2();
        pos2.x = 600.f;
        pos2.y = 50.f; 
        pos3.x = 0;
        pos3.y = 0;
        DrawTextureEx(img2, pos2, 0, 20, WHITE);
        DrawTextureEx(img3, pos3, 0, 20, WHITE);

        ship.OnDraw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}