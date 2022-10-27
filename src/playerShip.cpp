#include <string>
#include <iostream>
#include "raylib.h"
#include "raymath.h"

//Declaring ship struct
struct PlayerShip {
    //Ship Sprite
    Texture2D shipSprite = LoadTexture("assets/sprites/ship.png");   //ship sprite sheet
    float shipFrameWidth = shipSprite.width / 5.0f;   //Get the width of a single frame
    float shipFrameHeight = shipSprite.height / 2.0f;  //Get the height of a single frame
    float shipFrameMod = 2.0f;     //Multiplier for cycling through frames, set here to enable switching spritesheet later for more animation frames if desired 
    float currentShipFrame = shipFrameWidth * shipFrameMod; //Set the current frame
    Rectangle spriteRec;    //Ractangle for drawing the frame onto
    //Death Sprite
    Texture2D deathSprite = LoadTexture("assets/sprites/shipExplosion.png");   //ship sprite sheet
    float deathFrameWidth = deathSprite.width / 4.0f;   //Get the width of a single frame
    float deathFrameHeight = deathSprite.height / 4.0f;  //Get the height of a single frame
    float deathFrameY = 0.0f;     //Multiplier for cycling through frames, set here to enable switching spritesheet later for more animation frames if desired 
    float currentDeathFrame = deathFrameWidth * deathFrameY; //Set the current frame
    Rectangle deathSpriteRec;    //Ractangle for drawing the frame onto

    float shipFlameFrame = 0;   //Used to switch vertically to flicker the flame
    int flameSpeedCounter = 0;  //Used to calculate the speed of the flame flicker
    float shipSpeed = 2.0f;        //Used to modify ship speed
    Rectangle hitBox;       // Hitbox for ship
    Vector2 shipPos = {winWidth / 2.0f - (shipSprite.width / 10), winHeight - (winHeight / 4)};        //Ship position
    Vector2 shipVel = {0.0f,0.0f};        //Ship velocity
    bool alive = true;
    int lives = 3;

    void updateShip() {
    if (alive) 
    {
        spriteRec = { currentShipFrame, shipFlameFrame, (float)shipFrameWidth, (float)shipFrameHeight };

        // Checks whether to alternate flame sprite and then resets counter
        flameSpeedCounter++;
        if (flameSpeedCounter == 5)
            {
                shipFlameFrame == 0 ? shipFlameFrame = shipFrameHeight : shipFlameFrame = 0; // Flip the frame vertically
                flameSpeedCounter = 0;
            }
        
        
        ////////////////////////////
        // Movement 
        ////////////////////////////

        //Right
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {            //Check if key is being pressed
            //Update Position
            shipPos.x < winWidth - (shipSprite.width / 5) ? shipVel.x = 3.0f * shipSpeed : shipVel.x = 0.0f; // Check if current position is within the window, add velocity if true or set to 0 if false;
            //Update Frame
            if (shipFrameMod < 4.0f)                               //Check that current frame isn't out of range
            {
                shipFrameMod += 1.0f;                               //Move frame over one
                currentShipFrame = shipFrameWidth * shipFrameMod;   //Update current frame
            }
        }
        if(IsKeyReleased(KEY_RIGHT) || IsKeyReleased(KEY_D)) {      //Check if key is released
                shipFrameMod = 2.0f;                                //If so, reset frame to center
                shipVel.x = 0.0f;                                   //Set velocity to zero
                currentShipFrame = shipFrameWidth * shipFrameMod;   //Update current frame
            }

        //Left
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {            //Check if key is being pressed
            //Update Position
            shipPos.x > 0 ? shipVel.x = -3.0f * shipSpeed : shipVel.x = 0.0f; // Check if current position is within the window, add velocity if true or set to 0 if false;
            //Update Frame
            if (shipFrameMod > 0.0f)                               //Check that current frame isn't out of range
            {
                shipFrameMod -= 1.0f;                               //Move frame over one
                currentShipFrame = shipFrameWidth * shipFrameMod;   //Update current frame
            }
        }
        if(IsKeyReleased(KEY_LEFT) || IsKeyReleased(KEY_A)) {      //Check if key is released
                shipFrameMod = 2.0f;                                //If so, reset frame to center
                shipVel.x = 0.0f;                                   //Set velocity to zero
                currentShipFrame = shipFrameWidth * shipFrameMod;   //Update current frame
            }
    //Up
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {            //Check if key is being pressed
            //Update Position
            shipPos.y > 0 ? shipVel.y = -2.5f * shipSpeed : shipVel.y = 0.0f; // Check if current position is within the window, add velocity if true or set to 0 if false;
        }
        if(IsKeyReleased(KEY_UP) || IsKeyReleased(KEY_W)) {      //Check if key is released
            shipVel.y = 0.0f;                               //Set velocity to zero
        }

        ////Down
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {            //Check if key is being pressed
            //Update Position
            shipPos.y < winHeight - shipFrameHeight ? shipVel.y = 2.5f * shipSpeed : shipVel.y = 0.0f; // Check if current position is within the window, add velocity if true or set to 0 if false;
        }
        if(IsKeyReleased(KEY_DOWN) || IsKeyReleased(KEY_S)) {      //Check if key is released
            shipVel.y = 0.0f;                                 //Set velocity to zero
        }

        //Update Position
        shipPos.x += shipVel.x;
        shipPos.y += shipVel.y;
        }
        if (!alive) {
            lives--;
            shipSprite = LoadTexture("assets/sprites/shipExplosion.png");      
            spriteRec = { currentDeathFrame, deathFrameY, (float)deathFrameWidth, (float)deathFrameHeight };
            if (frameCounter % 5 == 0)
            {
                currentDeathFrame += deathFrameWidth;
                if (currentDeathFrame > deathFrameWidth * 2.5)
                {
                    currentDeathFrame = 0;
                    deathFrameY += deathFrameHeight;
                }
                
            }
            if (deathFrameY > deathFrameHeight * 2.5 && lives > 0) 
            {
                alive = true;
            }
            if (lives == 0)
            {
                std::cout << "GAME OVER" << std::endl;
            }
            

        }
    }

    void drawShip() {
        updateShip();// Call from here to reduce calls within main.cpp
        hitBox = {shipPos.x, shipPos.y, shipFrameWidth, shipFrameHeight};
        if(alive)
        {
            DrawTextureRec(shipSprite, spriteRec, shipPos, WHITE);
        } else {
            DrawTextureRec(deathSprite, spriteRec, shipPos, WHITE);
        }
    }

    Vector2 getShipPos() {
        return shipPos;
    }

    void death() {        
        alive = false;
    }

    void UnloadShip() {
        UnloadTexture(shipSprite);
    }
};