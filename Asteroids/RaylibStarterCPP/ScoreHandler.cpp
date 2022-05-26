#include "ScoreHandler.h"

ScoreHandler::ScoreHandler()
{
    // Sets the pointer to the asteroid handler to null.
    backgroundAsteroids = nullptr;
}

ScoreHandler::ScoreHandler(AsteroidHandler* asteroidHandler)
{
    // Stores a pointer to an existing asteroidHandler.
    backgroundAsteroids = asteroidHandler;
}

void ScoreHandler::GetHighScore()
{
    // Opens the highscores file, reads the current highest score data, and closes the file. 
    std::ifstream file("highscores.dat", std::ios::in);
    file >> highscoreName;
    file >> highscore;
    file.close();
}

void ScoreHandler::GetName()
{
    // Resets the player's name.
    playerName = "";
    while (!IsKeyPressed(KEY_ENTER)) {
        // Stores the key currently being pressed (stores 0 if no key was pressed)
        int letter = GetKeyPressed();
        int nameLength = playerName.size();

        if (IsKeyPressed(KEY_BACKSPACE) && nameLength >= 1) {
            // Removes the last character from the name if BACKSPACE was pressed (provided there is at least one letter to remove).
            playerName.pop_back();
        }
        // Adds the letter to the name (provided a key other than SPACE was entered, and the name is less than 10 characters).
        else if (letter != 0 && letter != KEY_SPACE && nameLength < 10) {
            playerName += (KeyboardKey)letter;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        // Draws the asteroids to the screen.
        if (backgroundAsteroids != nullptr) {
            backgroundAsteroids->MenuAsteroidUpdate();
        }
        // Displays the player's input.
        DrawText("ENTER NAME:", 200, 250, 30, RAYWHITE);
        DrawText((playerName + "_").c_str(), 200, 350, 30, RAYWHITE);
        DrawText("Press ENTER to confirm", 10, 550, 15, RAYWHITE);
        EndDrawing();
    }
    // If no name has been entered, set a default name.
    if (playerName == "") {
        playerName = "UNKNOWN_PLAYER";
    }
}

void ScoreHandler::GetScores()
{
    // Retrieves the scores and names from the highscores file.
    std::fstream file("highscores.dat", std::ios::in);
    for (int i = 0; i < 5; i++) {
        file >> names[i];
        file >> scores[i];
    }
    file.close();
}

void ScoreHandler::UpdateScores()
{
    // Retrieves the highscore values from the highscores file.
    GetScores();
    std::fstream file("highscores.dat", std::ios::out);
    // Compares the current score to each highscore value, going down the list.
    for (int i = 0; i < 5; i++) {
        // If the score is greater than or equal to the current highscore, replace the values with each other.
        if (currentScore >= scores[i]) {
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

void ScoreHandler::ResetScores()
{
    // Sets each highscore in the file to be a default value.
    std::ofstream file("highscores.dat", std::ios::in);
    for (int i = 0; i < 5; i++) {
        file << ".......... " + std::to_string(1000 - i * 100) << std::endl;
    }
    file.close();
    // Resets the player's current score value.
    currentScore = 0;
}

void ScoreHandler::DrawScoreboard()
{
    // Draws the current highscores to the screen.
    DrawText("HIGH SCORES!", 120, 100, 50, WHITE);
    for (int i = 0; i < 5; i++) {
        DrawText(std::to_string(scores[i]).c_str(), 200, 200 + 50 * i, 25, WHITE);
        DrawText(names[i].c_str(), 300, 200 + 50 * i, 25, WHITE);
    }
}

void ScoreHandler::DrawScores()
{
    // Draws the player's current score to the top-left of the screen
    DrawText(std::to_string(currentScore).c_str(), 20, 5, 18, WHITE);

    // Displays the highest score recorded so far (and who achieved it).
    DrawText("HIGHSCORE:", 370, 5, 18, WHITE);
    DrawText(highscoreName.c_str(), 370, 25, 18, WHITE);
    DrawText(std::to_string(highscore).c_str(), 500, 5, 18, WHITE);
}

void ScoreHandler::AddScore(int scoreToAdd)
{
    currentScore += scoreToAdd;
}

void ScoreHandler::SetScore(int scoreVal)
{
    currentScore = scoreVal;
}
