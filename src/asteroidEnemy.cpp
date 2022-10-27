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
    Rectangle hitBox;    // Rectange for collision detection
    Vector2 pos;         // XY position
    bool firstTime;      // Check if initial loop
    bool active;         // Bool to show if object still exists

    Asteroid() {
        sprite = LoadTexture("assets/sprites/AsteroidBrown.png");   // object sprite sheet
        frameWidth = sprite.width;                                  // Width of object
        frameHeight = sprite.height;                                // Height of object   
        travelSpeed = 0.05f;                                         // object speed
        travelDistance = 0.0f;
        pos = {0.0f,-frameHeight};                                  // XY position
        firstTime = true;                                          // Set to true
        active = false;                                             // Bool to show if object still exists
    }

    void updateAsteroid(int frequency, float startMod, float horizontalMovement) {
        if (frameCounter % frequency == 0 && !firstTime)
            {
                active = true;
                pos.x += startMod;
                firstTime = false;
            } 
            else if (frameCounter % frequency == 0) 
            {
                active = true;
            }
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
                if (pos.x >= winHeight - frameWidth) {
                    pos.x = startMod;
                } else {
                    pos.x += horizontalMovement;
                }
            }
        hitBox = {pos.x, pos.y, frameWidth, frameHeight};  
        DrawTextureRec(sprite, rec, pos, WHITE);
        }
    }
    void unload() {
        UnloadTexture(sprite);
    }
};

