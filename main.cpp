#include <string>
#include <iostream>
#include "raylib.h"
#include "raymath.h"

#include "src/game_variables.cpp"
#include "src/background.cpp"
#include "src/asteroidEnemy.cpp"
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
    Asteroid asteroid1;
    Asteroid asteroid2;
    Asteroid asteroid3;

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

            ////////////////////////////
            // Enemies
            ////////////////////////////                           
            asteroid1.updateAsteroid(600, 450.0f, 200.0f);     
            asteroid2.updateAsteroid(500, 120.0f, 120.0f);     
            asteroid3.updateAsteroid(100, 300.0f, 80.0f);     

            ////////////////////////////
            // Player bullet loop
            ////////////////////////////
            fireRateCounter++;       
            if (fireRateCounter > fireRate && IsKeyDown(KEY_SPACE))
            {
                fireRateCounter = 0;
                if (bullet[currentBullet].active == false) { bullet[currentBullet].active = true; }                
                currentBullet++;
                std::cout << currentBullet << std::endl;
                if (currentBullet >= maxBullets - 1){
                    currentBullet = 0;
                }
            }

            for (int i = 0; i < maxBullets; i++)
            {  
                if (bullet[i].active) {
                    bullet[i].updateBullet(playerShip.getShipPos(), playerShip.shipFrameHeight, playerShip.shipFrameWidth);
                }
            }

            ////////////////////////////
            // Collision detection
            ////////////////////////////
            
            //Ship hits
            if (playerShip.alive && frameCounter > 120) // Added min frame counter to counteract hitboxs spawning on top of eachother before positioned
            {
                //Asteroids
                if (CheckCollisionRecs(playerShip.hitBox, asteroid1.hitBox) && asteroid1.destroyed == false) { playerShip.alive = false; };
                if (CheckCollisionRecs(playerShip.hitBox, asteroid2.hitBox) && asteroid2.destroyed == false) { playerShip.alive = false; };
                if (CheckCollisionRecs(playerShip.hitBox, asteroid3.hitBox) && asteroid3.destroyed == false) { playerShip.alive = false; };
            }
            //Bullet hits
            for (int i = 0; i < maxBullets; i++)
            {  
                if (bullet[i].active) {
                    if (CheckCollisionRecs(bullet[i].hitBox, asteroid1.hitBox)) { bullet[i].active = false; asteroid1.destroyed = true; };
                    if (CheckCollisionRecs(bullet[i].hitBox, asteroid2.hitBox)) { bullet[i].active = false; asteroid2.destroyed = true; };
                    if (CheckCollisionRecs(bullet[i].hitBox, asteroid3.hitBox)) { bullet[i].active = false; asteroid3.destroyed = true; };
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