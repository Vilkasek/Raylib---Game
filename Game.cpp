#include "Game.hpp"
#include "raylib.h"

Game::Game()
{
    init();
}

Game::~Game()
{
    UnloadTexture(background);
    UnloadTexture(hopper);

    UnloadMusicStream(music);

    UnloadSound(fxHit);
    UnloadSound(fxBonus);

    delete player;
    delete trash;
    delete logo;
    delete tutorial;

    CloseAudioDevice();
    CloseWindow();
}

void Game::run()
{
    while (!WindowShouldClose())
    {
        update();
        render();
    }
}

void Game::initWindow()
{
    InitWindow(sWidth, sHeight, "Trash Sorter");
    SetTargetFPS(60);
}

void Game::initBackground()
{
    background = LoadTexture("Textures/Background.png");
}

void Game::initHopper()
{
    hopper = LoadTexture("Textures/Hopper.png");

    hopperColBox = { (float)sWidth / 2 - 25, (float)sHeight / 2 - 64, 50, 128 };
}

void Game::initMenu()
{
    menuFont = LoadFontEx("Fonts/ARCADECLASSIC.TTF", 32, 0, 250);
}

void Game::init()
{
    initWindow();
    initBackground();
    initHopper();
    initMenu();

    player = new Player();
    trash = new Trash();
    logo = new Logo();
    tutorial = new Tutorial();

    gameState = GameState::LOGO;

    InitAudioDevice();

    music = LoadMusicStream("Sounds/MenuSong.wav");

    fxHit = LoadSound("Sounds/Effects/Hit.wav");
    fxBonus = LoadSound("Sounds/Effects/Bonus.wav");
}

void Game::checkTexture(int i)
{
    if (trash -> currentTexture.id == trash -> textures[i].id)
    {
        PlaySound(fxHit);

        trash -> setPosition();
        trash -> setCurrentTexture();
        player -> score += 10;
    }
}

void Game::scoring()
{
    if (player -> upState == 1)
        checkTexture(0);

    if (player -> rightState == 1)
        checkTexture(2);

    if (player -> leftState == 1)
        checkTexture(1);
}

void Game::updateMenu()
{
    std::ifstream file ("Fonts/Old Score/oldScore.txt");

    if(file.is_open())
    {
        file >> player -> hiScore;
        file.close();
    }
    if (IsKeyPressed(KEY_ENTER))
    {
        tutorial -> loadTutorial();
        gameState = GameState::TUTORIAL;
    }
}

void Game::updateGame()
{
    float deltaTime = GetFrameTime();
    deltaTime = (1.0f / 60.0f);

    trash -> update(deltaTime, player -> lives);
    player -> update();

    if (player -> score % 100 == 0 && player -> score != 0)
    {
        PlaySound(fxBonus);
        player -> score += bonus;
        trash -> speed += trash -> speed * multiplier;
    }

    if (CheckCollisionRecs(trash -> trashColBox, hopperColBox))
        scoring();

    if (player -> lives == 0)
        gameState = GameState::GAME_OVER;
}

void Game::updateGameOver()
{
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
        gameState = GameState::MENU;
        player -> score = 0;
        player -> lives = 3;
    }
}

void Game::updateLogo()
{
    if (IsKeyPressed(KEY_ENTER))
    {
        gameState = GameState::MENU;
        PlayMusicStream(music);
    }

}

void Game::updateTutorial() 
{
    if (IsKeyPressed(KEY_ENTER))
    {
        tutorial -> unLoadTutorial();
        gameState = GameState::DIFICULTY_SCREEN;
    }
}

void Game::updateDifScreen() 
{
    if(IsKeyPressed(KEY_ONE))
    {
        trash -> speed = 300.f;
        bonus = 10;
        multiplier = 0.01f;
        StopMusicStream(music);
        gameState = GameState::GAME;
    }
    if(IsKeyPressed(KEY_TWO))
    {
        trash -> speed = 400.f;
        bonus = 20;
        multiplier = 0.02f;
        StopMusicStream(music);
        gameState = GameState::GAME;
    }
    if(IsKeyPressed(KEY_THREE))
    {
        trash -> speed = 500.f;
        bonus = 30;
        multiplier = 0.03f;
        StopMusicStream(music);
        gameState = GameState::GAME;
    }
}

void Game::updateMusic()
{
    UpdateMusicStream(music);

    timePlayed = GetMusicTimePlayed(music) / GetMusicTimeLength(music);

    if (timePlayed > GetMusicTimeLength(music))
    {
        timePlayed = 0.f;
        PlayMusicStream(music);
    }
}

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

void Game::renderMenu()
{
    DrawText("Trash Sorter ver. 0.0.5", sWidth / 2 - MeasureText("Trash Sorter ver. 0.0.5", 30), sHeight / 2 - 100, 30, BLACK);
    DrawText("Press ENTER to start", sWidth / 2 - MeasureText("Press ENTER to start", 25), sHeight / 2, 25, BLACK);
}

void Game::renderGame()
{
    DrawTextureEx(background, Vector2{ 0, 0 }, 0.f, 1.f, WHITE);
    DrawTextureEx(hopper, Vector2{ (float)sWidth / 2 - 128, (float)sHeight / 2 - 140 }, 0.f, 2.f, WHITE);

    player->render();
    trash->render();

    DrawText(("Score: " + std::to_string(player->score)).c_str(), 10, 10, 20, BLACK);
    DrawText(("Lives: " + std::to_string(player->lives)).c_str(), sWidth - 85, 10, 20, BLACK);
}

void Game::renderGameOver()
{
    DrawText("Game Over", sWidth / 2 - MeasureText("Game Over", 40) / 2, sHeight / 2 - 100, 40, BLACK);
    DrawText(("Final Score: " + std::to_string(player -> score)).c_str(), sWidth / 2 - MeasureText(("Final Score: " + std::to_string(player -> score)).c_str(), 30) / 2, sHeight / 2, 30, BLACK);
    DrawText(("Your Hiscore: " + std::to_string(player -> hiScore)).c_str(), sWidth / 2 - MeasureText(("Your Hiscore: " + std::to_string(player -> hiScore)).c_str(), 30) / 2, sHeight / 2 + 30, 30, BLACK);
    DrawText("Press ENTER to restart", sWidth / 2 - MeasureText("Press ENTER to restart", 20) / 2, sHeight / 2 + 70, 20, BLACK);
}

void Game::renderLogo()
{
    logo -> render();
}

void Game::renderTutorial()
{
    tutorial -> render();
}

void Game::renderDifScreen() 
{
    DrawText("Choose your dificulty:", 30, 30, 40, BLACK);
    DrawText("1. Easy:", 30, 80, 30, BLACK);
    DrawText("2. Normal:", 30, 130, 30, BLACK);
    DrawText("3. Hard:", 30, 180, 30, BLACK);
    DrawText("Press numeric key on your keyboard", 30, 300, 25, BLACK);
}

void Game::render()
{
    BeginDrawing();

    ClearBackground(WHITE);
    switch (gameState)
    {
    case GameState::LOGO:
        renderLogo();
        break;
    case GameState::MENU:
        renderMenu();
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
