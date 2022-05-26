#pragma once

#include "PlayerShip.h"
#include "Button.h"
#include "AsteroidHandler.h"
#include "ScoreHandler.h"

class GameController
{
private: // Variables

	// An enum representing different states the game can be in.
	enum class GameMode {
		Menu,
		Game,
		Score,
		Quit
	};

	// The current game state. Changing this value will cause different scenes to load.
	GameMode gamestate = GameMode::Menu;

	// The width of the screen.
	int screenWidth = 600;

	// The height of the screen.
	int screenHeight = 600;

	// The ship the player controls in the game.
	PlayerShip* ship = nullptr;

	// A boolean indicating if the game should end or not.
	bool endgame = false;

	// The asteroid handler that manages the asteroids throughout the game.
	AsteroidHandler asteroidHandler;

	// The score handler that tracks and updates the player's score, as well as the recorded high scores.
	ScoreHandler scoreHandler;

public: // Functions

	// Controls the game process, loading and updating objects based on the current state of the game.
	void PlayGame();

private: // Functions

	// Prepares the game to be played by setting up background objects such as the score handler and the random generator.
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

	// Displays the scoreboard. This displays previous highscores.
	void Scoreboard();
};

