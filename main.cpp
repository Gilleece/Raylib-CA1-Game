#include <string>
#include <iostream>
#include "raylib.h"

#include "src/game_variables.cpp"
#include "src/level_1.cpp"


int main()
{

    // Create game window
    InitWindow(winWidth, winHeight, "Space Ex");
    // Lock framerate to monitor rate
    SetWindowState(FLAG_VSYNC_HINT);

    //Variable that sets the game speed
    float gameSpeed = 1.0f;

    Texture2D background;
    Texture2D midLayer;
    Texture2D foreLayer;

    level_1(gameSpeed, background, midLayer, foreLayer);

    // Close the window
    CloseWindow();

    // Free memory
    UnloadTexture(background);
    UnloadTexture(midLayer);
    UnloadTexture(foreLayer);
    return 0;
}