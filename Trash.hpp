#pragma once

#include "raylib.h"

class Trash {
public:
    Trash();
    ~Trash();

    void update(float deltaTime, int& lives, Sound& miss);
    void render();

    void setPosition();
    void setCurrentTexture();

    void setSpeedLimit(float limit);

public:
    Rectangle trashColBox = { 0 };

    Texture2D currentTexture = { 0 };
    Texture2D textures[3] = { 0 };

    Vector2 position = { 0,0 };

    float speed = { 0 };
    float maxSpeed = { 0 };

private:
    void initTextures();
    void unloadTextures();

    void init();

    void clampSpeed();

private:
    int textureWidth = 0;
    int textureHeight = 0;
};
