#pragma once

#include <fstream>
#include "Button.h"
#include "AsteroidHandler.h"

class ScoreHandler
{
private:

	AsteroidHandler* backgroundAsteroids;

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

public:
	ScoreHandler();
	ScoreHandler(AsteroidHandler* asteroidHandler);

	int GetCurrentScore() { return currentScore; }

	void AddScore(int scoreToAdd) { currentScore += scoreToAdd; }

	void SetScore(int scoreVal) { currentScore = scoreVal; }

	void GetHighScore();

	// Gets the player's name at the end of the game.
	void GetName();

	// Opens the highscores file and reads the contents.
	void GetScores();

	// Updates the highscore file based on the player's most recent score.
	void UpdateScores();

	// Sets the highscore list to a default state (names are all "..........", scores are 1000, 900, 800, 700, 600).
	void ResetScores();

	void DrawScoreboard();

	void DrawScores();
};

