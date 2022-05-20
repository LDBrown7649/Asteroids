#include "Button.h"

Button::Button(Vector2 pos, int width, int height, Color color, std::string message)
{
    // Sets each button component based on the values passed in.
    cornerPoint = pos;
    this->width = width;
    this->height = height;
    buttonColor = color;
    this->message = message;
}

bool Button::CheckButtonOverlap(Vector2* point)
{
    // Checks if a specified point overlaps with the button
    return point->x > cornerPoint.x && point->x < cornerPoint.x + width
        && point->y > cornerPoint.y && point->y < cornerPoint.y + height;
}

void Button::DrawButton() {
    Vector2 mousePos = GetMousePosition();

    // Draws the rectangle of the button in white if the button is being hovered over, or in its regular colours otherwise.
    DrawRectangle((int)cornerPoint.x, (int)cornerPoint.y, width, height, CheckButtonOverlap(&mousePos) ? RAYWHITE : buttonColor);

    // Displays the message, centred within the button.
    if (message != "") {
        DrawText(message.c_str(), cornerPoint.x + width / 2 - (message.length()) * 20.f / 3.5f, 
            cornerPoint.y + height / 2 - 20 / 3.5f, 20, RED);
    }
}
