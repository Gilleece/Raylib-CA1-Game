#include <string>
#include <iostream>
#include "raylib.h"
#include "raymath.h"

////////////////////////////
// General Game Loop
////////////////////////////

// Window size
const int winHeight = 900; // Game window width is set here
const int winWidth = 700;  // Game window height is set here

// Game speed
float gameSpeed = 1.0f; // Game speed is set here, is updated by various functions

// Game progress
int frameCounter = 0;   // For tracking progress of the level, when to spawn enemies etc
int startScreen = true; // Bool to determine if the start screen should be show

// Tracking variables
int playerScore = 0;    // Set player score to 0 for init score
bool gameOver = false;  // Set game over to false initially


////////////////////////////
// UI
////////////////////////////


// Text
const char* startScreenSubText = nullptr;   // nullptr set to allocate memory for text that will be put here later
const char* playText = nullptr;             // nullptr set to allocate memory for text that will be put here later
const char* gameOverText = nullptr;         // nullptr set to allocate memory for text that will be put here later, you might be noticing a trend here
const char* replayText = nullptr;           // This one is diffrent. Actually no, that's a lie, it is just a nullptr set to allocate memory for text that will be put here later
const char* scoreText = "SCORE: ";          // This text is already set as I could be certain that this wouldn't be changed.
int textOpacity = 255;                      // Variable for controlling opacity of the text, used for pulsing text animation on start screen. Init to fully opaque.

// Elements
Texture2D lifeSprite;                       // Create object for the life texture
Rectangle lifeRec;                          // Create object for the life texture rectangle
Texture2D logo;                             // Create object for the logo texture
Rectangle logoRec;                          // Create object for the logo texture rectangle
Texture2D controlsImage;                    // Create object for the controls image
Rectangle controlsRec;                      // Create object for the controls image rectangle

void initUI() {
    lifeSprite = LoadTexture("assets/sprites/shipLife.png");                     // Load the life sprite
    lifeRec = {0, 0, (float)lifeSprite.width, (float)lifeSprite.height};         // Set the sprite frame within the rectangle
    logo = LoadTexture("assets/misc/gameLogo.png");                              // load the startscreen logo image
    logoRec = {0, 0, (float)logo.width, (float)logo.height};                     // Set the frame within the rectangle
    controlsImage = LoadTexture("assets/misc/controls.png");                     // Load the controls image
    controlsRec = {0,0, (float)controlsImage.width, (float)controlsImage.height};// Set the frame within the rectangle
}


void drawUI(Font mainFont, int lives)                                       // Function to call to draw the UI
{
    //Draw Score
    DrawTextEx(mainFont, scoreText, (Vector2) {10.0f, 10.0f }, (float)mainFont.baseSize, 0, RED);                        // Draw the score text, uses the font loaded in main.cpp
    DrawTextEx(mainFont, TextFormat("%05i", playerScore), (Vector2) {160.0f, 10.0f }, (float)mainFont.baseSize, 0, RED); // The 05 in %05i is to format the score to 5 zeroes, purely for aesthetic purporses

    //Draw Lives
    if (lives > 0) { DrawTextureRec(lifeSprite, lifeRec, (Vector2){winWidth - (float)lifeSprite.width - 10, 2}, WHITE);};       // If 1 life left, draw the far right life sprite
    if (lives > 1) { DrawTextureRec(lifeSprite, lifeRec, (Vector2){winWidth - ((float)lifeSprite.width*2) - 15, 2}, WHITE);};   // If 2 lives left, draw the middle life sprite
    if (lives > 2) { DrawTextureRec(lifeSprite, lifeRec, (Vector2){winWidth - ((float)lifeSprite.width*3) - 20, 2}, WHITE);};   // If 3 lives left, draw the far left life sprite
    
    


    if (gameOver) {                                                                                             // Check if the game is over
        int textWidth = MeasureText(gameOverText, 60);                                                          // Measure the size of the gameOverText to enable positioning it correctly
        int replayTextWidth = MeasureText(replayText, 30);                                                      // Measure the size of the replayText to enable positioning it correctly
        DrawText(gameOverText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, GOLD);     // Draw the text using the measurements from 2 lines prior to position it in the center
        DrawText(replayText, GetScreenWidth() / 2 - replayTextWidth / 2, GetScreenHeight() / 2 + 60, 30, RED);  // Draw the text using the measurements from 2 lines prior to position it in the center
        
    }    
}

void drawStartScreen()                              // Function to call to draw the start screen
{
    if (IsKeyPressed(KEY_ENTER) && startScreen)     // Check if enter is pressed to start the game
    {
        gameSpeed = 1.0f;                           // If so, set game speed to 1 (start screen is set to 2 for A E S T H E T I C S)
        startScreen = false;                        // Disable the start screen
        frameCounter = 0;                           // Reset the frame counter so that logic based on it (i.e waiting 300 frames before spawning an aesteroid) runs at the correct time
    }

    startScreenSubText = "A very originally titled Shoot 'Em Up";   // Set the text
    playText = "Press ENTER to play!";                              // Set more text
    int subWidth = MeasureText(startScreenSubText, 30);             // Measure the text size for positioning
    int playTextWidth = MeasureText(playText, 45);                  // Same as prior line
    DrawTextureRec(logo, logoRec, (Vector2){(float)GetScreenWidth() / 2 - logo.width / 2, (float)GetScreenHeight() / 3 - logo.height}, WHITE);                // Draw the logo image
    DrawText(startScreenSubText, GetScreenWidth() / 2 - subWidth / 2, GetScreenHeight() / 3 - 30, 30, GOLD);                                                  // Draw the text underneath the logo
    if (textOpacity > 0) {textOpacity -= 5;} else {textOpacity = 255;};                                                                                       // Loop to check transparency of the text and to enable the flashing animation
    DrawText(playText, GetScreenWidth() / 2 - playTextWidth / 2, GetScreenHeight() - 120, 45, CLITERAL(Color){ 255, 255, 255, (unsigned char)textOpacity});   // Draw this text, take in the opacity number being modified in the prior line
    DrawTextureRec(controlsImage, controlsRec, (Vector2){(float)GetScreenWidth() / 2 - controlsImage.width / 2, (float)GetScreenHeight() / 2}, WHITE);   // Draw the controls image

}


////////////////////////////
// Game state
////////////////////////////


void checkGameState(int *lives, Vector2 *shipPos, Vector2 *shipVel, Vector2 startPos) {
    if (frameCounter % 600 == 0 && gameSpeed > 0.1f) {gameSpeed -= 0.1f;}                   // Speeds up date every 10 seconds, until max speed
    if (*lives == 0) {gameOver = true;}                                                     // Set Game over state to true on 0 lives
    if (gameOver) {                                                                         // Applies the text to be displayed
        gameOverText = "Game Over!";                                                        // Set the text
        replayText = "Press Enter to Play Again.";                                          // Set the text
    }
    if (replayText && IsKeyPressed(KEY_ENTER))                                              // If player presses enter, while replaytext is displayed, then reset game state and restart game
    {
        gameOverText = nullptr;                                                             // This section resets the game variables upon replay, here sets the text to a nullptr again
        replayText = nullptr;                                                               // This also sets it to a nullptr. In hindsight this isn't really necessary as I don't check for the nullptr anywhere (could be used in lieu of a boolean) but it works fine so no need to really change
        gameSpeed = 1.0f;                                                                   // Reset game speed
        playerScore = 0;                                                                    // Reset player score, ouch.
        frameCounter = 0;                                                                   // Reset frameCounter
        *lives = 3;                                                                         // Modify lives directly by pointer
        *shipPos = startPos;                                                                // Reset ship position, also by pointer
        *shipVel = {0.0f, 0.0f};                                                            // Reset ship velocity, by POINTER
        gameOver = false;                                                                   // Set game over state back to false
    }
    
}