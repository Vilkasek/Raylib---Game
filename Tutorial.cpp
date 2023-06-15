#include "Tutorial.hpp"

// Konstruktor i destruktor
Tutorial::Tutorial() {}
Tutorial::~Tutorial() 
{
	// Pętla for each po to, aby odładować tekstury
	for (Texture2D texture : textures)
        UnloadTexture(texture);
}

// Wyświetalmy śmiecia i obok co ma zrobić gracz
// aby go zbić
void Tutorial::render() 
{
	DrawTexture(textures[0], 20, 40, WHITE);
	DrawTexture(textures[1], 20, 178, WHITE);
	DrawTexture(textures[2], 20, 316, WHITE);

	DrawText("You must press UP arrow on your keyboard", 150, 104, 25, BLACK);
	DrawText("You must press LEFT arrow on your keyboard", 150, 242, 25, BLACK);
	DrawText("You must press RIGHT arrow on your keyboard", 150, 380, 25, BLACK);

	DrawText("Press ENTER to start", 400, 600, 30, BLACK);
}

/*
-----------------------------------------------------
Po co zrobiłem coś takiego?

Powód jest wręcz banalnie prosty, jeżeli bym
nie odładowywał tych tekstur, to nadal siedziałyby
one w pamięci podręcznej procesora graficznego, poza
tym nie są one nam stale potrzebne, więc nie ładujemy
ich od razu.

Co jest więc powodem? OPTYMALIZACJA!
-----------------------------------------------------
*/

// Ładowanie tutoriala
void Tutorial::loadTutorial()
{
    textures[0] = LoadTexture("Textures/Trashes/Bottle.png");
    textures[1] = LoadTexture("Textures/Trashes/Phone.png");
    textures[2] = LoadTexture("Textures/Trashes/Battery.png");
}

// Odładowywanie tutoriala
void Tutorial::unLoadTutorial()
{
    for (Texture2D texture : textures)
        UnloadTexture(texture);
}
