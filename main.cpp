#include "raylib.h"

int main()
{
    int winHeight = 1024;
    int winWidth = 600;
    // Create game window
    InitWindow(winWidth, winHeight, "Space Ex");
    // Lock framerate to monitor rate
    SetWindowState(FLAG_VSYNC_HINT);

    //Load textures for background layers
    Texture2D background = LoadTexture("assets/backgrounds/bg1.png");
    Texture2D starLayer = LoadTexture("assets/backgrounds/ol4.png");

    float bgScroll = 0;
    float midScroll = -starLayer.height*2;
    float hozScroll = 0;

    //Game loop
    while (!WindowShouldClose())
    {
        //Update background positions
        bgScroll += 5.0f;
        midScroll += 20.0f;


        //Reset background position to loop
        if (bgScroll >= background.height*2) bgScroll = 0;
        if (midScroll >= starLayer.height*2) midScroll = -starLayer.height*2;

        BeginDrawing();
            ClearBackground(BLACK);

            //Draw backgrounds based on positions being updated
            DrawTextureEx(background, (Vector2){ 0, bgScroll}, 0.0f, 2.0f, WHITE);
            DrawTextureEx(background, (Vector2){ 0, -background.height*2 + bgScroll }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(starLayer, (Vector2){ 0, midScroll }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(starLayer, (Vector2){ 0, -starLayer.height + midScroll }, 0.0f, 2.0f, WHITE);

            
            DrawFPS(10,10);
        EndDrawing();
    }
    // Free memory
    UnloadTexture(background);
    UnloadTexture(starLayer);

    // Bit self explanatory
    CloseWindow();

    return 0;
}