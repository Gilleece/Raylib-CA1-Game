#include <string>
#include <iostream>
#include "raylib.h"
#include "raymath.h"

// Declaring bullet struct
struct Asteroid {
    Texture2D sprite;    // object sprite sheet
    float frameWidth;    // Width of object
    float frameHeight;   // Height of object   
    float travelSpeed;   // object speed
    float travelDistance;// object distance
    Rectangle rec;       // Rectange to draw bullet onto
    Vector2 pos;         // XY position
    bool active;         // Bool to show if object still exists

    Asteroid() {
        sprite = LoadTexture("assets/sprites/AsteroidBrown.png");   // object sprite sheet
        frameWidth = sprite.width;                                  // Width of object
        frameHeight = sprite.height;                                // Height of object   
        travelSpeed = 0.1f;                                         // object speed
        travelDistance = 0.0f;
        pos = {frameWidth + 10,-frameHeight};                                              // XY position
        active = false;                                              // Bool to show if object still exists
    }

    void updateAsteroid() {
        if (active)
        {        
            rec = { 0.0f, 0.0f, frameWidth, frameHeight};
            // Asteroid position
            pos = {pos.x, pos.y + travelDistance};
            travelDistance += travelSpeed;
            if (pos.y > winHeight)
            {
                active = false;
                pos.y = -frameHeight;
                travelDistance = 0.0f;
                pos.x = (pos.x >= winHeight - frameWidth) ? pos.x = frameWidth + 10 : pos.x += winHeight / 5;
            }
            
        DrawTextureRec(sprite, rec, pos, WHITE);
        }
    }
    void unload() {
        UnloadTexture(sprite);
    }
};

