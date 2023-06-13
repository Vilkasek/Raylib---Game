#include "Logo.hpp"

Logo::Logo() {}
Logo::~Logo() {}

void Logo::render()
{
    DrawText("Made with:", 100, 100, 30, BLACK);
    DrawRectangle(GetScreenWidth() / 2 - 128, GetScreenHeight() / 2 - 128, 256, 256, BLACK);
    DrawRectangle(GetScreenWidth() / 2 - 112, GetScreenHeight() / 2 - 112, 224, 224, RAYWHITE);
    DrawText("raylib", GetScreenWidth() / 2 - 44, GetScreenWidth() / 2 + 48, 50, BLACK);
    DrawText("Press ENTER to continue", 100, 700, 30, BLACK);
}