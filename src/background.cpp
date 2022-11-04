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

    Background(Texture2D backgroundTexture, Texture2D midLayerTexture, Texture2D foreLayerTexture) { // Constructor that takes in textures loaded in main.cpp
        background = backgroundTexture;                                                              // Set texture for back layer
        midLayer = midLayerTexture;                                                                  // Set texture for mid layer
        foreLayer = foreLayerTexture;                                                                // Set texture for fore layer
        bgScroll = 0;                                                                                // Init to 0;
        midScroll = 0;                                                                               // Init to 0;
        foreScroll = 0;                                                                              // Init to 0;
    }

    void updateBackground() {
        //Update background positions
        bgScroll += 10.0f - (gameSpeed * 5.0f);                                                     // Update position based on game speed
        midScroll += 12.5f - (gameSpeed * 5.0f);                                                    // Update position based on game speed
        foreScroll += 15.0f - (gameSpeed * 5.0f);                                                   // Update position based on game speed

        //Reset background position to loop
        if (bgScroll >= background.height*2) bgScroll = 0;                                          // Reset layer position if beyond texture height by 2
        if (midScroll >= midLayer.height*2) midScroll = 0;                                          // Reset layer position if beyond texture height by 2
        if (foreScroll >= foreLayer.height*2) foreScroll = 0;                                       // Reset layer position if beyond texture height by 2
    }

    void drawBackground() {                                                                             // Function to call for drawing the background
        updateBackground();                                                                             // Call from here to reduce calls within main.cpp
                                                                                                        // Draw backgrounds based on positions being updated
        DrawTextureEx(background, (Vector2){ 0, bgScroll}, 0.0f, 2.0f, WHITE);                          // Each layer is drawn twice, this allows a seamless loop
        DrawTextureEx(background, (Vector2){ 0, -background.height*2 + bgScroll }, 0.0f, 2.0f, WHITE);  // This layer is the same as the previous line, but positioned separate to loop
        DrawTextureEx(midLayer, (Vector2){ 0, midScroll }, 0.0f, 1.0f, WHITE);                          // The same process happens with the next 2 layers, for mid and foreground
        DrawTextureEx(midLayer, (Vector2){ 0, -midLayer.height*2 + midScroll }, 0.0f, 1.0f, WHITE);     // Also, to note, these 3 layers move at different speeds
        DrawTextureEx(foreLayer, (Vector2){ 0, foreScroll }, 0.0f, 2.0f, WHITE);                        // This creates parralax scrolling to provide a sense of depth
        DrawTextureEx(foreLayer, (Vector2){ 0, -foreLayer.height*2 + foreScroll }, 0.0f, 2.0f, WHITE);  // All layers are drawn with white tint to just preserve the original colour
    }

    void unloadBackground() {       // Function to call to collect the garbage
        UnloadTexture(background); // Free
        UnloadTexture(midLayer);   // The
        UnloadTexture(foreLayer);  // Memory
    }
};





