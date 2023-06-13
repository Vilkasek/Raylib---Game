#pragma once

#include "raylib.h"

#include "Player.hpp"
#include "Trash.hpp"
#include "Logo.hpp"
#include "Tutorial.hpp"

#include <iostream>
#include <string>
#include <fstream>

enum class GameState
{
	LOGO,
    MENU,
	TUTORIAL,
	DIFICULTY_SCREEN,
    GAME,
    GAME_OVER,
};

class Game
{
public:
	Game();
  	~Game();

	void run();

private:
	void initWindow();
	void initBackground();
	void initHopper();
    void initMenu();

	void init();

	void checkTexture(int i);
	void scoring();

    void updateMenu();
    void updateGame();
    void updateGameOver();
	void updateLogo();
	void updateTutorial();
	void updateDifScreen();

	void update();

    void renderMenu();
    void renderGame();
    void renderGameOver();
	void renderLogo();
	void renderTutorial();
	void renderDifScreen();

	void render();
        
private:
	const int sWidth = 800;
	const int sHeight = 800;

	float multiplier = { 0 };
	float bonus = { 0 };

	Texture2D background = { 0 };
	Texture2D hopper = { 0 };

	Rectangle hopperColBox = { 0 };

	Player *player = nullptr;
	Trash *trash = nullptr;
	Logo *logo = nullptr;
	Tutorial *tutorial = nullptr;

    GameState gameState = GameState::LOGO;
    Font menuFont = { 0 };

    Music music = { 0 };
};
