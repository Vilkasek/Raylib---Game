#pragma once

#include "raylib.h"

#include "Player.hpp"
#include "Trash.hpp"
#include "Logo.hpp"
#include "Tutorial.hpp"
#include "Options.hpp"

#include <iostream>
#include <string>
#include <fstream>

enum class GameState
{
	LOGO,
    MENU,
	OPTIONS,
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

public:
	const int sWidth = 800;
	const int sHeight = 800;

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
	void updateOptScreen();

	void updateMusic();

	void update();

    void renderMenu();
    void renderGame();
    void renderGameOver();
	void renderLogo();
	void renderTutorial();
	void renderDifScreen();
	void renderOptScreen();

	void render();

private:
	float multiplier = { 0 };
	float bonus = { 0 };

	float timePlayed = { 0 };

	Texture2D background = { 0 };
	Texture2D hopper = { 0 };

	Rectangle hopperColBox = { 0 };

	Player *player = nullptr;
	Trash *trash = nullptr;
	Logo *logo = nullptr;
	Tutorial *tutorial = nullptr;
	Options *options = nullptr;

    GameState gameState = GameState::LOGO;
    Font menuFont = { 0 };

    Music music = { 0 };

	Sound fxHit = { 0 };
	Sound fxBonus = { 0 };

	Color tint = WHITE;
};
