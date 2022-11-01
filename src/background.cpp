#include <string>
#include <iostream>
#include "raylib.h"
#include "raymath.h"

//Declaring background variables
struct Background {
    Texture2D background;   // "Furthest" layer
    Texture2D midLayer;     // "Middle" layer
    Texture2D foreLayer;    // "Foreground" layer
    float bgScroll;         // Scroll speed for background layer
    float midScroll;        // Scroll speed for middle layer
    float foreScroll;       // Scroll speed for foreground layer

    Background(Texture2D backgroundTexture, Texture2D midLayerTexture, Texture2D foreLayerTexture) {
        background = backgroundTexture;
        midLayer = midLayerTexture;
        foreLayer = foreLayerTexture;
        bgScroll = 0;
        midScroll = 0;
        foreScroll = 0;
    }

    void updateBackground() {
        //Update background positions
        bgScroll += 10.0f - (gameSpeed * 5.0f);
        midScroll += 12.5f - (gameSpeed * 5.0f);
        foreScroll += 15.0f - (gameSpeed * 5.0f);

        //Reset background position to loop
        if (bgScroll >= background.height*2) bgScroll = 0;
        if (midScroll >= midLayer.height*2) midScroll = 0;
        if (foreScroll >= foreLayer.height*2) foreScroll = 0;
    }

    void drawBackground() {
        updateBackground(); // Call from here to reduce calls within main.cpp
        //Draw backgrounds based on positions being updated
        DrawTextureEx(background, (Vector2){ 0, bgScroll}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(background, (Vector2){ 0, -background.height*2 + bgScroll }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(midLayer, (Vector2){ 0, midScroll }, 0.0f, 1.0f, WHITE);
        DrawTextureEx(midLayer, (Vector2){ 0, -midLayer.height*2 + midScroll }, 0.0f, 1.0f, WHITE);
        DrawTextureEx(foreLayer, (Vector2){ 0, foreScroll }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(foreLayer, (Vector2){ 0, -foreLayer.height*2 + foreScroll }, 0.0f, 2.0f, WHITE);
    }

    void unloadBackground() {
        UnloadTexture(background);
        UnloadTexture(midLayer);
        UnloadTexture(foreLayer);
    }
};





