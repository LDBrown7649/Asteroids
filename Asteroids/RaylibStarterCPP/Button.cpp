#include "Button.h"

Button::Button(Vector2 pos, int width, int height, Color color, std::string message)
{
    cornerPoint = pos;
    this->width = width;
    this->height = height;
    buttonColor = color;
    this->message = message;
}

bool Button::CheckButtonOverlap(Vector2 point)
{
    return point.x > cornerPoint.x && point.x < cornerPoint.x + width
        && point.y > cornerPoint.y && point.y < cornerPoint.y + height;
}

void Button::DrawButton() {
    DrawRectangle((int)cornerPoint.x, (int)cornerPoint.y, width, height, CheckButtonOverlap(GetMousePosition()) ? RAYWHITE : buttonColor);
    if (message != "") {
        DrawText(message.c_str(), cornerPoint.x + width / 2 - (message.length()) * 20.f / 3.5f, 
            cornerPoint.y + height / 2 - 20.f / 3.5f, 20, RED);
    }
}
