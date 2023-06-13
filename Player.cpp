#include "Player.hpp"

Player::Player()
{
    init();
}

Player::~Player()
{
    deinit();
}

void Player::update()
{
    stating();
    actioning();
    rectangleUpdate();
}

void Player::render()
{
    DrawTextureRec(arrowLeft, leftRec, Vector2{ 50, 600 }, WHITE);
    DrawTextureRec(arrowUp, upRec, Vector2{ 336, 600 }, WHITE);
    DrawTextureRec(arrowRight, rightRec, Vector2{ 622, 600 }, WHITE);
}

void Player::initTextures()
{
    arrowUp = LoadTexture("Textures/Arrows/ArrowUp.png");
    arrowLeft = LoadTexture("Textures/Arrows/ArrowLeft.png");
    arrowRight = LoadTexture("Textures/Arrows/ArrowRight.png");
}

void Player::initStates()
{
    upState = 0;
    rightState = 0;
    leftState = 0;
}

void Player::initRec()
{
    upRec = { 0, 0, (float)arrowUp.width, upHeight };
    leftRec = { 0, 0, (float)arrowLeft.width, leftHeight };
    rightRec = { 0, 0, (float)arrowRight.width, rightHeight };
}

void Player::initFrames()
{
    upHeight = (float)arrowUp.height / NUM_FRAMES;
    leftHeight = (float)arrowLeft.height / NUM_FRAMES;
    rightHeight = (float)arrowRight.height / NUM_FRAMES;
}

void Player::init()
{
    initTextures();
    initFrames();
    initStates();
    initRec();
}

void Player::deinit()
{
    UnloadTexture(arrowUp);
    UnloadTexture(arrowLeft);
    UnloadTexture(arrowRight);
}

void Player::stating()
{
    if (IsKeyDown(KEY_UP))
        upState = 1;
    else
        upState = 0;

    if (IsKeyDown(KEY_LEFT))
        leftState = 1;
    else
        leftState = 0;

    if (IsKeyDown(KEY_RIGHT))
        rightState = 1;
    else
        rightState = 0;
}

void Player::actioning()
{
    up = (upState == 1);
    left = (leftState == 1);
    right = (rightState == 1);
}

void Player::rectangleUpdate()
{
    upRec.y = upState * upHeight;
    leftRec.y = leftState * leftHeight;
    rightRec.y = rightState * rightHeight;
}
