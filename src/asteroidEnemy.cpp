#include <string>
#include <iostream>
#include "raylib.h"
#include "raymath.h"

// Declaring asteroid struct
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
    Sound deathSound;    // For loading and playing the sound when destroyed

    Asteroid() {
        sprite = LoadTexture("assets/sprites/AsteroidBrown.png");       // object sprite sheet
        frameWidth = sprite.width;                                      // Width of object
        frameHeight = sprite.height;                                    // Height of object   
        travelSpeed = 0.05f;                                            // object speed
        travelDistance = 0.0f;                                          // Set the distance travelled to 0. IT HAS GONE NOWHERE YET!
        pos = {0.0f,-frameHeight};                                      // XY position
        firstTime = true;                                               // Set to true
        active = false;                                                 // Bool to show if object still exists
        destroyed = false;                                              // If true then player has shot the asteroid
        opacity = 255;                                                  // Make completely non-transparent (What is the opposite of transparent? Oh, it's opaque...) Okay, let me say that again. Make completely opaque. That now makes sense why the opacity would be 255 and not 0, I always thought it was the opposite away around, but no.
        deathSound = LoadSound("assets/sounds/asteroidDestroyed.wav");  // Load sound of homer ship destroyed
        SetSoundVolume(deathSound, 0.5f);                               // Set volume for the death sound
    }

    void updateAsteroid(int frequency, float startMod, float horizontalMovement) { // Function that handles updating the aesteroid on each frame
        if (frameCounter % frequency == 0 && firstTime)                            // This loop only runs the very first time the asteroid is generated, at the beginning of the game (even on replays it is not called again)
            {
                active = true;                                                     // Make the asteroid active
                pos.x += startMod;                                                 // The initial position is determined by the startMod passed though, important for providing unique positioning for each asteroid initially
                firstTime = false;                                                 // Mark as no longer the first time
            } 
            else if (frameCounter % frequency == 0 && frameCounter > 300)          // Check if the frame counter is over 300, so that aesteroids only start briefly after game starts, frequency is passed through to determine how often the asteroid is made active
            {
                active = true;                                                     // Make the asteroid active
            }
        if (active && !destroyed)                                                  // If active and not destroyed
        {        
            rec = { 0.0f, 0.0f, frameWidth, frameHeight};                          // Set the rectangle to drawn on as the sprite width and height, 0,0 vector to draw as is
            // Asteroid position                                                    
            pos = {pos.x, pos.y + travelDistance};                                 // Sets position, travel distance is added to create motion. 
            travelDistance += travelSpeed + ((1.0f - gameSpeed) / 2);              // Travel disance is incremented here based on travel speed and a lovely formula that took me far longer to figure out than I would care to admit
            hitBox = {pos.x, pos.y, frameWidth, frameHeight};                      // Draw the hit box for collision detection. As detractors of MC hammer would say "You can indeed touch this"
            if (pos.y > winHeight)                                                 // If asteroid goes beyond the bottom of the scrteen 
            {
                active = false;                                                    // Set it as inactive
                pos.y = -frameHeight;                                              // Set the y position to negativeFrameheight
                travelDistance = 0.0f;                                             // Reset travel distance to 0
                hitBox = {-100, -100, 0, 0};                                       // This sets the hitbox in an arbitrary off screen location to stop hitbox blocking bullets or movement after asteroid is destroyed
                if (pos.x >= winHeight - frameWidth)                               // if the position of the aesteroid is beyonc the right hand side of the screen
                {
                    pos.x = startMod;                                              // Set the position to the startMod to repeat the loop. The aesteroids complete their loop at different times so the positions seem more erratic and interesting than they actually are.
                } 
                else 
                {
                    pos.x += horizontalMovement;                                   // Move the asteroid to the right to change where it falls next loop
                }
            }
          
        DrawTextureRec(sprite, rec, pos, CLITERAL(Color){ 255, 255, 255, (unsigned char)opacity});      // Draw the texture of the asteroid
        }
        if (destroyed && opacity > 0)                                                                   // If destroyed and still visible
        {
            hitBox = {-100, -100, 0, 0};                                                                // To stop hitbox blocking bullets or movement after asteroid is destroyed
            pos.y-= 3;                                                                                  // Move asteroid back a bit to reflect the impact of the bullet
            opacity -= 15;                                                                              // Reduce opacity, to fade out the aesteroid
            DrawTextureRec(sprite, rec, pos, CLITERAL(Color){ 255, 255, 255, (unsigned char)opacity});  // Drw the aesteroid
        } 
        else if (destroyed && opacity <= 0)                                                             // When asteroid is destroyed and has become fully transparent
        {                                       
            active = false;                                                                             // Mark asteroid as inactive
            pos.y = -frameHeight;                                                                       // Reset asteroid position
            travelDistance = 0.0f;                                                                      // Reset travel distance to 0
            if (pos.x >= winHeight - frameWidth)                                                        // if the position of the aesteroid is beyonc the right hand side of the screen
            {       
                pos.x = startMod;                                                                       // Set asteroid to startMod
            } 
            else 
            {
                pos.x += horizontalMovement;                                                            // Move the asteroid to the right to change where it falls next loop
            }
            playerScore += 10;                                                                          // Increment player score
            destroyed = false;                                                                          // No longer destroyed
            opacity = 255;                                                                              // Make fully opaque. Great word.
        }
    }

    void deathLoop() {
        PlaySound(deathSound);                                          // Play the death sound
        destroyed = true;                                               // Set asteroid alive status to false, this then allows for the rest of the death logic to trigger        
    }

    void unload() {                                                                                     // Function for unloading the texture
        UnloadTexture(sprite);                                                                          // Unload to free memory
    }


};

