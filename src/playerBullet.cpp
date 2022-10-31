#include <string>
#include <iostream>
#include "raylib.h"
#include "raymath.h"

// Variables
const int fireRate = 30;
const int maxBullets = 50;
int fireRateCounter = fireRate;
int currentBullet = 0;

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
    Rectangle bulletRec;       // Rectange to draw bullet onto
    Vector2 bulletPos;         // XY position
    Vector2 currentPos;        // Updates the position independent of passed through ship position
    float bulletTravel;        // Distance travelled of bullet
    bool fired;                // To track bullet state
    bool active;               // Bool to show if bullet still exists
    Rectangle hitBox;

    Bullet() {
        bulletSprite = LoadTexture("assets/sprites/laser-bolts.png");     // Bullet sprite sheet
        bulletFrameWidth = bulletSprite.width / 2.0f;                     // Width of a bullet
        bulletFrameHeight = bulletSprite.height / 2.0f;                   // Height of a bullet
        bulletType = 0;                                                   // Switch through the 2 available bullet types
        bulletFrame = 0.0f;                                               // Tracks the current animation frame
        bulletAnimationCounter  = 0;                                      // Used to calculate speed of bullet animation
        fireDelayCounter = 5;                                             // Stops bullet spam, allows mechanical tweaking
        bulletSpeed = 8.0f;                                               // projectile speed
        bulletTravel = 0.0f;                                              // Distance travelled of bullet
        fired = false;                                                    // To track bullet state
        active = false;                                                   // Set to false initially
    }

    void updateBullet(Vector2 startPos, float shipHeight, float shipWidth) {
        if (!fired)
        {
            currentPos = startPos;
            fired = true;
        }
        
        bulletRec = { bulletFrame, bulletType, (float)bulletFrameWidth, (float)bulletFrameHeight};
        // Bullet position
        bulletPos = {currentPos.x + shipWidth / 5 + 1.0f, currentPos.y - bulletTravel - shipHeight / 5};
        hitBox = {bulletPos.x, bulletPos.y, bulletFrameWidth, bulletFrameHeight};
        bulletTravel += bulletSpeed;

        if (bulletPos.y < 0)
        {
            active = false;
            fired = false;
        }
        

        // Checks whether to alternate bullet animation sprite and then resets counter
        bulletAnimationCounter++;
        if (bulletAnimationCounter == 5)
            {
                bulletFrame == 0.0f ? bulletFrame = bulletFrameWidth - 4.0f : bulletFrame = 0.0f; // Flip the frame horizontally, the -8 is to correct for the sprite sheet not being centered
                bulletAnimationCounter = 0;
            }
        
        DrawTextureRec(bulletSprite, bulletRec, bulletPos, WHITE);
    }
    void unloadBullet() {
        UnloadTexture(bulletSprite);
    }
};

