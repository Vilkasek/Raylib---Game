#include "Trash.hpp"

Trash::Trash()
{
    initTextures();
    setCurrentTexture();
    setPosition();
}

Trash::~Trash()
{
    unloadTextures();
}

void Trash::update(float deltaTime, int& lives)
{
    position.x += speed * deltaTime;

    if (position.x > GetScreenWidth())
    {
        setCurrentTexture();
        setPosition();
        lives--;
    }

    trashColBox = {position.x, position.y, 72, 128};
}

void Trash::render()
{
    DrawTexture(currentTexture, int(position.x), int(position.y), WHITE);
}

void Trash::initTextures()
{
    textures[0] = LoadTexture("Textures/Trashes/Bottle.png");
    textures[1] = LoadTexture("Textures/Trashes/Phone.png");
    textures[2] = LoadTexture("Textures/Trashes/Battery.png");
}

void Trash::unloadTextures()
{
    for (Texture2D texture : textures)
        UnloadTexture(texture);
}

void Trash::setPosition()
{
    position.x = textureWidth * -1.0f;
    position.y = GetScreenHeight() / 2.0f - textureHeight / 2.0f;
}

void Trash::setCurrentTexture()
{
    int randomIndex = GetRandomValue(0, 2);
    currentTexture = textures[randomIndex];
    textureWidth = currentTexture.width;
    textureHeight = currentTexture.height;
}
