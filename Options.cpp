#include "Options.hpp"

Options::Options() {}
Options::~Options() {}

// Aktualizujemy ekran opcji
void Options::update() 
{
    // Sprawdzamy, czy dany klawisz został wciśnięty
    // oraz czy opcja jest już przełączona
    if(IsKeyPressed(KEY_F) && !changedTint)
        changedTint = true;
    else if(IsKeyPressed(KEY_F) && changedTint)
        changedTint = false;

    if(IsKeyPressed(KEY_M) && !muted)
        muted = true;
    else if(IsKeyPressed(KEY_M) && muted)
        muted = false;
}

// Wyświetlamy opcje
void Options::render()
{
    DrawText("Press F to enable dark theme", ((float)800 / 2) - MeasureText("Press F to enable dark theme", 30) / 2, 800 / 2, 30, BLACK);
    DrawText("Press M to mute game", ((float)800 / 2) - MeasureText("Press M to mute game", 30) / 2, 800 / 2 + 40, 30, BLACK);
    DrawText("Press BACKSPACE to back to menu", ((float)800 / 2) - MeasureText("Press BACKSPACE to back to menu", 20) / 2, (800 / 2) + 90, 20, BLACK);
}
