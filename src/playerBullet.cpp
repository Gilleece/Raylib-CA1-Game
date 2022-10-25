#include <string>
#include <iostream>
#include "raylib.h"
#include "raymath.h"

//Declaring bullet struct
struct {
    Texture2D bulletSprite;     //Bullet sprite sheet
    float bulletFrameWidth;     //Width of a bullet
    float bulletFrameHeight;    //Height of a bullet
    float bulletType;           //Switch through the 2 available bullet types
    float bulletFrame;          //Tracks the current animation frame
    int bulletAnimationCounter; //Used to calculate speed of bullet animation
    int fireDelayCounter;       //Stops bullet spam, allows mechanical tweaking
    float bulletSpeed;          //projectile speed
    Rectangle bulletRec;        //Rectange to draw bullet onto
    Vector2 bulletPos;          // XY position
    Vector2 bulletVel;          // velocity of bullet
} bullet;

//Initialize the bullet
void initBullet() {
    bullet.bulletSprite = LoadTexture("assets/sprites/laser-bolts.png");
    bullet.bulletFrameWidth = bullet.bulletSprite.width / 2.0f;
    bullet.bulletFrameHeight = bullet.bulletSprite.height / 2.0f;
    bullet.bulletType = bullet.bulletFrameHeight;
    bullet.bulletFrame = 0.0f;
    bullet.bulletAnimationCounter = 0;
    bullet.fireDelayCounter = 5;
    bullet.bulletSpeed = 1.0f;
    bullet.bulletPos = {20,20};
    bullet.bulletVel = {0.0f, 0.0f};
}

void updateBullet() {
    bullet.bulletRec = { bullet.bulletFrame, bullet.bulletType, (float)bullet.bulletFrameWidth, (float)bullet.bulletFrameHeight };

    // Checks whether to alternate bullet animation sprite and then resets counter
    bullet.bulletAnimationCounter++;
    if (bullet.bulletAnimationCounter == 50)
        {
            bullet.bulletFrame == 0.0f ? bullet.bulletFrame = bullet.bulletFrameWidth - 8.0f : bullet.bulletFrame = 0.0f; // Flip the frame horizontally, the -8 is to correct for the sprite sheet not being centered
            bullet.bulletAnimationCounter = 0;
        }


}

void drawBullet() {
    DrawTextureRec(bullet.bulletSprite, bullet.bulletRec, bullet.bulletPos, WHITE);
}

void UnloadBullet() {
    UnloadTexture(bullet.bulletSprite);
}