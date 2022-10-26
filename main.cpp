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
    Background background;                          // Create the background object
    PlayerShip playerShip;                          // Create the player ship object
    Bullet bullet;

    ////////////////////////////
    // Gameloop
    ////////////////////////////
    while (!WindowShouldClose())
    {
        // Update variables
        background.updateBackground();                         // Update background variables
        playerShip.updateShip();                               // Update ship variables
        bullet.updateBullet();
        
        // DRAW FRAMES
        BeginDrawing();
            ClearBackground(BLACK);                 // Clear the background and paint it black

            background.drawBackground();                       // Draw the background
            playerShip.drawShip();                             // Draw the ship
            bullet.drawBullet();
            
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