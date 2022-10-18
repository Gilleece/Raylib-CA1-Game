#include <string>
#include <iostream>
#include "raylib.h"
#include "raymath.h"

#include "src/game_variables.cpp"
#include "src/playerShip.cpp"


int main()
{
    // Create game window
    InitWindow(winWidth, winHeight, "Space Ex");
    // Lock framerate to monitor refresh rate
    SetWindowState(FLAG_VSYNC_HINT);


    ////////////////////////////
    // BACKGROUND
    ////////////////////////////

    //Load textures for background layers
    Texture2D background = LoadTexture("assets/backgrounds/bg1.png");
    Texture2D midLayer = LoadTexture("assets/backgrounds/ol1.png");
    Texture2D foreLayer = LoadTexture("assets/backgrounds/ol4.png");

    //Initial layer
    float bgScroll = 0;
    float midScroll = 0;
    float foreScroll = -foreLayer.height;

    ////////////////////////////
    // SHIP
    ////////////////////////////

    //Load the ship texture
    Texture2D shipSprite = LoadTexture("assets/sprites/ship.png");

    // Variables for sprite sheet selection
    float shipFrameWidth = shipSprite.width / 5.0f;     //Get the width of a single frame
    float shipFrameHeight = shipSprite.height / 2.0f;    //Get the height of a single frame
    float currentShipFrame = shipFrameWidth * 2.0f;     //Set the current frame
    float shipFlameFrame = 0;                           //Used to switch vertically to flicker the flame
    int flameSpeedCounter = 0;                          //Used to calculate the speed of the flame flicker


    ////////////////////////////
    // Gameloop
    ////////////////////////////
    while (!WindowShouldClose())
    {
        ////////////////////////////
        // BACKGROUND UPDATES
        ////////////////////////////
        
        //Update background positions
        bgScroll += 5.0f * gameSpeed;
        midScroll += 10.0f * gameSpeed;
        foreScroll += 7.5f * gameSpeed;

        //Reset background position to loop
        if (bgScroll >= background.height*2) bgScroll = 0;
        if (midScroll >= midLayer.height*2) midScroll = -midLayer.height*2;
        if (foreScroll >= foreLayer.height*2) foreScroll = -foreLayer.height*2;

        ////////////////////////////
        // PLAYER SHIP
        ////////////////////////////     
        
        flameSpeedCounter++; //increment counter

        // Flicker the engine fire by switching the sprite sheet vertically
        flameFlicker(&flameSpeedCounter, &shipFlameFrame, shipFrameHeight);
        
        Rectangle spriteRec = { currentShipFrame, shipFlameFrame, (float)shipFrameWidth, (float)shipFrameHeight };
        Vector2 shipPos = {winWidth / 2.0f - (shipSprite.width / 10), winHeight - (winHeight / 4)};
        Vector2 shipVel = {0.0f,0.0f};
        

        ////////////////////////////
        // DRAW FRAMES
        ////////////////////////////
        BeginDrawing();
            ClearBackground(BLACK);

            //Draw backgrounds based on positions being updated
            DrawTextureEx(background, (Vector2){ 0, bgScroll}, 0.0f, 2.0f, WHITE);
            DrawTextureEx(background, (Vector2){ 0, -background.height*2 + bgScroll }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(midLayer, (Vector2){ 0, midScroll }, 0.0f, 1.0f, WHITE);
            DrawTextureEx(midLayer, (Vector2){ 0, -midLayer.height + midScroll }, 0.0f, 1.0f, WHITE);
            DrawTextureEx(foreLayer, (Vector2){ 0, foreScroll }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(foreLayer, (Vector2){ 0, -foreLayer.height + foreScroll }, 0.0f, 2.0f, WHITE);

            DrawTextureRec(shipSprite, spriteRec, shipPos, WHITE);

            
            DrawFPS(10,10);
        EndDrawing();
    }

    // Close the window
    CloseWindow();

    // Free memory
    UnloadTexture(background);
    UnloadTexture(midLayer);
    UnloadTexture(foreLayer);
    return 0;
}