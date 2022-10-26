#include <string>
#include <iostream>
#include "raylib.h"
#include "raymath.h"

//Declaring bullet struct
struct Bullet {
    Texture2D bulletSprite = LoadTexture("assets/sprites/laser-bolts.png");     //Bullet sprite sheet
    float bulletFrameWidth = bulletSprite.width / 2.0f;                         //Width of a bullet
    float bulletFrameHeight = bulletSprite.height / 2.0f;                       //Height of a bullet
    float bulletType = 0;                                                       //Switch through the 2 available bullet types
    float bulletFrame = 0.0f;                                                   //Tracks the current animation frame
    int bulletAnimationCounter  = 0;                                            //Used to calculate speed of bullet animation
    int fireDelayCounter = 5;                                                   //Stops bullet spam, allows mechanical tweaking
    float bulletSpeed = 1.0f;                                                   //projectile speed
    Rectangle bulletRec;                                                        //Rectange to draw bullet onto
    Vector2 bulletPos = {20,20};                                                // XY position
    Vector2 bulletVel = {0.0f, 0.0f};                                           // velocity of bullet
    bool active = true;                                                         // Bool to show if bullet still exists

    void updateBullet() {
    bulletRec = { bulletFrame, bulletType, (float)bulletFrameWidth, (float)bulletFrameHeight};

    // Checks whether to alternate bullet animation sprite and then resets counter
    bulletAnimationCounter++;
    if (bulletAnimationCounter == 5)
        {
            bulletFrame == 0.0f ? bulletFrame = bulletFrameWidth - 8.0f : bulletFrame = 0.0f; // Flip the frame horizontally, the -8 is to correct for the sprite sheet not being centered
            bulletAnimationCounter = 0;
        }
    }

    void drawBullet() {
    DrawTextureRec(bulletSprite, bulletRec, bulletPos, WHITE);
    }

    void UnloadBullet() {
    UnloadTexture(bulletSprite);
    }
};