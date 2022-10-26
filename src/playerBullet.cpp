#include <string>
#include <iostream>
#include "raylib.h"
#include "raymath.h"

// Declaring bullet struct
struct Bullet {
    Texture2D bulletSprite;    // Bullet sprite sheet
    float bulletFrameWidth;    // Width of a bullet
    float bulletFrameHeight;   // Height of a bullet
    float bulletType;          // Switch through the 2 available bullet types
    float bulletFrame;         // Tracks the current animation frame
    int bulletAnimationCounter;// Used to calculate speed of bullet animation
    int fireDelayCounter;      // Stops bullet spam, allows mechanical tweaking
    float bulletSpeed;         // projectile speed
    float fireRate;            // Rate of fire
    Rectangle bulletRec;       // Rectange to draw bullet onto
    Vector2 bulletPos;         // XY position
    Vector2 bulletVel;         // velocity of bullet
    bool active;               // Bool to show if bullet still exists

    Bullet() {
        bulletSprite = LoadTexture("assets/sprites/laser-bolts.png");     // Bullet sprite sheet
        bulletFrameWidth = bulletSprite.width / 2.0f;                     // Width of a bullet
        bulletFrameHeight = bulletSprite.height / 2.0f;                   // Height of a bullet
        bulletType = 0;                                                   // Switch through the 2 available bullet types
        bulletFrame = 0.0f;                                               // Tracks the current animation frame
        bulletAnimationCounter  = 0;                                      // Used to calculate speed of bullet animation
        fireDelayCounter = 5;                                             // Stops bullet spam, allows mechanical tweaking
        bulletSpeed = 1.0f;                                               // projectile speed
        bulletPos = {20,20};                                              // XY position
        bulletVel = {0.0f, 0.0f};                                         // velocity of bullet
        fireRate = 1;                                                     // Rate of fire
        active = false;                                                   // Set to false initially
    }

    void updateBullet() {
    bulletRec = { bulletFrame, bulletType, (float)bulletFrameWidth, (float)bulletFrameHeight};

    // Checks whether to alternate bullet animation sprite and then resets counter
    bulletAnimationCounter++;
    if (bulletAnimationCounter == 5)
        {
            bulletFrame == 0.0f ? bulletFrame = bulletFrameWidth - 4.0f : bulletFrame = 0.0f; // Flip the frame horizontally, the -8 is to correct for the sprite sheet not being centered
            bulletAnimationCounter = 0;
        }
    }

    void drawBullet() {
    DrawTextureRec(bulletSprite, bulletRec, bulletPos, WHITE);
    }

    void fireBullet() {
        updateBullet();
        drawBullet();
    }

    void UnloadBullet() {
    UnloadTexture(bulletSprite);
    }
};