#pragma once
#include "raylib.h"
#include <string>

class Button
{
private:
	// The position of the top-left corner of the button
	Vector2 cornerPoint;

	// The button object's width.
	int width = 0;

	// The button object's height.
	int height = 0;

	// A label to be written on the button.
	std::string label = "";

	// The colour of the background of the button object.
	Color buttonColor;

public:
	// A button constructor for generating new buttons.
	Button(Vector2 pos, int width, int height, Color color, std::string message);

	// Check if a point is within the bounds of the button object.
	bool CheckButtonOverlap(Vector2* point);
	
	// Make the button visible on the player's screen.
	void DrawButton(Vector2* mousePos);
};
