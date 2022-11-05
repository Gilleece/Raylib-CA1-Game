#include <string>
#include <iostream>
#include "raylib.h"
#include "raymath.h"

//Declaring ship struct
struct PlayerShip {
    //Ship Sprite
    Texture2D shipSprite = LoadTexture("assets/sprites/ship.png");      // Ship sprite sheet
    float shipFrameWidth = shipSprite.width / 5.0f;                     // Get the width of a single frame
    float shipFrameHeight = shipSprite.height / 2.0f;                   // Get the height of a single frame
    float shipFrameMod = 2.0f;                                          // Multiplier for cycling through frames, set here to enable switching spritesheet later for more animation frames if desired 
    float currentShipFrame = shipFrameWidth * shipFrameMod;             // Set the current frame
    Rectangle spriteRec;                                                // Ractangle for drawing the frame onto
    //Death Sprite
    Texture2D deathSprite = LoadTexture("assets/sprites/shipExplosion.png");    // Ship sprite sheet, not actually used to display the sprite sheet, it is just loaded here to calculate size
    float deathFrameWidth = deathSprite.width / 4.0f;                           // Get the width of a single frame
    float deathFrameHeight = deathSprite.height / 4.0f;                         // Get the height of a single frame
    float deathFrameY = 0.0f;                                                   // Multiplier for cycling through frames, set here to enable switching spritesheet later for more animation frames if desired 
    float currentDeathFrame = deathFrameWidth * deathFrameY;                    // Set the current frame
    Rectangle deathSpriteRec;                                                   // Ractangle for drawing the frame
    bool deathAnimationComplete = false;                                        // Used to see if the death animation is complete before carrying out the rest of the death mechanic

    float shipFlameFrame = 0;                                                                   // Used to switch vertically to flicker the flame
    int flameSpeedCounter = 0;                                                                  // Used to calculate the speed of the flame flicker
    float shipSpeed;                                                                            // Used to modify ship speed
    Rectangle hitBox;                                                                           // Hitbox for ship
    Vector2 shipPos = {winWidth / 2.0f - (shipSprite.width / 10), winHeight - (winHeight / 4)}; // Ship position
    Vector2 startPos = {winWidth / 2.0f - (shipSprite.width / 10), winHeight - (winHeight / 4)};// For quick reference on replay
    Vector2 shipVel = {0.0f,0.0f};                                                              // Ship velocity
    bool alive = true;                                                                          // Mark ship as alive
    int lives = 3;                                                                              // Set number of lives
    int invincibleFrames = 60;                                                                  // Invicibility frames so player can't instantly die again is spawn position is currently in contact with a hostile
    int opacity = 255;                                                                          // Used to control transparency of ship, used for the animation on respawn

    void updateShip() {                                                                                     // Primary function called to update the ship and control it
    if (alive || invincibleFrames < 60)                                                                     // Check if ship is alive or if the ship is going through the "invincible frames" animation
    {
        spriteRec = { currentShipFrame, shipFlameFrame, (float)shipFrameWidth, (float)shipFrameHeight };    // Set the ship rectangle within the sprite sheet

        shipSpeed = 7.0f - (gameSpeed * 5.0f);                                                              // Set ship speed based on game speed

        // Checks whether to alternate flame sprite and then resets counter
        flameSpeedCounter++;                                                                                // Increment flame counter
        if (flameSpeedCounter == 5)                                                                         // Check if it's equal to 5. This could have been easily done with "frameCounter % 5 == 0" like other  sections of code but I included it as an alternative just for the sake of interest
            {
                shipFlameFrame == 0 ? shipFlameFrame = shipFrameHeight : shipFlameFrame = 0;                // Flip the frame vertically
                flameSpeedCounter = 0;                                                                      // Reset the counter
            }
        
        
        ////////////////////////////
        // Movement 
        ////////////////////////////

        //Right
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {                                                         //Check if key is being pressed
            //Update Position
            shipPos.x < winWidth - (shipSprite.width / 5) ? shipVel.x = 3.0f * shipSpeed : shipVel.x = 0.0f;    // Check if current position is within the window, add velocity if true or set to 0 if false;
            //Update Frame
            if (shipFrameMod < 4.0f)                                                                            //Check that current frame isn't out of range
            {
                shipFrameMod += 1.0f;                                                                           //Move frame over one
                currentShipFrame = shipFrameWidth * shipFrameMod;                                               //Update current frame
            }
        }
        if(IsKeyReleased(KEY_RIGHT) || IsKeyReleased(KEY_D)) {                                                  //Check if key is released
                shipFrameMod = 2.0f;                                                                            //If so, reset frame to center
                shipVel.x = 0.0f;                                                                               //Set velocity to zero
                currentShipFrame = shipFrameWidth * shipFrameMod;                                               //Update current frame
            }

        //Left
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {                                                          //Check if key is being pressed
            //Update Position
            shipPos.x > 0 ? shipVel.x = -3.0f * shipSpeed : shipVel.x = 0.0f;                                   // Check if current position is within the window, add velocity if true or set to 0 if false;
            //Update Frame
            if (shipFrameMod > 0.0f)                                                                            //Check that current frame isn't out of range
            {
                shipFrameMod -= 1.0f;                                                                           //Move frame over one
                currentShipFrame = shipFrameWidth * shipFrameMod;                                               //Update current frame
            }
        }
        if(IsKeyReleased(KEY_LEFT) || IsKeyReleased(KEY_A)) {                                                   //Check if key is released
                shipFrameMod = 2.0f;                                                                            //If so, reset frame to center
                shipVel.x = 0.0f;                                                                               //Set velocity to zero
                currentShipFrame = shipFrameWidth * shipFrameMod;                                               //Update current frame
            }
    //Up
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {                                                            //Check if key is being pressed
            //Update Position
            shipPos.y > 0 ? shipVel.y = -2.5f * shipSpeed : shipVel.y = 0.0f;                                   // Check if current position is within the window, add velocity if true or set to 0 if false;
        }
        if(IsKeyReleased(KEY_UP) || IsKeyReleased(KEY_W)) {                                                     //Check if key is released
            shipVel.y = 0.0f;                                                                                   //Set velocity to zero
        }

        ////Down
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {                                                          //Check if key is being pressed
            //Update Position
            shipPos.y < winHeight - shipFrameHeight ? shipVel.y = 2.5f * shipSpeed : shipVel.y = 0.0f;          // Check if current position is within the window, add velocity if true or set to 0 if false;
        }
        if(IsKeyReleased(KEY_DOWN) || IsKeyReleased(KEY_S)) {                                                   //Check if key is released
            shipVel.y = 0.0f;                                                                                   //Set velocity to zero
        }

        //Update Position
        shipPos.x += shipVel.x;                                                                                 // Update ship x position  based on x velocity
        shipPos.y += shipVel.y;                                                                                 // Update ship x position  based on y velocity
        }
    }

    void drawShip() {                                                                                               // Function to call to draw the ship
        updateShip();                                                                                               // Call from here to reduce calls within main.cpp
        hitBox = {shipPos.x, shipPos.y, shipFrameWidth, shipFrameHeight};                                           // Set the hitbox as the same as the ship
        if(!alive && !deathAnimationComplete)                                                                       // Check if the ship is not alive and if the death animation hasn't completed
        {   
            playDeathAnimation();                                                                                   // Call the death animation
        }   
        else if (!alive && deathAnimationComplete) {                                                                // Else if not alive but the death animation is complete
            death();                                                                                                // DEATH, THE CESSATION OF A LIFE
            DrawTextureRec(shipSprite, spriteRec, shipPos, CLITERAL(Color){ 255, 255, 255, (unsigned char)opacity});// Draw the sprite based on the rectangle within the sprite sheet
        }
        else if (alive) {                                                                                           // Else if alive
            DrawTextureRec(shipSprite, spriteRec, shipPos, CLITERAL(Color){ 255, 255, 255, (unsigned char)opacity});// Draw the rectangle. Same as before just this time without calling the death animation, this is the rectangle called throughout the game primarily
        }
    }

    Vector2 getShipPos() {                                                                                          // Function for getting the ship position for other elements relevant to it, such as drawing the bullet
        return shipPos;                                                                                             // Returns the ship position to the function caller
    }

    void playDeathAnimation() {                                                                                     // Function for playing the death animation of the ship
        Vector2 adjustedShipPos = { shipPos.x - 10, shipPos.y };                                                    // Adjusts the position of the drawn explosion sprite to appear like it is the same location as the player ship, this was necessary as the explosion sprite is a different size
        DrawTextureRec(deathSprite, deathSpriteRec, adjustedShipPos, WHITE);                                        // Set the sprite rectangle
        deathSpriteRec = { currentDeathFrame, deathFrameY, (float)deathFrameWidth, (float)deathFrameHeight };       // If loops to time the animation
        if (frameCounter % 5 == 0)
            {
                currentDeathFrame += deathFrameWidth;                                                               // Move the shown frame on the sprite sheet horizontally by 1 width of an individual frame
                if (currentDeathFrame > deathFrameWidth * 2.5 && deathFrameY == 0.0f)                               // If the currentFrame is at the far right and still on the first row
                {
                    currentDeathFrame = 0;                                                                          // Reset it to left and then...
                    deathFrameY += deathFrameHeight;                                                                // ...MOVE TO THE NEXT ROW!
                }
                if (currentDeathFrame > deathFrameWidth * 2.5 && deathFrameY > 0.0f) {                              // If the current frame is at the far but but this time is on the second rown
                    deathAnimationComplete = true;                                                                  // Then mark the death animation as complete
                    deathFrameY = 0.0f;                                                                             // Reset the y
                    currentDeathFrame = deathFrameWidth * deathFrameY;                                              // Refet the x
                }
                
            }   
    }

    void death() {                                                      // Function for handling the end of a ship, as in the ship  was destroyed. That ship, as it was, has ceased to be. 
        if (invincibleFrames == 60)                                     // If the invincible frames is at 60, the default amount
        {
            lives--;                                                    // Then decrement the life count
            shipPos = startPos;                                         // Move the ship to the starting position
            opacity = 0;                                                // Make the ship fully transparent
            invincibleFrames--;                                         // Decrement the invincible frame count
        }
        else if (invincibleFrames > 0 && invincibleFrames != 60)        // If invincibleFrames is greater than 0, or else than 60, as in if the animation is underway
        {   
            if (invincibleFrames % 10 == 0 && invincibleFrames > 0)     // if loop to time the animation
            {
                opacity = 128;                                          // Set to half opacity
            }
            else                                                        // otherwise
            {
                opacity = 0;                                            // Set to full transparency. This creates a flashing animation that commonly is used to show invincible frames, this means that the player can't be unfairly hit and killed due to the spawn location
            }
            invincibleFrames--;                                         // Decrement invincibleFrames
        }
        else
        {            
            alive = true;                                               // Essentially if invisible frames == 0
            deathAnimationComplete = false;                             // set death animation complete to false for the next usage, slightly ironically this is set right as the animation is complete but trust me it makes more sense this way. Actually that's subjective.
            invincibleFrames = 60;                                      // Reset invincible frames to the default 60. Probably would have been better to have created a game variable for this rather than magic numbers.
            opacity = 255;                                              // Make ship fully opaque once again
        }
    }

    void UnloadShip() {                                                 // Function for garbage collection
        UnloadTexture(shipSprite);                                      // Unload the shipSprite
        UnloadTexture(deathSprite);                                        // Unload the deathSprite
    }
};