#include <string>
#include <iostream>
#include "raylib.h"
#include "raymath.h"

// Variables
const int fireRate = 20;
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
    int fireDelayCounter;      // Stops bullet spam, allows mechanical tweaking
    float bulletSpeed;         // projectile speed
    Rectangle bulletRec;       // Rectange to draw bullet onto
    Vector2 bulletPos;         // XY position
    Vector2 currentPos;        // Updates the position independent of passed through ship position
    float bulletTravel;        // Distance travelled of bullet
    bool fired;                // To track bullet state
    bool active;               // Bool to show if bullet still exists
    Rectangle hitBox;          // Reactangle for the hitbox
    Sound bulletSound;         // Bullet sound      

    Bullet() {
        bulletSprite = LoadTexture("assets/sprites/laser-bolts.png");     // Bullet sprite sheet
        bulletFrameWidth = bulletSprite.width / 2.0f;                     // Width of a bullet
        bulletFrameHeight = bulletSprite.height / 2.0f;                   // Height of a bullet
        bulletType = 0;                                                   // Switch through the 2 available bullet types
        bulletFrame = 0.0f;                                               // Tracks the current animation frame
        fireDelayCounter = 30;                                            // Stops bullet spam, allows mechanical tweaking
        bulletSpeed = 15.0f;                                              // projectile speed
        bulletTravel = 0.0f;                                              // Distance travelled of bullet
        fired = false;                                                    // To track bullet state
        active = false;                                                   // Set to false initially
        bulletSound = LoadSound("assets/sounds/bullet.wav");              // Load bullet wav
    }

    void updateBullet(Vector2 startPos, float shipHeight, float shipWidth) {                                    // Function to call to update bullets
        if (!fired)                                                                                             // If fired
        {           
            currentPos = startPos;                                                                              // Set the currentPosition to the start position passed though
            fired = true;                                                                                       // Set to fired 
            bulletPos = {currentPos.x + shipWidth / 5 + 1.0f, currentPos.y - bulletTravel - shipHeight / 5};    // Update the bullet position to the initial frame at the tip of ship
            SetSoundVolume(bulletSound, 0.6);                                                                   // Make the sound quiet enough to be not irritating 
            SetSoundPitch(bulletSound, float(GetRandomValue(90, 99)) / 100);                                    // Randomws sets the pitch between 0.90 and 0.99 to make the sound less repetitive
            PlaySound(bulletSound);                                                                             // Play the bullet sound
        }
        
        if (fired)                                                                                              // If bullet has been fired
        {
            bulletRec = { bulletFrame, bulletType, (float)bulletFrameWidth, (float)bulletFrameHeight};          // Set rectangle for drawing sprite onto, including the type of bullet by the Y axis
            bulletPos = {currentPos.x + shipWidth / 5 + 1.0f, currentPos.y - bulletTravel - shipHeight / 5};    // Set the bullet position, initially at the middle tip of the front of the ship
            hitBox = {bulletPos.x, bulletPos.y, bulletFrameWidth, bulletFrameHeight};                           // Set the hitboxc position as the same
            bulletTravel += bulletSpeed - (gameSpeed * 5.0f);                                                   // Increment bullet travel based on game speed

            if (bulletPos.y < 0)                                                                                // If bullet goes off the top edge of the screen
            {
                resetBullet();                                                                                  // Call the function to reset it so that it can be used later
            }
            

            // Checks whether to alternate bullet animation sprite and then resets counter
            if (frameCounter % 5 == 0)                                                                // If statement based on framecounter controls speed of animation
                {
                    bulletFrame == 0.0f ? bulletFrame = bulletFrameWidth - 4.0f : bulletFrame = 0.0f; // Flip the frame horizontally, the -8 is to correct for the sprite sheet not being centered
                }
            
            DrawTextureRec(bulletSprite, bulletRec, bulletPos, WHITE);                                // Draw the bullet
        }
    }

    void resetBullet()                                                                                // Function for resetting the bullet, hence the name "resetBullet". 
    {
        bulletTravel = 0.0f;                                                                          // Set the travel amount of bullet to 0
        active = false;                                                                               // Set bullet to not active, this means it isn't shown or have any effect etc
        fired = false;                                                                                // Set fired to false
    }

    void unloadBullet()                                                                               // Function for garbage collection
    {
        UnloadTexture(bulletSprite);                                                                  // Unload the bullet texture/sprite
    }
};

