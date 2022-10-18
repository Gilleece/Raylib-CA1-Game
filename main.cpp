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

    initShip(); // Initiatilize the ship

    //Gameloop
    while (!WindowShouldClose())
    {
        
        //Update background positions
        bgScroll += 5.0f * gameSpeed;
        midScroll += 10.0f * gameSpeed;
        foreScroll += 7.5f * gameSpeed;

        //Reset background position to loop
        if (bgScroll >= background.height*2) bgScroll = 0;
        if (midScroll >= midLayer.height*2) midScroll = -midLayer.height*2;
        if (foreScroll >= foreLayer.height*2) foreScroll = -foreLayer.height*2;
    
        updateShip(); //Update ship variables
        

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

            drawShip(); // Draw the ship
            
            DrawFPS(10,10);
        EndDrawing();
    }

    // Close the window
    CloseWindow();

    // Free memory
    UnloadTexture(background);
    UnloadTexture(midLayer);
    UnloadTexture(foreLayer);
    UnloadShip();
    return 0;
}