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
    bool destroyed;      // Bool to show if destroyed
    int opacity;         // counter to handle opacity fade

    Asteroid() {
        sprite = LoadTexture("assets/sprites/AsteroidBrown.png");   // object sprite sheet
        frameWidth = sprite.width;                                  // Width of object
        frameHeight = sprite.height;                                // Height of object
        travelDistance = 0.0f;
        pos = {0.0f,-frameHeight};                                  // XY position
        firstTime = true;                                          // Set to true
        active = false;                                             // Bool to show if object still exists
        destroyed = false;                                          // If true then player has shot the asteroid
        opacity = 255;
    }

    void updateAsteroid(int frequency, float startMod, float horizontalMovement) {
        travelSpeed = 5.05f - (gameSpeed * 5.0f);
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
        if (active && !destroyed)
        {        
            rec = { 0.0f, 0.0f, frameWidth, frameHeight};
            // Asteroid position
            pos = {pos.x, pos.y + travelDistance};
            travelDistance += travelSpeed;
            hitBox = {pos.x, pos.y, frameWidth, frameHeight};
            if (pos.y > winHeight)
            {
                active = false;
                pos.y = -frameHeight;
                travelDistance = 0.0f;
                hitBox = {-100, -100, 0, 0}; // To stop hitbox blocking bullets or movement after asteroid is destroyed
                if (pos.x >= winHeight - frameWidth) 
                {
                    pos.x = startMod;
                } 
                else 
                {
                    pos.x += horizontalMovement;
                }
            }
          
        DrawTextureRec(sprite, rec, pos, CLITERAL(Color){ 255, 255, 255, (unsigned char)opacity});
        }
        if (destroyed && opacity > 0) 
        {
            hitBox = {-100, -100, 0, 0}; // To stop hitbox blocking bullets or movement after asteroid is destroyed
            pos.y-= 3;
            opacity -= 15;
            DrawTextureRec(sprite, rec, pos, CLITERAL(Color){ 255, 255, 255, (unsigned char)opacity});
        } 
        else if (destroyed && opacity <= 0)
        {
            active = false;
            pos.y = -frameHeight;
            travelDistance = 0.0f;
            if (pos.x >= winHeight - frameWidth) 
            {
                pos.x = startMod;
            } 
            else 
            {
                pos.x += horizontalMovement;
            }
            playerScore += 10;
            destroyed = false;
            opacity = 255;
        }
    }
    void unload() {
        UnloadTexture(sprite);
    }


};

