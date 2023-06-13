#pragma once

#include "raylib.h"

class Tutorial {
public:
	Tutorial();
	~Tutorial();

	void render();
    
    void loadTutorial();
    void unLoadTutorial();

private:
    Texture2D textures[3] = { 0 };
};