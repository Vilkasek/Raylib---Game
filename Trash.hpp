#pragma once

#include "raylib.h"

class Trash {
public:
    Trash();
    ~Trash();

    void update(float deltaTime, int& lives);
    void render();

    void setPosition();
    void setCurrentTexture();

public:
    Rectangle trashColBox = { 0 };

    Texture2D currentTexture = { 0 };
    Texture2D textures[3] = { 0 };

    Vector2 position = { 0,0 };

    float speed = 0.f;

private:
    void initTextures();
    void unloadTextures();

    void changeSpeed();

private:
    int textureWidth = 0;
    int textureHeight = 0;
};
