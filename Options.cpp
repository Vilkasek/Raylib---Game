#include "Options.hpp"

Options::Options() {}
Options::~Options() {}

void Options::update() 
{
    if(IsKeyPressed(KEY_F) && !changedTint)
        changedTint = true;
    else if(IsKeyPressed(KEY_F) && changedTint)
        changedTint = false;
}
void Options::render()
{
    DrawText("Press F to enable dark theme", ((float)800 / 2) - MeasureText("Press F to enable dark theme", 30) / 2, 800 / 2, 30, BLACK);
    DrawText("Press BACKSPACE to back to menu", ((float)800 / 2) - MeasureText("Press BACKSPACE to back to menu", 20) / 2, (800 / 2) + 70, 20, BLACK);
}
