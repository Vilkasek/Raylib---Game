#include "Trash.hpp"

// Inicjalizujemy śmieci
Trash::Trash()
{
    initTextures();
    setCurrentTexture();
    setPosition();
}

// Odładowujemy tekstury
Trash::~Trash()
{
    unloadTextures();
}

// Aktualizujemy śmieci, pobierając czas klatki
// oraz jako referencję życia (Dzięki temu tutaj
// możemy je odejmować)
void Trash::update(float deltaTime, int& lives)
{
    // Zmieniamy pozycję na osi X
    position.x += speed * deltaTime;

    // Jeżeli dojdziemy do końca ekranu, zmieniamy
    // teksturę, resetujemy pozycję oraz odejmujemy
    // życie
    if (position.x > GetScreenWidth())
    {
        setCurrentTexture();
        setPosition();
        lives--;
    }

    // Tworzymy hitboxy śmieci
    trashColBox = {position.x, position.y, 72, 128};
}

// Rysujemy aktualną teksturę ze zmienną pozycją
void Trash::render()
{
    DrawTexture(currentTexture, int(position.x), int(position.y), WHITE);
}

// Ładujemy do tablicy tekstur tekstury
void Trash::initTextures()
{
    textures[0] = LoadTexture("Textures/Trashes/Bottle.png");
    textures[1] = LoadTexture("Textures/Trashes/Phone.png");
    textures[2] = LoadTexture("Textures/Trashes/Battery.png");
}

// Za pomocą pętli for each odładowujemy tekstury
void Trash::unloadTextures()
{
    for (Texture2D texture : textures)
        UnloadTexture(texture);
}

// Ustawiamy odpowiednią pozycję na początku gry
void Trash::setPosition()
{
    position.x = textureWidth * -1.0f;
    position.y = GetScreenHeight() / 2.0f - textureHeight / 2.0f;
}

// Ustawiamy aktualną teksturę
void Trash::setCurrentTexture()
{
    // Losujemy jedną z trzech tesktur
    int randomIndex = GetRandomValue(0, 2);

    // Ustawiamy odpowiednią teksturę
    currentTexture = textures[randomIndex];

    // Zmieniamy jeżeli to potrzebne szerokość
    // i wysokość tekstury
    textureWidth = currentTexture.width;
    textureHeight = currentTexture.height;
}
