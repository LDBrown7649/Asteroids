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
    // Creates a new ScoreHandler, passing in a reference to the asteroid handler.
    scoreHandler = ScoreHandler(&asteroidHandler);
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
    scoreHandler.UpdateScores();

    // Deletes the ship and asteroids, and sets each pointer to the null pointer.
    delete ship;
    ship = nullptr;
    asteroidHandler.ClearAsteroids();
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
    asteroidHandler.MenuAsteroidUpdate();
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
            scoreHandler.ResetScores();
        }
        else if (scoreBoardButton.CheckButtonOverlap(&mousePos)) {
            // Changes the game state from "Menu" to "Score" if the scoreboard button was pressed.
            gamestate = GameMode::Score;
            scoreHandler.UpdateScores();
        }
    }
}

void GameController::GameUpdate()
{
    // Checks which objects have collided with each other.
    CheckCollisions();

    // Checks which asteroids need to split or be removed.
    asteroidHandler.UpdateAsteroids();

    // Updates the ship (and the attached bullet objects)
    ship->Update();

    // If the player ship has run out of lives, ask the player for their name and switch to the scoreboard.
    if (ship->GetLives() <= 0) {
        gamestate = GameMode::Score;
        scoreHandler.GetName();
        scoreHandler.UpdateScores();
    }
}

void GameController::CheckCollisions()
{
    // Retrieves the list of bullets from the ship object.
    std::deque<Bullet*>* bullets = ship->GetBullets();

    for (Asteroid* asteroid : *asteroidHandler.GetAsteroids()) {
        for (Bullet* bullet : *bullets) {
            // Checks collisions between each asteroid and bullet.
            bullet->CheckCollision(asteroid);
        }

        // Checks collisions between each asteroid and the ship if they are not currently immune.
        if (!ship->immune) {
            ship->CheckCollision(asteroid);
        }
        
        if (asteroid->collided) {
            // Increases the player's current point score by the asteroid's point value.
            scoreHandler.AddScore(asteroid->GetPoints());
        }
    }
}

void GameController::GameDraw()
{
    BeginDrawing();

    ClearBackground(BLACK);
    // Draws the player's current score and the highest score to the screen
    scoreHandler.DrawScores();

    // Draws each asteroid, the ship, and the bullets (as part of the ship drawing process).
    asteroidHandler.DrawAsteroids();
    ship->Draw();

    EndDrawing();
}

void GameController::ResetGame()
{
    // Resets the current score to 0.
    scoreHandler.SetScore(0);

    // Resets the asteroids
    asteroidHandler.ClearAsteroids();

    // Resets the player ship object.
    delete ship;
    ship = new PlayerShip();

    scoreHandler.GetHighScore();
}

void GameController::Scoreboard() {
    // Creates a button for the player to press to restart the game, and one to access the menu.
    Button playButton = Button(Vector2{ 170, 500 }, 250, 60, DARKBROWN, "PLAY AGAIN");
    Button menuButton = Button(Vector2{ 20, 20 }, 150, 50, DARKBROWN, "MENU");

    BeginDrawing();
    ClearBackground(BLACK);
    // Draws the asteroids in the background of the scene.
    asteroidHandler.MenuAsteroidUpdate();
    // Draws the buttons for the player to press
    playButton.DrawButton();
    menuButton.DrawButton();
    scoreHandler.DrawScoreboard();
    
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