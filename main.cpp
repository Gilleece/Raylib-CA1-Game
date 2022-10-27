#include <string>
#include <iostream>
#include "raylib.h"
#include "raymath.h"

#include "src/game_variables.cpp"
#include "src/background.cpp"
#include "src/playerShip.cpp"
#include "src/playerBullet.cpp"
#include "src/asteroidEnemy.cpp"


int main()
{
    ////////////////////////////
    // Initilization
    ////////////////////////////
    InitWindow(winWidth, winHeight, "Space Fighter (most original title of all time)");    // Create game window
    SetWindowState(FLAG_VSYNC_HINT);                // Enable Vsync
    SetWindowState(FLAG_MSAA_4X_HINT);              // Turn on MSAA
    SetTargetFPS(60);                               // Lock FPS to 60


    ////////////////////////////
    // Create game objects
    ////////////////////////////
    Background background(
        LoadTexture("assets/backgrounds/bg2.png"),
        LoadTexture("assets/backgrounds/ol2.png"),
        LoadTexture("assets/backgrounds/ol3.png")
        );                                          // Create the background object
    PlayerShip playerShip;                          // Create the player ship object
    Bullet bullet[maxBullets];
    Asteroid asteroid;

    ////////////////////////////
    // Gameloop
    ////////////////////////////
    while (!WindowShouldClose())
    {
        frameCounter++;
        BeginDrawing();
            ClearBackground(BLACK);                 // Clear the background and paint it black, not strictly necessary but handy for debugging

            background.drawBackground();            // Background call per frame
            playerShip.drawShip();                  // Ship call per frame       

            if (frameCounter % 300 == 0)
            {
                asteroid.active = true;
            }
            
            asteroid.updateAsteroid();     

            ////////////////////////////
            // Player bullet loop
            ////////////////////////////
            fireRateCounter++;       
            if (fireRateCounter > fireRate && IsKeyDown(KEY_SPACE))
            {
                fireRateCounter = 0;
                bullet[currentBullet].active = true;
                currentBullet++;
            }

            for (int i = 0; i < maxBullets; i++)
            {  
                if (bullet[i].active) {
                    bullet[i].updateBullet(playerShip.getShipPos(), playerShip.shipFrameHeight, playerShip.shipFrameWidth);
                }
            }
        EndDrawing();
    }

    ////////////////////////////
    // Tidying up
    ////////////////////////////
    CloseWindow();                                  // Close the window
    background.unloadBackground();                  // Free memory
    playerShip.UnloadShip();                        // Free memory
    for (int i = 0; i < maxBullets; i++)
    {
        bullet[i].unloadBullet();
    }
    
    
    return 0;                                       // Successful exit code
}