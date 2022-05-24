#pragma once

#include <vector>
#include <fstream>
#include "PlayerShip.h"
#include "Button.h"
#include "AsteroidHandler.h"

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

	AsteroidHandler asteroidHandler;

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
};

