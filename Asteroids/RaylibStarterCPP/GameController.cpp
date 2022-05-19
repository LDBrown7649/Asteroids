#include "GameController.h"
#include <iostream>
#include "Button.h"


/// <summary>
/// Loads, updates, and draws the main menu
/// </summary>
void GameController::LoadMenu()
{
    // Adds new background asteroids until 5 are in the scene.
    while (asteroids.size() < 5) {
        asteroids.push_back(new Asteroid());
    }

    // Creates a button for the player to press to begin the game.
    Button playButton = Button(Vector2{ 150, 250 }, 250, 80, DARKBROWN, "PLAY ASTEROIDS!");

    // Creates a button for the player to press to quit.
    Button quitButton = Button(Vector2{ 150, 350 }, 250, 80, DARKBROWN, "QUIT GAME");

    Vector2 mousePos = GetMousePosition();

    // Checks if the play button was pressed.
    if (IsMouseButtonPressed(0) && playButton.CheckButtonOverlap(mousePos)) {
        // Changes the game state from "Menu" to "Game"
        ResetGame();
        gamestate = GameMode::Game;
    }

    // Checks if the quit button was pressed
    if (IsMouseButtonPressed(0) && quitButton.CheckButtonOverlap(mousePos)) {
        // Changes the game state from "Menu" to "Quit"
        gamestate = GameMode::Quit;
    }

    // Draws the background asteroids, as well as the buttons.
    BeginDrawing();
    ClearBackground(BLACK);
    for (Asteroid* asteroid : asteroids) {
        asteroid->Update();
        asteroid->Draw();
    }
    DrawText("Asteroids!", 50, 80, 100, RAYWHITE);
    playButton.DrawButton();
    quitButton.DrawButton();
    EndDrawing();
}

/// <summary>
/// Displays the scoreboard at the end of the game. This displays previous highscores.
/// </summary>
void GameController::Scoreboard() {
    // Creates a button for the player to press to restart the game.
    Button playButton = Button(Vector2{ 50, 500 }, 175, 75, DARKBROWN, "PLAY AGAIN");
    // Creates a button for the player to press to quit.
    Button quitButton = Button(Vector2{ 350, 500 }, 175, 75, DARKBROWN, "QUIT GAME");

    // Adds new background asteroids (if required)
    while (asteroids.size() < 5) {
        asteroids.push_back(new Asteroid());
    }

    // Checks if the scores need to be read from the file.
    if (scores[0] == 0) {
        GetScores();
        UpdateScores();
    }

    Vector2 mousePos = GetMousePosition();

    // Checks if the quit button was pressed.
    if (quitButton.CheckButtonOverlap(mousePos) && IsMouseButtonDown(0)) {
        // Moves the game state from "Score" to "Quit"
        gamestate = GameMode::Quit;
    }
    // Checks if the play button was pressed.
    if (playButton.CheckButtonOverlap(mousePos) && IsMouseButtonDown(0)) {
        ResetGame();
        // Moves the game state from "Score" to "Game"
        gamestate = GameMode::Game;
    }

    // Draws the highscore values and buttons, along with the background asteroids.
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("HIGH SCORES!", 120, 100, 50, WHITE);
    
    for (Asteroid* asteroid : asteroids) {
        asteroid->Update();
        asteroid->Draw();
    }
    playButton.DrawButton();
    quitButton.DrawButton();
    for (int i = 0; i < 5; i++) {
        DrawText(std::to_string(scores[i]).c_str(), 200, 200 + 50 * i, 25, WHITE);
        DrawText(names[i].c_str(), 300, 200 + 50 * i, 25, WHITE);
    }
    
    EndDrawing();
}

void GameController::GetScores() {
    // Retrieves the scores and names from the highscores file.
    std::fstream file("highscores.dat", std::ios::in);
    for (int i = 0; i < 5; i++) {
        file >> names[i];
        file >> scores[i];
    }
    file.close();
}

void GameController::PlayGame()
{
    // Setup the required game features.
    Setup();

    // Continuously runs the game loop, calling functions based on the game's current state.
    while (!(endgame || WindowShouldClose())) {
        switch (gamestate) {
            case GameMode::Menu:
                // Loads the main menu objects.
                LoadMenu();
                break;
            case GameMode::Game:
                // The main gameplay section where the player avoids asteroids.
                GameUpdate();
                GameDraw();
                break;
            case GameMode::Score:
                // The scoreboard showing past highscores.
                Scoreboard();
                break;
            case GameMode::Quit:
                // Ends the while loop, exiting the game.
                endgame = true;
        }
        
    }

    // End the play loop and free any used memory.
    Shutdown();
}

/// <summary>
/// Remove all asteroids from the scene and delete them from memory.
/// </summary>
void GameController::ClearAsteroids()
{
    for (Asteroid* asteroid : asteroids) {
        delete asteroid;
        asteroid = nullptr;
    }
    asteroids.clear();
}

/// <summary>
/// Resets important game features so that the game can be played again.
/// </summary>
void GameController::ResetGame()
{
    // Resets the player's name
    playerName = "Lachlan";

    // Resets the score items
    scores[0] = 0;
    currentScore = 0;

    // Resets the asteroids
    ClearAsteroids();
    numAsteroids = 1;

    // Resets the player ship object.
    delete ship;
    ship = new PlayerShip();
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

    // Opens the highscores file, reads the first record (current highest score), and closes the file. 
    std::ifstream file("highscores.dat", std::ios::in);
    file >> highscoreName;
    file >> highscore;
    file.close();
}

void GameController::GameUpdate()
{
    // Checks which objects have collided with each other.
    CheckCollisions();
    // Checks which asteroids need to split or be removed.
    CheckAsteroids();

    // Updates the ship (and the attached bullet objects)
    ship->Update();

    if (ship->GetLives() <= 0){
        gamestate = GameMode::Score;
    }
}

void GameController::GameDraw()
{
    BeginDrawing();

    // Draws the player's current score to the screen and sets the background to be Black.
    ClearBackground(BLACK);
    DrawText(std::to_string(currentScore).c_str(), 20, 5, 18, WHITE);

    // Displays the highest score recorded so far (and who did it).
    DrawText("HIGHSCORE:", 370, 5, 18, WHITE);
    DrawText(highscoreName.c_str(), 370, 25, 18, WHITE);
    DrawText(std::to_string(highscore).c_str(), 500, 5, 18, WHITE);

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
    ClearAsteroids();

    if (scores[0] == 0) {
        GetScores();
    }

    UpdateScores();
}

void GameController::UpdateScores() {
    // Updates the highscores, adding in the current score at the required location
    // and updating the list as required.
    std::fstream file("highscores.dat", std::ios::out);
    for (int i = 0; i < 5; i++) {
        if (currentScore > scores[i]) {
            std::string tempName = names[i];
            int tempScore = scores[i];
            names[i] = playerName;
            scores[i] = currentScore;
            playerName = tempName;
            currentScore = tempScore;
        }
        // Prints the high score to the file.
        file << names[i] << " " << std::to_string(scores[i]) << std::endl;
    }
    file.close();
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
                // Increases the player's current point score by the asteroid's point value.
                currentScore += asteroids[i]->GetPoints();
                BreakAsteroid(i, &size);
            }
        }
    }

    // Updates each asteroid in the scene
    for (Asteroid* asteroid : asteroids) {
        asteroid->Update();
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