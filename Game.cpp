#include "Game.hpp"
#include "raylib.h"

// Konstruktor
Game::Game()
{
    init();
}

// Destruktor
Game::~Game()
{
    // Usuwamy z pamięci karty graficznej tekstury
    UnloadTexture(background);
    UnloadTexture(hopper);
    UnloadTexture(tCoin);
    UnloadTexture(tHeart);

    // Usuwamy obraz z pamięci RAM
    UnloadImage(iCoin);

    // Usuwamy z ramu muzykę
    UnloadMusicStream(music);

    // Usuwamy z ramu dźwięki
    UnloadSound(fxHit);
    UnloadSound(fxBonus);
    UnloadSound(fxMissed);
    UnloadSound(fxBigPoints);

    // Usuwamy nasze wskaźniki (zwalniamy pamięć)
    delete player;
    delete trash;
    delete logo;
    delete tutorial;
    delete options;

    // Kończymy działanie karty dźwiękowej i
    // zamykamy okno
    CloseAudioDevice();
    CloseWindow();
}

// Główna pętla naszej gry
void Game::run()
{
    // Gra ma się wykonywać jeżeli nie dostanie
    // zdarzenia, które każe się jej zamknąć
    while (!WindowShouldClose())
    {
        // Liczymy klatki
        fCount++;

        // Pierw aktualizujemy wszystkie obiekty
        // a dopiero potem je rysujemy
        update();
        render();
    }
}

// Inicjalizujemy okno
void Game::initWindow()
{
    // Ustawiamy wielkość okna i jego tytuł, a
    // następnie ustalamy do jakiego klatkarzu
    // dążymy
    InitWindow(sWidth, sHeight, "Trash Sorter");
    SetTargetFPS(60);
}

// Ładujemy teksturę tła
void Game::initBackground()
{
    background = LoadTexture("Textures/Background.png");
}

// Inicjalizujemy punk w którym będziemy zrzucać 
// śmieci
void Game::initHopper()
{
    // Ładujemy teksturę
    hopper = LoadTexture("Textures/Hopper.png");

    // Tworzymy hitbox
    hopperColBox = { (float)sWidth / 2 - 40, (float)sHeight / 2 - 64, 90, 128 };
}

// Ładujemy czcionkę
void Game::initMenu()
{
    menuFont = LoadFontEx("Fonts/ARCADECLASSIC.TTF", 32, 0, 250);
}

// Inicjalizujemy UI poprzez załadowanie grafik
void Game::initUI()
{
    // Przez to, że nie możemy bezpośrednio pobrać animowanej tekstury
    // musimy pierw załadować obrazek i z niego
    // załadować do tekstury
    iCoin = LoadImageAnim("Textures/UI/Coin.gif", &animFrames);
    tCoin = LoadTextureFromImage(iCoin);

    tHeart = LoadTexture("Textures/UI/Heart.png");
}

// Inicjalizacja
void Game::init()
{
    // Wywołujemy inicjalitazory
    initWindow();
    initBackground();
    initHopper();
    initMenu();
    initUI();

    // Tworzymy obiekty
    player = new Player();
    trash = new Trash();
    logo = new Logo();
    tutorial = new Tutorial();
    options = new Options();

    // Ustalamy domyślny stan gry
    gameState = GameState::LOGO;

    // Uruchamiamy kartę dźwiękową
    InitAudioDevice();

    // Ładujemy strumień muzyki
    music = LoadMusicStream("Sounds/MenuSong.wav");

    // Ładujemy efekty dźwiękowe
    fxHit = LoadSound("Sounds/Effects/Hit.wav");
    fxBonus = LoadSound("Sounds/Effects/Bonus.wav");
    fxMissed = LoadSound("Sounds/Effects/Missed.wav");
    fxBigPoints = LoadSound("Sounds/Effects/BigPoints.wav");
}

// Sprawdzamy, która tektura jest wyświetlana
void Game::checkTexture(int i)
{
    if (trash -> currentTexture.id == trash -> textures[i].id)
    {
        // Gramy dźwięk hit.wav
        PlaySound(fxHit);

        // Resetujemy śmiecia i dodajemy graczowi
        // 10 punktów
        trash -> setPosition();
        trash -> setCurrentTexture();
        player -> score += 10;
    }
    else if (trash -> currentTexture.id != trash -> textures[i].id)
        PlaySound(fxMissed);
}

// Sprawdzamy, czy stan gracza się zgadza z teksturą
void Game::scoring()
{
    if (player -> upState == 1)
        checkTexture(0);
    else if (player -> rightState == 1)
        checkTexture(2);
    else if (player -> leftState == 1)
        checkTexture(1);
}

// Aktualizujemy menu gry
void Game::updateMenu()
{
    // Gramy muzykę
    PlayMusicStream(music);
    
    // Odczytujemy plik
    std::ifstream file ("Fonts/Old Score/oldScore.txt");

    // Otwieramy plik i odczytujemy wartość, po czym
    // ładujemy wartość do zmiennej
    if(file.is_open())
    {
        file >> player -> hiScore;
        file.close();
    }

    // Po kliknięciu przycisku enter przechodzimy
    // do tutoriala
    if (IsKeyPressed(KEY_ENTER))
    {
        tutorial -> loadTutorial();
        gameState = GameState::TUTORIAL;
    }
    // Jeżeli zamiast tego klikniemy O to
    // przejdziemy do opcji
    else if(IsKeyPressed(KEY_O))
        gameState = GameState::OPTIONS;
}

// Aktualizujemy grę
void Game::updateGame()
{
    // Pobieramy różnicę czasu pomiędzy klatkami
    float deltaTime = GetFrameTime();
    deltaTime = (1.0f / 60.0f);

    // Aktualizujemy obiekt śmiecia
    trash -> update(deltaTime, player -> lives, fxMissed);

    // Aktualizujemy obiekt gracza
    player -> update();

    // Dodajemy bonus co 100 punktów i zwiększamy
    // prędkość oraz odgrywamy dźwięk bonus.wav
    if (player -> score % 100 == 0 && player -> score % 500 != 0 && player -> score != 0)
    {
        PlaySound(fxBonus);
        player -> score += bonus;
        trash -> speed += multiplier;
    }
    else if(player -> score % 500 == 0 && player -> score != 0)
    {
        PlaySound(fxBigPoints);
        player -> score += bonus;
        trash -> speed += multiplier;
    }

    // Sprawdzamy kolizje i na tej podstawie
    // wywołujemy funkcję scoring jeżeli nie ma
    // kolizji to ogrywamy dźwięk missed
    if (CheckCollisionRecs(trash -> trashColBox, hopperColBox))
        scoring();

    // Wywołujemy aktualizacje animacji UI
    updateUI();

    // Przechodzimy do Game Over po stracie żyć
    if (player -> lives == 0)
        gameState = GameState::GAME_OVER;
}

// Aktualizujemy GameOver
void Game::updateGameOver()
{
    // Po wciśnięciu enter zapisujemy wynik jeżeli
    // jest większy niż poprzedni najwyższy wynik
    if (IsKeyPressed(KEY_ENTER))
    {   
        std::ofstream file ("Fonts/Old Score/oldScore.txt");

        if (player -> score > float(player -> hiScore))
        {
            if(file.is_open())
            {
                file << player -> score;
                file.close();
            }
        }
        // Przechodzimy do menu
        gameState = GameState::MENU;

        // Resetujemy gracza
        player -> score = 0;
        player -> lives = 3;
    }
}

// Aktualizujemy logo, jeżeli wciśniesz enter to
// przechodzisz do menu
void Game::updateLogo()
{
    if (IsKeyPressed(KEY_ENTER))
    {
        gameState = GameState::MENU;
    }

}

// Aktualizujemy tutorial i przechodzimy do
// wyboru poziomu trudności
void Game::updateTutorial() 
{
    if (IsKeyPressed(KEY_ENTER))
    {
        // Po przejściu zwalniamy pamięć VRAM
        tutorial -> unLoadTutorial();
        gameState = GameState::DIFICULTY_SCREEN;
    }
}

// Aktualizujemy ekran wyboru poziomu
// trudności
void Game::updateDifScreen() 
{
    // Jeżeli klikniesz 1, to zastosowane są takie
    // modyfikatory
    if(IsKeyPressed(KEY_ONE))
    {
        trash -> speed = 300.f;
        bonus = 10;
        multiplier = 30;
        StopMusicStream(music);
        gameState = GameState::GAME;
    }

    // Jeżeli klikniesz 2, to zastosowane są takie
    // modyfikatory
    if(IsKeyPressed(KEY_TWO))
    {
        trash -> speed = 400.f;
        bonus = 20;
        multiplier = 50;
        StopMusicStream(music);
        gameState = GameState::GAME;
    }

    // Jeżeli klikniesz 3, to zastosowane są takie
    // modyfikatory
    if(IsKeyPressed(KEY_THREE))
    {
        trash -> speed = 500.f;
        bonus = 30;
        multiplier = 70;
        StopMusicStream(music);
        gameState = GameState::GAME;
    }
}

// Aktualizujemy muzykę
void Game::updateMusic()
{
    // Aktualizujemy strumień
    UpdateMusicStream(music);

    // Pobieramy czas jaki gra muzyka
    timePlayed = GetMusicTimePlayed(music) / GetMusicTimeLength(music);

    // Jeżeli czas jest większy od długości
    // zerujemy go i gramy od nowa
    if (timePlayed > GetMusicTimeLength(music))
    {
        timePlayed = 0.f;
        PlayMusicStream(music);
    }

    // Sprawdzamy, czy muzyka ma być wyciszona
    if(options -> muted)
    {
        SetMusicVolume(music, 0);
        SetSoundVolume(fxHit, 0);
        SetSoundVolume(fxBonus, 0);
        SetSoundVolume(fxMissed, 0);
        SetSoundVolume(fxBigPoints, 0);
    }
    else
    {
        SetMusicVolume(music, 1);
        SetSoundVolume(fxHit, 1);
        SetSoundVolume(fxBonus, 1);
        SetSoundVolume(fxMissed, 1); 
        SetSoundVolume(fxBigPoints, 1); 
    }
}

// Aktualizujemy UI
void Game::updateUI()
{
    if(fCount >= frameDelay)
    {
        currFrame++;

        if(currFrame >= animFrames)
            currFrame = 0;
        
        // Pobieramy przesunięcie bitów pamięci
        offset = iCoin.width * iCoin.height * 4 * currFrame;

        // Aktualizujemy teksturę
        UpdateTexture(tCoin, ((unsigned char *)iCoin.data) + offset);

        fCount = 0;
    }
}

// Aktualizujemy ekran opcji
void Game::updateOptScreen()
{
    // Wywołujemy metodę update klast Options
    options -> update();

    // Jeżeli opcja jest zmieniona, włączamy
    // albo wyłączamy ciemny motyw
    if(!options -> changedTint)
        tint = WHITE;
    else
        tint = GRAY;

    // Jeżeli klikniesz backspace wracasz do menu
    if(IsKeyPressed(KEY_BACKSPACE))
        gameState = GameState::MENU;
}


// Aktualizujemy obiekty gry w zależności od jej
// stanu
void Game::update()
{
    updateMusic();
    
    switch (gameState)
    {
    case GameState::LOGO:
        updateLogo();
        break;
    case GameState::MENU:
        updateMenu();
        break;
    case GameState::OPTIONS:
        updateOptScreen();
        break;
    case GameState::TUTORIAL:
        updateTutorial();
        break;
    case GameState::DIFICULTY_SCREEN:
        updateDifScreen();
        break;
    case GameState::GAME:
        updateGame();
        break;
    case GameState::GAME_OVER:
        updateGameOver();
        break;
    }
}

// Wyświetlamy menu
void Game::renderMenu()
{
    DrawText("Trash Sorter ver. 0.0.7", sWidth / 2 - MeasureText("Trash Sorter ver. 0.0.7", 30), sHeight / 2 - 100, 30, BLACK);
    DrawText("Press ENTER to start", sWidth / 2 - MeasureText("Press ENTER to start", 25), sHeight / 2, 25, BLACK);
    DrawText("Press O to options", sWidth / 2 - MeasureText("Press O to options", 25), sHeight / 2 + 30, 25, BLACK);
}

// Renderujemy grę
void Game::renderGame()
{
    // Rysujemy teksturę tła i zsypu na śmieci
    DrawTextureEx(background, Vector2{ 0, 0 }, 0.f, 1.f, tint);
    DrawTextureEx(hopper, Vector2{ (float)sWidth / 2 - 128, (float)sHeight / 2 - 140 }, 0.f, 2.f, WHITE);

    // Rysujemy gracza i śmieci
    player->render();
    trash->render();

    // Rysujemy UI
    renderUI();
}

// Wyświetlamy GameOver
void Game::renderGameOver()
{
    DrawText("Game Over", sWidth / 2 - MeasureText("Game Over", 40) / 2, sHeight / 2 - 100, 40, BLACK);
    DrawText(("Final Score: " + std::to_string(player -> score)).c_str(), sWidth / 2 - MeasureText(("Final Score: " + std::to_string(player -> score)).c_str(), 30) / 2, sHeight / 2, 30, BLACK);
    DrawText(("Your Highscore: " + std::to_string(player -> hiScore)).c_str(), sWidth / 2 - MeasureText(("Your Highscore: " + std::to_string(player -> hiScore)).c_str(), 30) / 2, sHeight / 2 + 30, 30, BLACK);
    DrawText("Press ENTER to restart", sWidth / 2 - MeasureText("Press ENTER to restart", 20) / 2, sHeight / 2 + 70, 20, BLACK);
}

// Wyświetlamy logo
void Game::renderLogo()
{
    logo -> render();
}

// Wyświetlamy tutorial
void Game::renderTutorial()
{
    tutorial -> render();
}

// Wyświetlamy kran wyboru poziomu trudności
void Game::renderDifScreen() 
{
    DrawText("Choose your dificulty:", 30, 30, 40, BLACK);
    DrawText("1. Easy: Slower, low bonus (10 points)", 30, 80, 30, BLACK);
    DrawText("2. Normal: Normal, normal bonus (20 points)", 30, 130, 30, BLACK);
    DrawText("3. Hard: Faster, big bonus (30 points)", 30, 180, 30, BLACK);
    DrawText("Press numeric key on your keyboard", 30, 300, 25, BLACK);
}

// Wyświetlamy ekran opcji
void Game::renderOptScreen()
{
    options -> render();
}

// Rysowanie UI
void Game::renderUI()
{
    DrawTexture(tCoin, 10, 10, WHITE);
    DrawText((" x " + std::to_string(player->score)).c_str(), 64, 15, 40, BLACK);

    DrawTextureEx(tHeart, Vector2{sWidth - 130.f, 10.f}, 0.f, 0.7f, WHITE);
    DrawText((" x " + std::to_string(player->lives)).c_str(), sWidth - 85, 15, 40, BLACK);
}

// Wyświetlamy grę w zależności od jej stanu
void Game::render()
{
    BeginDrawing();

    ClearBackground(tint);

    switch (gameState)
    {
    case GameState::LOGO:
        renderLogo();
        break;
    case GameState::MENU:
        renderMenu();
        break;
    case GameState::OPTIONS:
        renderOptScreen();
        break;
    case GameState::TUTORIAL:
        renderTutorial();
        break;
    case GameState::DIFICULTY_SCREEN:
        renderDifScreen();
        break;
    case GameState::GAME:
        renderGame();
        break;
    case GameState::GAME_OVER:
        renderGameOver();
        break;
    }
    EndDrawing();
}
