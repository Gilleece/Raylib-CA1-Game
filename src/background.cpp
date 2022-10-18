#include <string>
#include <iostream>
#include "raylib.h"
#include "raymath.h"

//Declaring background variables
Texture2D background;   // "Furthest" layer
Texture2D midLayer;     // "Middle" layer
Texture2D foreLayer;    // "Foreground" layer
float bgScroll;         // Scroll speed for background layer
float midScroll;        // Scroll speed for middle layer
float foreScroll;       // Scroll speed for foreground layer

void initBackground() {
    background = LoadTexture("assets/backgrounds/bg1.png");
    midLayer = LoadTexture("assets/backgrounds/ol1.png");
    Texture2D foreLayer = LoadTexture("assets/backgrounds/ol4.png");
    bgScroll = 0;
    midScroll = 0;
    foreScroll = -foreLayer.height;
}

void updateBackground() {
    //Update background positions
    bgScroll += 5.0f * gameSpeed;
    midScroll += 10.0f * gameSpeed;
    foreScroll += 7.5f * gameSpeed;

    //Reset background position to loop
    if (bgScroll >= background.height*2) bgScroll = 0;
    if (midScroll >= midLayer.height*2) midScroll = -midLayer.height*2;
    if (foreScroll >= foreLayer.height*2) foreScroll = -foreLayer.height*2;
}

void drawBackground() {
    //Draw backgrounds based on positions being updated
    DrawTextureEx(background, (Vector2){ 0, bgScroll}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(background, (Vector2){ 0, -background.height*2 + bgScroll }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(midLayer, (Vector2){ 0, midScroll }, 0.0f, 1.0f, WHITE);
    DrawTextureEx(midLayer, (Vector2){ 0, -midLayer.height + midScroll }, 0.0f, 1.0f, WHITE);
    DrawTextureEx(foreLayer, (Vector2){ 0, foreScroll }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(foreLayer, (Vector2){ 0, -foreLayer.height + foreScroll }, 0.0f, 2.0f, WHITE);
}

void unloadBackground() {
    UnloadTexture(background);
    UnloadTexture(midLayer);
    UnloadTexture(foreLayer);
}