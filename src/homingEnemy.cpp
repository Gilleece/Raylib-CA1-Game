#include <string>
#include <iostream>
#include "raylib.h"
#include "raymath.h"

// Declaring Homer class - This enemy homes in on the player ship, hence the name.
struct Homer {
    Texture2D sprite;    // object sprite sheet
    float frameWidth;    // Width of object
    float frameHeight;   // Height of object  
    float currentFrame;  // For animating the sprite 
    float travelSpeed;   // object speed
    float travelAmount;  // object distance
    Rectangle rec;       // Rectange to draw bullet onto
    Rectangle hitBox;    // Rectange for collision detection
    Vector2 pos;         // XY position
    bool firstTime;      // Check if initial loop
    bool active;         // Bool to show if object still exists
    bool destroyed;      // Bool to show if destroyed
    int opacity;         // counter to handle opacity fade
    int colourFade;      // Used to shift colour on death 

    Homer() {
        sprite = LoadTexture("assets/sprites/homerSprite.png");   // object sprite sheet
        frameWidth = sprite.width / 2;                              // Width of object
        frameHeight = sprite.height;                                // Height of object
        currentFrame = 0.0f;                                        // Init to zero   
        travelSpeed = 4.0f;                                        // object speed
        travelAmount = 0.0f;                                        // Set the distance travelled to 0.
        pos = {0.0f,-frameHeight};                                  // XY position
        firstTime = true;                                           // Set to true
        active = false;                                             // Bool to show if object still exists
        destroyed = false;                                          // If true then player has shot the Homer
        opacity = 255;                                              // Make completely non-transparent (What is the opposite of transparent? Oh, it's opaque...) Okay, let me say that again. Make completely opaque. That now makes sense why the opacity would be 255 and not 0, I always thought it was the opposite away around, but no.
        colourFade = 255;                                           // Set colours to default
    }

    void updateHomer(int frequency, float startMod, float horizontalMovement, Vector2 targetPos) { // Function that handles updating the homer on each frame
        if (frameCounter % frequency == 0 && firstTime)                            // This loop only runs the very first time the Homer is generated, at the beginning of the game (even on replays it is not called again)
            {
                active = true;                                                     // Make the Homer active
                pos.x += startMod;                                                 // The initial position is determined by the startMod passed though, important for providing unique positioning for each Homer initially
                firstTime = false;                                                 // Mark as no longer the first time
            } 
            else if (frameCounter % frequency == 0 && frameCounter > 300)          // Check if the frame counter is over 300, so that aesteroids only start briefly after game starts, frequency is passed through to determine how often the Homer is made active
            {
                active = true;                                                     // Make the Homer active
            }
        if (active && !destroyed)                                                  // If active and not destroyed
        {        
            rec = { currentFrame, 0.0f, frameWidth, frameHeight};                  // Set the rectangle to drawn on as the sprite width and height, 0,0 vector to draw as is
            travelAmount = travelSpeed + ((1.0f - gameSpeed) / 2);                 // Update travel amount
            // Homing behaviour
            if (pos.x <= targetPos.x)
            {
                pos.x += travelAmount / 2;
            }
            else if (pos.x >= targetPos.x) {
                pos.x -= travelAmount / 2;
            }
            if (pos.y <= targetPos.y)
            {
                pos.y += travelAmount;
            }
            else if (pos.y >= targetPos.y) {
                pos.y -= travelAmount;
            }
            hitBox = {pos.x, pos.y, frameWidth, frameHeight};                      // Draw the hit box for collision detection. As detractors of MC hammer would say "You can indeed touch this"
            if (pos.y > winHeight)                                                 // If Homer goes beyond the bottom of the scrteen 
            {
                active = false;                                                    // Set it as inactive
                pos.y = -frameHeight;                                              // Set the y position to negativeFrameheight
                travelAmount = 0.0f;                                             // Reset travel distance to 0
                hitBox = {-100, -100, 0, 0};                                       // This sets the hitbox in an arbitrary off screen location to stop hitbox blocking bullets or movement after Homer is destroyed
                if (pos.x >= winHeight - frameWidth)                               // if the position of the aesteroid is beyonc the right hand side of the screen
                {
                    pos.x = startMod;                                              // Set the position to the startMod to repeat the loop. The aesteroids complete their loop at different times so the positions seem more erratic and interesting than they actually are.
                } 
                else 
                {
                    pos.x += horizontalMovement;                                   // Move the Homer to the right to change where it falls next loop
                }
            }

        if (frameCounter % 5 == 0 && currentFrame == 0)                            // If loop to animate ship flame, modulus 5 is the speed of the animation. If current Frame is the default
        {
            currentFrame = frameWidth;                                             // Update it to the frameWidth to show the second frame
        }
        else if (frameCounter % 5 == 0 && currentFrame == frameWidth)              // Otherwise, if the opposite is true
        {
            currentFrame = 0.0f;                                                   // Set it back to zero
        }        

        DrawTextureRec(sprite, rec, pos, CLITERAL(Color){ 255, (unsigned char)colourFade, (unsigned char)colourFade, (unsigned char)opacity});   // Draw the texture of the Homer
        }
        if (destroyed && opacity > 0)                                                                   // If destroyed and still visible
        {
            hitBox = {-100, -100, 0, 0};                                                                // To stop hitbox blocking bullets or movement after Homer is destroyed
            pos.y-= 3;                                                                                  // Move Homer back a bit to reflect the impact of the bullet
            opacity -= 5;                                                                               // Reduce opacity, to fade out the aesteroid
            if (colourFade > 0) {colourFade -= 15;};                                                    // Change the colour to animate the destruction, checking if above 0 so colour doesn't loop around as the opacity drops at a slower rate
            DrawTextureRec(sprite, rec, pos, CLITERAL(Color){ 255, (unsigned char)colourFade, (unsigned char)colourFade, (unsigned char)opacity});// Draw the aesteroid
        } 
        else if (destroyed && opacity <= 0)                                                             // When Homer is destroyed and has become fully transparent
        {                                       
            active = false;                                                                             // Mark Homer as inactive
            pos.y = -frameHeight;                                                                       // Reset Homer position
            travelAmount = 0.0f;                                                                      // Reset travel distance to 0
            if (pos.x >= winHeight - frameWidth)                                                        // if the position of the aesteroid is beyonc the right hand side of the screen
            {       
                pos.x = startMod;                                                                       // Set Homer to startMod
            } 
            else 
            {
                pos.x += horizontalMovement;                                                            // Move the Homer to the right to change where it falls next loop
            }
            playerScore += 50;                                                                          // Increment player score
            destroyed = false;                                                                          // No longer destroyed
            opacity = 255;                                                                              // Make fully opaque. Great word.
            colourFade = 255;                                                                           // Reset colours
        }
    }
    void unload() {                                                                                     // Function for unloading the texture
        UnloadTexture(sprite);                                                                          // Unload to free memory
    }


};

