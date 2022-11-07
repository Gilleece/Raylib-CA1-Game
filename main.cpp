#include <string>
#include <iostream>
#include "raylib.h"
#include "raymath.h"

#include "src/game_variables.cpp"               //Source files are included here
#include "src/background.cpp"                   // Proper practice would be to include them as header files
#include "src/asteroidEnemy.cpp"                // However I had a particularly awkward IDE setup (VS Code on linux beta for chromebook, only device I had on the go)
#include "src/playerShip.cpp"                   // Due to this it was easier to just organise code by including the files directly rather than with headers
#include "src/playerBullet.cpp"                 // Just wanted to note this here
#include "src/homingEnemy.cpp"



int main()
{
    ////////////////////////////
    // Initilization
    ////////////////////////////
    InitWindow(winWidth, winHeight, "Space Fighter (most original title of all time)");    // Create game window
    InitAudioDevice();                                                                     // Initialize the audio device
    Music backgroundMusic = LoadMusicStream("assets/sounds/bgm.mp3");
    PlayMusicStream(backgroundMusic);
    SetWindowState(FLAG_VSYNC_HINT);                                                       // Enable Vsync
    SetWindowState(FLAG_MSAA_4X_HINT);                                                     // Turn on MSAA
    SetTargetFPS(60);                                                                      // Lock FPS to 60
    Font mainFont = LoadFont("assets/fonts/font.TTF");                                     // Load font used for score counter
    initUI();                                                                              // Initialise the UI


    ////////////////////////////
    // Create game objaects
    ////////////////////////////
    Background startBackground(
        LoadTexture("assets/backgrounds/bg1.png"),
        LoadTexture("assets/backgrounds/ol1.png"),
        LoadTexture("assets/backgrounds/ol4.png")
        );                                          // Create the background object for the start screen
    Background background(
        LoadTexture("assets/backgrounds/bg2.png"),
        LoadTexture("assets/backgrounds/ol2.png"),
        LoadTexture("assets/backgrounds/ol3.png")
        );                                          // Create the background object for the game loop
    PlayerShip playerShip;                          // Create the player ship object
    Bullet bullet[maxBullets];                      // Create the bullet objects
    Asteroid asteroid1;                             // Create Asteroid object
    Asteroid asteroid2;                             // Create Asteroid object
    Asteroid asteroid3;                             // Create Asteroid object
    Asteroid asteroid4;                             // Create Asteroid object
    Asteroid asteroid5;                             // Create Asteroid object
    Homer homer1;                                   // Create Homer object
    Homer homer2;                                   // Create Homer object

    ////////////////////////////
    // Gameloop
    ////////////////////////////
    while (!WindowShouldClose())                        // Main gameloop, carries on until user presses ESC or Xs off the window
    {
        frameCounter++;                                 // Increment the frame counter on each frame while window is open
        UpdateMusicStream(backgroundMusic);             // Reads and plays data from the bgm.mp3 file
        BeginDrawing();                                 // Begin drawing frames
            ClearBackground(BLACK);                     // Clear the background and paint it black, not strictly necessary but handy for debugging
            if (startScreen) {                          // Checks if the game is currently on the start screen
                gameSpeed = 2.0f;                       // Set game speed for the animation of the start screen
                startBackground.drawBackground();       // Call the function to draw the background for the start screen background
                drawStartScreen();                      // Draw the other elements of the start screen, the logic is also contained here for pressing start
            }

            else if (!gameOver)                         // Check that the game isn't over, this marks the primary gameloop
            {
                background.drawBackground();            // Background call per frame
                playerShip.drawShip();                  // Ship call per frame   

                ////////////////////////////
                // Enemies
                //////////////////////////// 
                // Asteroid                          
                asteroid1.updateAsteroid(30, 40.0f, 30.0f);     // Updates the aesteroid on each frame, the parameters passed through are
                asteroid2.updateAsteroid(20, 600.0f, 50.0f);    // in order: frequency, startMod and horizontalMovement
                asteroid3.updateAsteroid(90, 120.0f, 100.0f);   // Frequency: How often the aestroid falls down the screen
                asteroid4.updateAsteroid(70, 450.0f, 180.0f);   // StartMod: A modifier to set the initial horizontal position so that the aesteroids each exhibit individual behaviour
                asteroid5.updateAsteroid(5, 300.0f, 270.0f);   // horizontalMovement: How much the aesteroid moves across the screen upon each loop of its behaviour

                //Homer
                homer1.updateHomer(400, 150.0f, 200.0f, playerShip.getShipPos());
                homer2.updateHomer(900, 150.0f, 200.0f, playerShip.getShipPos());
                ////////////////////////////
                // Player bullet loop
                ////////////////////////////
                fireRateCounter++;                                                                          // Increments the variable for the fireCounter. This was kept separate from the frameRateCounter to allow for control separate to the main game speed to provide an additional means of increasing difficult over time beyond
                if (fireRateCounter > fireRate && IsKeyDown(KEY_SPACE))                                     // Check if the the bullet can be fired and if the space bar is pressed down
                {
                    fireRateCounter = 0;                                                                    // Reset fireRateCounter
                    if (bullet[currentBullet].active == false) { bullet[currentBullet].active = true; }     // If the current bullet is false then set it to active           
                    currentBullet++;                                                                        // Increment to the next bullet
                    if (currentBullet >= maxBullets - 1){                                                   // If the current bullet is more than the max amount of bullets
                        currentBullet = 0;                                                                  // Reset the current bullet to 0
                    }
                }

                for (int i = 0; i < maxBullets; i++)                                                        // Loop for incrementing through bullets to update and draw them
                {  
                    if (bullet[i].active) {                                                                                     // If the bullet is active
                        bullet[i].updateBullet(playerShip.getShipPos(), playerShip.shipFrameHeight, playerShip.shipFrameWidth); // Then update it, passing through the necessary parameters so that it can be drawn in the correct location
                    }
                }
                ////////////////////////////
                // Collision detection
                ////////////////////////////
                
                //Ship hits
                if (playerShip.alive) // Only check for collisions if ship is alive
                {
                    //Asteroids
                    if (CheckCollisionRecs(playerShip.hitBox, asteroid1.hitBox) && asteroid1.destroyed == false) { playerShip.deathLoop();}; // Check for collision between the ship and an asteroid
                    if (CheckCollisionRecs(playerShip.hitBox, asteroid2.hitBox) && asteroid2.destroyed == false) { playerShip.deathLoop(); }; // If a collision happens then the playership is destroyed
                    if (CheckCollisionRecs(playerShip.hitBox, asteroid3.hitBox) && asteroid3.destroyed == false) { playerShip.deathLoop(); }; // I deliberately do not destroy the asteroids as it makes more sense in my mind that the aesteroid would carry on unhindered
                    if (CheckCollisionRecs(playerShip.hitBox, asteroid4.hitBox) && asteroid4.destroyed == false) { playerShip.deathLoop(); }; 
                    if (CheckCollisionRecs(playerShip.hitBox, asteroid5.hitBox) && asteroid5.destroyed == false) { playerShip.deathLoop(); };

                    // Homers
                    if (CheckCollisionRecs(playerShip.hitBox, homer1.hitBox) && homer1.destroyed == false) { playerShip.deathLoop(); homer1.destroyed= true; };
                    if (CheckCollisionRecs(playerShip.hitBox, homer2.hitBox) && homer2.destroyed == false) { playerShip.deathLoop(); homer2.destroyed= true; };

                }
                //Bullet hits
                for (int i = 0; i < maxBullets; i++)                                                                                       // Loop through the bullets
                {  
                    if (bullet[i].active) {                                                                                                // Check if the current bullet in the iteration is active
                        if (CheckCollisionRecs(bullet[i].hitBox, asteroid1.hitBox)) { bullet[i].resetBullet(); asteroid1.deathLoop(); };   // If it's active then perform collision checks for each object that it can interact with 
                        if (CheckCollisionRecs(bullet[i].hitBox, asteroid2.hitBox)) { bullet[i].resetBullet(); asteroid2.deathLoop(); };   // This collision code could have all probably been refactored into its own source file...I may or may not do that. I guess if you're reading this then you know how that went!
                        if (CheckCollisionRecs(bullet[i].hitBox, asteroid3.hitBox)) { bullet[i].resetBullet(); asteroid3.deathLoop(); };   // Anyway, upon a collision the bullet is reset. This behaviour seems more logcial to me, having the bullet disappear. A potential power up would be "super bullets" that don't disappear and carry on and can hit another enemy in its path. What a classic!
                        if (CheckCollisionRecs(bullet[i].hitBox, asteroid4.hitBox)) { bullet[i].resetBullet(); asteroid4.deathLoop(); };   // The aestroid is marked as destroyed, which the asteroid update loop handles
                        if (CheckCollisionRecs(bullet[i].hitBox, asteroid5.hitBox)) { bullet[i].resetBullet(); asteroid5.deathLoop(); };
                        if (CheckCollisionRecs(bullet[i].hitBox, homer1.hitBox)) { bullet[i].resetBullet(); homer1.deathLoop(); };
                        if (CheckCollisionRecs(bullet[i].hitBox, homer2.hitBox)) { bullet[i].resetBullet(); homer2.deathLoop(); };
                    }
                }
            }
            
            if (!startScreen)                                                                                       // Only run this code if the game is not on the start screen
            {
                checkGameState(&playerShip.lives, &playerShip.shipPos, &playerShip.shipVel, playerShip.startPos);   // Check the game state, the lives are passed through as a pointer so that the actual lives can be modified at the correct memory address rather than just modifying a reference to it which would break the logic I wrote
                drawUI(mainFont, playerShip.lives);                                                                 // Draw the ui, passes through the font used for the score and passes through the player lives (in this case just a reference) to display the number of lives
            }
            
        EndDrawing(); // Stop drawing the game
    }
    ////////////////////////////
    // Tidying up
    ////////////////////////////            
    playerShip.UnloadShip();                 // Free Memory               
    for (int i = 0; i < maxBullets; i++)     
    {
        bullet[i].unloadBullet();
    }                                        // Loop through all bullets and free memory
    startBackground.unloadBackground();      // Free Memory                           
    background.unloadBackground();           // Free Memory
    UnloadMusicStream(backgroundMusic);      // Free Memory
    CloseWindow();                           // Close the window
    
    return 0;                                // Successful exit code
}