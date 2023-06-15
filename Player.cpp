#include "Player.hpp"

// Konstruktor i destruktor
Player::Player()
{
    // Inicjalizujemy gracza
    init();
}
Player::~Player()
{
    // Deinicjalizujemy gracza
    deinit();
}

// Aktualizujemy gracza
void Player::update()
{
    stating();
    actioning();
    rectangleUpdate();
}

// Wyświetlamy odpowiednią klatkę animacji
void Player::render()
{
    DrawTextureRec(arrowLeft, leftRec, Vector2{ 50, 600 }, WHITE);
    DrawTextureRec(arrowUp, upRec, Vector2{ 336, 600 }, WHITE);
    DrawTextureRec(arrowRight, rightRec, Vector2{ 622, 600 }, WHITE);
}

// Ładujemy tekstury
void Player::initTextures()
{
    arrowUp = LoadTexture("Textures/Arrows/ArrowUp.png");
    arrowLeft = LoadTexture("Textures/Arrows/ArrowLeft.png");
    arrowRight = LoadTexture("Textures/Arrows/ArrowRight.png");
}

// Inicjalizujemy stany
void Player::initStates()
{
    upState = 0;
    rightState = 0;
    leftState = 0;
}

// Tworzymy obiekt rec, który będzie odpowiadał 
// za wyświetlanie odpowiednich klatek animacji
void Player::initRec()
{
    upRec = { 0, 0, (float)arrowUp.width, upHeight };
    leftRec = { 0, 0, (float)arrowLeft.width, leftHeight };
    rightRec = { 0, 0, (float)arrowRight.width, rightHeight };
}

// Inicjalizujemy klatki
void Player::initFrames()
{
    upHeight = (float)arrowUp.height / NUM_FRAMES;
    leftHeight = (float)arrowLeft.height / NUM_FRAMES;
    rightHeight = (float)arrowRight.height / NUM_FRAMES;
}

// Wywołujemy inicjalizatory
void Player::init()
{
    initTextures();
    initFrames();
    initStates();
    initRec();
}

// Odładowujemy tekstury z pamięci karty graficznej
void Player::deinit()
{
    UnloadTexture(arrowUp);
    UnloadTexture(arrowLeft);
    UnloadTexture(arrowRight);
}

// Zmieniamy stany gracza
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

// Ustawiamy nasze akcje, aby miały wartości true,
// albo false
void Player::actioning()
{
    up = (upState == 1);
    left = (leftState == 1);
    right = (rightState == 1);
}

// Aktualizujemy rec, aby sie przesuwał po teksturze
// żeby wyświetlić odpowiednią klatkę
void Player::rectangleUpdate()
{
    upRec.y = upState * upHeight;
    leftRec.y = leftState * leftHeight;
    rightRec.y = rightState * rightHeight;
}
