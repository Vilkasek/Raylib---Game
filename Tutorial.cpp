#include "Tutorial.hpp"

Tutorial::Tutorial() {}
Tutorial::~Tutorial() 
{
	for (Texture2D texture : textures)
        UnloadTexture(texture);
}

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

void Tutorial::loadTutorial()
{
    textures[0] = LoadTexture("Textures/Trashes/Bottle.png");
    textures[1] = LoadTexture("Textures/Trashes/Phone.png");
    textures[2] = LoadTexture("Textures/Trashes/Battery.png");
}

void Tutorial::unLoadTutorial()
{
    for (Texture2D texture : textures)
        UnloadTexture(texture);
}
