#pragma once

#include "raylib.h"

constexpr int NUM_FRAMES = 2;

class Player
{
public:
    Player();
    ~Player();

    void update();
    void render();

public:
    int score = 0;
    int hiScore = 0;
    int lives = 3;

    int upState = 0;
    int leftState = 0;
    int rightState = 0;

private:
    void initTextures();
    void initStates();
    void initRec();
    void initFrames();

    void init();
    void deinit();

    void stating();
    void actioning();
    void rectangleUpdate();

private:
    bool up = false;
    bool left = false;
    bool right = false;

    float upHeight = 0;
    float leftHeight = 0;
    float rightHeight = 0;

    Texture2D arrowUp = { 0 };
    Texture2D arrowLeft = { 0 };
    Texture2D arrowRight = { 0 };

    Rectangle upRec = { 0 };
    Rectangle leftRec = { 0 };
    Rectangle rightRec = { 0 };
};