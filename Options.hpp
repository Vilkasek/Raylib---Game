#include "raylib.h"

class Options
{
public:
    Options();
    ~Options();

    void update();
    void render();

public:
    bool changedTint = false;
    bool muted = false;

private:
    void changeTint();
};