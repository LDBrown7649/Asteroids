#pragma once

#include <fstream>
#include "AsteroidHandler.h"

class ScoreHandler
{
private:

	// The asteroids that are used by the game handler script.
	AsteroidHandler* backgroundAsteroids;

	// The player's current score.
	int currentScore = 0;

	// The highest score currently recorded in the highscores file.
	int highscore = 0;

	// The name associated with the highest score in the highscores file.
	std::string highscoreName = "";

	// The scores stored in the highscores data file.
	int scores[5] = { 0,0,0,0,0 };

	// The names stored in the highscores data file.
	std::string names[5] = { "","","","","" };

	// The name of the current player.
	std::string playerName = "UNKNOWN_PLAYER";

public:
	// A default constructor for the score handler.
	ScoreHandler();

	// A constructor for the score handler that has a reference to an asteroid handler.
	ScoreHandler(AsteroidHandler* asteroidHandler);

	// Gets the highscore values from the highscores data file.
	void GetHighScore();

	// Gets the player's name at the end of the game.
	void GetName();

	// Opens the highscores file and reads the contents.
	void GetScores();

	// Updates the highscore file based on the player's most recent score.
	void UpdateScores();

	// Sets the highscore list to a default state (names are all "..........", scores are 1000, 900, 800, 700, 600).
	void ResetScores();

	// Draws the scoreboard values to the screen.
	void DrawScoreboard();

	// Draws the current score and the current highscore value.
	void DrawScores();

	// Adds to the current score value by a specified amount.
	void AddScore(int scoreToAdd);

	// Sets the score to a given value.
	void SetScore(int scoreVal);
};

