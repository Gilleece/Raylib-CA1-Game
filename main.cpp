#include "raylib.h"

int main()
{
    // Create game window
    InitWindow(600, 1024, "Space Ex");
    // Lock framerate to monitor rate
    SetWindowState(FLAG_VSYNC_HINT);

    //Load textures for background layers
    Texture2D background = LoadTexture("assets/backgrounds/bg1.png");
    Texture2D starLayer = LoadTexture("assets/backgrounds/ol3.png");

    float bgScroll = -background.height;
    float midScroll = -starLayer.height;

    //Game loop
    while (!WindowShouldClose())
    {
        //Update background positions
        bgScroll += 20.0f;
        midScroll += 20.0f;


        //Reset background position to loop
        if (bgScroll >= background.height*2) bgScroll = 0;
        if (midScroll >= starLayer.height) midScroll = 0;

        BeginDrawing();
            ClearBackground(BLACK);

            //Draw backgrounds based on positions being updated
            DrawTextureEx(background, (Vector2){ 0, bgScroll }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(background, (Vector2){ 0, -background.height + bgScroll }, 0.0f, 2.0f, WHITE);
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