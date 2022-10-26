#include <string>
#include <iostream>
#include "raylib.h"
#include "raymath.h"

#include "src/game_variables.cpp"
#include "src/background.cpp"
#include "src/playerShip.cpp"
#include "src/playerBullet.cpp"


int main()
{
    ////////////////////////////
    // Initilization
    ////////////////////////////
    InitWindow(winWidth, winHeight, "Space Fighter (most original title of all time)");    // Create game window
    SetWindowState(FLAG_VSYNC_HINT);                // Enable Vsync
    SetWindowState(FLAG_MSAA_4X_HINT);              // Turn on MSAA
    SetTargetFPS(60);                               // Lock FPS to 60
    Background background(
        LoadTexture("assets/backgrounds/bg2.png"),
        LoadTexture("assets/backgrounds/ol2.png"),
        LoadTexture("assets/backgrounds/ol3.png")
        );                                          // Create the background object
    PlayerShip playerShip;                          // Create the player ship object
    Bullet bullet[maxBullets];

    ////////////////////////////
    // Gameloop
    ////////////////////////////
    while (!WindowShouldClose())
    {        
        // Game Loop
        BeginDrawing();
            ClearBackground(BLACK);                 // Clear the background and paint it black

            background.drawBackground();            // Background call per frame
            playerShip.drawShip();                  // Ship call per frame
            bullet[0].fireBullet();                 // Bullet call per frame
            

            // Debugging - Comment out on finish
            DrawFPS(10,10);                         // Show an FPS counter for debugging purposes
        EndDrawing();
    }

    ////////////////////////////
    // Tidying up
    ////////////////////////////
    CloseWindow();                                  // Close the window
    background.unloadBackground();                             // Free memory
    playerShip.UnloadShip();                                   // Free memory
    
    return 0;                                       // Successful exit code
}