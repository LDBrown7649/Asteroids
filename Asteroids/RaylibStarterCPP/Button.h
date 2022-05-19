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

	Color buttonColor;

public:
	// A button constructor for generating new buttons.
	Button(Vector2 pos, int width, int height, Color color, std::string message);

	// Check if a point and the button are overlapping currently.
	bool CheckButtonOverlap(Vector2 point);
	void DrawButton();
};

