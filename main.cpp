#include <string>
#include <iostream>
#include "raylib.h"
#include "raymath.h"

#include "src/game_variables.cpp"
#include "src/background.cpp"
#include "src/playerShip.cpp"


int main()
{
    ////////////////////////////
    // Initilization
    ////////////////////////////
    InitWindow(winWidth, winHeight, "Space Fighter (most original title of all time)");    // Create game window
    SetWindowState(FLAG_VSYNC_HINT);                // Lock framerate to monitor refresh rate
    initBackground();                               // Initialize the background textures
    initShip();                                     // Initiatilize the ship

    ////////////////////////////
    // Gameloop
    ////////////////////////////
    while (!WindowShouldClose())
    {
        // Update variables
        updateBackground();                         // Update background variables
        updateShip();                               // Update ship variables
        
        // DRAW FRAMES
        BeginDrawing();
            ClearBackground(BLACK);                 // Clear the background and paint it black

            drawBackground();                       // Draw the background
            drawShip();                             // Draw the ship
            
            DrawFPS(10,10);                         // Show an FPS counter for debugging purposes
        EndDrawing();
    }

    ////////////////////////////
    // Tidying up
    ////////////////////////////
    CloseWindow();                                  // Close the window
    unloadBackground();                             // Free memory
    UnloadShip();                                   // Free memory
    
    return 0;                                       // Successful exit code
}