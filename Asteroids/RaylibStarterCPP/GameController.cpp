#include "GameController.h"

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

void GameController::Setup()
{
    // Opens the window with the current screen width and height.
    InitWindow(screenWidth, screenHeight, "ASTEROIDS!");

    // Seeds the random generator.
    srand((int)time(nullptr));

    // Limits the game to running at 60 fps.
    SetTargetFPS(60);

    ResetGame();
}

void GameController::Shutdown()
{
    // Closes the game window.
    CloseWindow();

    // Updates the score values in the highscores file.
    GetScores();
    UpdateScores();

    // Deletes the ship and asteroids, and sets each pointer to the null pointer.
    delete ship;
    ship = nullptr;
    ClearAsteroids();
}

void GameController::LoadMenu()
{
    // Creates a range of buttons for the player to interact with.
    Button playButton = Button(Vector2{ 170, 250 }, 250, 80, DARKBROWN, "PLAY ASTEROIDS!");
    Button resetHighscoreButton = Button(Vector2{ 170, 340 }, 250, 40, DARKBROWN, "RESET SCORES");
    Button scoreBoardButton = Button(Vector2{ 170, 390 }, 250, 40, DARKBROWN, "SCOREBOARD");
    Button quitButton = Button(Vector2{ 170, 440 }, 250, 80, DARKBROWN, "QUIT GAME");

    // Draws the background asteroids, as well as the buttons.
    BeginDrawing();
    ClearBackground(BLACK);
    DrawMenuAsteroids();
    DrawText("Asteroids!", 50, 80, 100, RAYWHITE);
    playButton.DrawButton();
    quitButton.DrawButton();
    resetHighscoreButton.DrawButton();
    scoreBoardButton.DrawButton();
    EndDrawing();

    // Checks if the player clicked on the screen.
    if (IsMouseButtonPressed(0)) {
        Vector2 mousePos = GetMousePosition();
        if (playButton.CheckButtonOverlap(&mousePos)) {
            // Changes the game state from "Menu" to "Game" if the play button was pressed
            gamestate = GameMode::Game;
            ResetGame();
        }
        else if (quitButton.CheckButtonOverlap(&mousePos)) {
            // Changes the game state from "Menu" to "Quit" if the quit button was pressed
            gamestate = GameMode::Quit;
        }
        else if (resetHighscoreButton.CheckButtonOverlap(&mousePos)) {
            // Overwrites the saved highscores to a default state if the reset button was pressed.
            ResetScores();
        }
        else if (scoreBoardButton.CheckButtonOverlap(&mousePos)) {
            // Changes the game state from "Menu" to "Score" if the scoreboard button was pressed.
            gamestate = GameMode::Score;
            GetScores();
            UpdateScores();
        }
    }
}

void GameController::GameUpdate()
{
    // Checks which objects have collided with each other.
    CheckCollisions();

    // Checks which asteroids need to split or be removed.
    UpdateAsteroids();

    // Updates the ship (and the attached bullet objects)
    ship->Update();

    // If the player ship has run out of lives, ask the player for their name and switch to the scoreboard.
    if (ship->GetLives() <= 0) {
        gamestate = GameMode::Score;
        GetName();
        GetScores();
        UpdateScores();
    }
}

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

void GameController::GameDraw()
{
    BeginDrawing();

    ClearBackground(BLACK);
    // Draws the player's current score to the top-left of the screen
    DrawText(std::to_string(currentScore).c_str(), 20, 5, 18, WHITE);

    // Displays the highest score recorded so far (and who achieved it).
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

void GameController::ResetGame()
{
    // Resets the current score to 0.
    currentScore = 0;

    // Resets the asteroids
    ClearAsteroids();
    numAsteroids = 1;

    // Resets the player ship object.
    delete ship;
    ship = new PlayerShip();

    // Opens the highscores file, reads the current highest score, and closes the file. 
    std::ifstream file("highscores.dat", std::ios::in);
    file >> highscoreName;
    file >> highscore;
    file.close();
}

void GameController::GetName() {
    bool proceed = false;
    // Resets the player's name.
    playerName = "";
    while (!IsKeyPressed(KEY_ENTER)) {
        // Stores the key currently pressed (stores 0 if no key was pressed)
        int letter = GetKeyPressed();
        int nameLength = playerName.size();

        // Removes the last character from the name (provided there is at least one letter to remove).
        if (IsKeyPressed(KEY_BACKSPACE) && nameLength >= 1) {
            playerName.pop_back();
        }
        // Adds the letter to the name (provided a key other than SPACE was entered, and the name is less than 10 characters).
        else if (letter != 0 && letter != KEY_SPACE && nameLength < 10) {
            playerName += (KeyboardKey)letter;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        // Draws the asteroids to the screen.
        DrawMenuAsteroids();
        // Displays the player's input.
        DrawText("ENTER NAME:", 200, 250, 30, RAYWHITE);
        DrawText((playerName + "_").c_str(), 200, 350, 30, RAYWHITE);
        DrawText("Press ENTER to confirm", 10, 550, 15, RAYWHITE);
        EndDrawing();
    }
    // If no name has been entered so far, set a default name.
    if (playerName == "") {
        playerName = "UNKNOWN_PLAYER";
    }
}

void GameController::Scoreboard() {
    // Creates a button for the player to press to restart the game, and one to access the menu.
    Button playButton = Button(Vector2{ 170, 500 }, 250, 60, DARKBROWN, "PLAY AGAIN");
    Button menuButton = Button(Vector2{ 20, 20 }, 150, 50, DARKBROWN, "MENU");

    BeginDrawing();
    ClearBackground(BLACK);
    // Draws the asteroids in the background of the scene.
    DrawMenuAsteroids();
    // Draws the buttons for the player to press
    playButton.DrawButton();
    menuButton.DrawButton();
    // Draws the current highscores.
    DrawText("HIGH SCORES!", 120, 100, 50, WHITE);
    for (int i = 0; i < 5; i++) {
        DrawText(std::to_string(scores[i]).c_str(), 200, 200 + 50 * i, 25, WHITE);
        DrawText(names[i].c_str(), 300, 200 + 50 * i, 25, WHITE);
    }
    EndDrawing();
    // Checks if the player clicked on the screen.
    if (IsMouseButtonPressed(0)) {
        Vector2 mousePos = GetMousePosition();
        if (playButton.CheckButtonOverlap(&mousePos)) {
            ResetGame();
            // Moves the game state from "Score" to "Game" if the play button was pressed.
            gamestate = GameMode::Game;
        }
        if (menuButton.CheckButtonOverlap(&mousePos)) {
            // Moves the game state from "Score" to "Game" if the menu button was pressed.
            gamestate = GameMode::Menu;
        }
    }
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

void GameController::UpdateScores() {
    std::fstream file("highscores.dat", std::ios::out);
    // Compares the current score to each highscore value, going down the list.
    for (int i = 0; i < 5; i++) {
        // If the score is greater than the current highscore, replace the values with each other.
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

void GameController::ResetScores()
{
    // Sets each highscore in the file to be a default value.
    std::ofstream file("highscores.dat", std::ios::in);
    for (int i = 0; i < 5; i++) {
        file << ".......... " + std::to_string(1000 - i * 100) << std::endl;
    }
    file.close();
}

void GameController::UpdateAsteroids()
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
                // Increases the player's current point score by the asteroid's point value.
                currentScore += asteroids[i]->GetPoints();
                BreakAsteroid(i, &size);
            }
            // Update the asteroid if it did not break.
            else {
                asteroids[i]->Update();
            }
        }
    }
}

void GameController::ClearAsteroids()
{
    // Deletes each asteroid before clearing the asteroid vector.
    for (Asteroid* asteroid : asteroids) {
        delete asteroid;
        asteroid = nullptr;
    }
    asteroids.clear();
}

void GameController::DrawMenuAsteroids()
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

/// <summary>

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