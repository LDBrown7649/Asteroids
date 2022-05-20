#pragma once

#include <vector>
#include <fstream>
#include "Asteroid.h"
#include "PlayerShip.h"
#include "Button.h"

// An enum for classifying different states the game can be in.
enum class GameMode {
	Menu,
	Game,
	Score,
	Quit
};

class GameController
{
private: // Variables

	// The current game state. Changing this value will cause different scene objects to load.
	GameMode gamestate = GameMode::Menu;

	// The dimensions of the game window.
	int screenWidth = 600;
	int screenHeight = 600;

	// The ship the player controls in the game.
	PlayerShip* ship = nullptr;

	// A vector of pointers to asteroid objects.
	std::vector<Asteroid*> asteroids;

	// The number of asteroids that should be spawned into the scene.
	int numAsteroids = 1;

	// A limit on the amount of asteroids that can be present in any scene.
	int maxNumAsteroids = 6;

	// Tracks how many frames have elapsed since the game had asteroids present.
	int timeSinceAsteroids = 0;

	// The maximum number of elapsed frames before more asteroids should be added.
	int maxTimeSinceAsteroids = 60;

	// The player's current score.
	int currentScore = 0;

	// The highest score currently recorded in the data file.
	int highscore = 0;

	// The name associated with the highest recorded score.
	std::string highscoreName = "";

	// The scores stored in the highscores data file.
	int scores[5] = { 0,0,0,0,0 };

	// The names stored in the highscores data file.
	std::string names[5] = { "","","","","" };

	// The name of the current player.
	std::string playerName = "UNKNOWN_PLAYER";

	// A boolean indicating if the game should end or not.
	bool endgame = false;

	std::vector<Button*> buttons;

public: // Functions

	// Controls the game process, loading and updating objects based on the current state of the game.
	void PlayGame();

private: // Functions

	// Prepares the game to be played by opening the game window and seeding the random generator.
	void Setup();

	// Updates the scoreboard, closes the window, and deletes any remaining assets.
	void Shutdown();

	// Loads, updates, and draws objects and buttons on the main menu.
	void LoadMenu();

	// Checks for collisions or changes in the scene before moving each game object to its new location.
	void GameUpdate();

	// Checks for collisions between game objects (such as asteroids, bullets, and ships).
	void CheckCollisions();

	// Draws each game object to the screen
	void GameDraw();

	// Resets important game features so that the game can be played again.
	void ResetGame();

	// Gets the player's name at the end of the game.
	void GetName();

	// Displays the scoreboard at the end of the game. This displays previous highscores.
	void Scoreboard();

	// Opens the highscores file and reads the contents.
	void GetScores();

	// Updates the highscore file based on the player's most recent score.
	void UpdateScores();

	// Sets the highscore list to a default state (names are all "..........", scores are 1000, 900, 800, 700, 600).
	void ResetScores();

	// Checks that the scene has the correct amount of asteroids, adding more or breaking existing ones as required.
	void UpdateAsteroids();

	// Remove all asteroids from the scene and delete them.
	void ClearAsteroids();

	// A method for continuing to update and draw asteroids while in the background of the menu screens.
	void DrawMenuAsteroids();

	// Removes the asteroid at the specified index from the scene. If it had sufficient health, replace it with two
	// smaller "children" asteroids. Increases or decreases the number of existing asteroids to reflect the result.
	void BreakAsteroid(int asteroidIndex, int* numAsteroids);
};

