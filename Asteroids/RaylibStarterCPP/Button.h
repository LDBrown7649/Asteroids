#pragma once
#include "raylib.h"
#include <string>
class Button
{
private:
	// The position of the top-left corner of the button
	Vector2 cornerPoint;

	// The width and height of the button
	int width = 0;
	int height = 0;

	// An optional message to be written on the button.
	std::string message = "";

	// The colour that the button's border will be drawn in.
	Color buttonColor;

public:
	// A button constructor for generating new buttons.
	Button(Vector2 pos, int width, int height, Color color, std::string message);

	// Check if a point and the button are overlapping currently.
	bool CheckButtonOverlap(Vector2* point);

	// Makes the button visible on the player's screen.
	void DrawButton();
};
