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
    Texture2D deathSprite = LoadTexture("assets/sprites/shipExplosion.png");   //ship sprite sheet, not actually used to display the sprite sheet, it is just loaded here to calculate size
    float deathFrameWidth = deathSprite.width / 4.0f;   //Get the width of a single frame
    float deathFrameHeight = deathSprite.height / 4.0f;  //Get the height of a single frame
    float deathFrameY = 0.0f;     //Multiplier for cycling through frames, set here to enable switching spritesheet later for more animation frames if desired 
    float currentDeathFrame = deathFrameWidth * deathFrameY; //Set the current frame
    Rectangle deathSpriteRec;    //Ractangle for drawing the frame onto
    bool deathAnimationComplete = false;

    float shipFlameFrame = 0;   //Used to switch vertically to flicker the flame
    int flameSpeedCounter = 0;  //Used to calculate the speed of the flame flicker
    float shipSpeed = 2.0f;        //Used to modify ship speed
    Rectangle hitBox;       // Hitbox for ship
    Vector2 shipPos = {winWidth / 2.0f - (shipSprite.width / 10), winHeight - (winHeight / 4)};        //Ship position
    Vector2 shipVel = {0.0f,0.0f};        //Ship velocity
    bool alive = true;
    int lives = 3;
    int invincibleFrames = 60; // Invicibility frames so player can't instantly die again is spawn position is currently in contact with a hostile

    void updateShip() {
    if (alive || invincibleFrames < 60) 
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
    }

    void drawShip() {
        updateShip();// Call from here to reduce calls within main.cpp
        hitBox = {shipPos.x, shipPos.y, shipFrameWidth, shipFrameHeight};
        if(!alive && !deathAnimationComplete)
        {
            playDeathAnimation();
        } 
        else if (!alive && deathAnimationComplete) {
            death();
            DrawTextureRec(shipSprite, spriteRec, shipPos, WHITE);
        }
        else if (alive) {
            DrawTextureRec(shipSprite, spriteRec, shipPos, WHITE);
        }
    }

    Vector2 getShipPos() {
        return shipPos;
    }

    void playDeathAnimation() {
        Vector2 adjustedShipPos = { shipPos.x - 10, shipPos.y };  
        DrawTextureRec(deathSprite, deathSpriteRec, adjustedShipPos, WHITE); 
        deathSpriteRec = { currentDeathFrame, deathFrameY, (float)deathFrameWidth, (float)deathFrameHeight };     
        if (frameCounter % 5 == 0)
            {
                currentDeathFrame += deathFrameWidth;
                if (currentDeathFrame > deathFrameWidth * 2.5 && deathFrameY == 0.0f)
                {
                    currentDeathFrame = 0;
                    deathFrameY += deathFrameHeight;
                }
                if (currentDeathFrame > deathFrameWidth * 2.5 && deathFrameY > 0.0f) {
                    deathAnimationComplete = true;
                    deathFrameY = 0.0f;
                    currentDeathFrame = deathFrameWidth * deathFrameY;
                }
                
            }   
    }

    void death() {     
        if (lives == 0)
        {
            std::cout << "GAME OVER" << std::endl;
        }
        else if (invincibleFrames == 60)
        {
            std::cout << "INITIAL" << std::endl;
            shipPos = {winWidth / 2.0f - (shipSprite.width / 10), winHeight - (winHeight / 4)};  
            invincibleFrames--;      
        }
        else if (invincibleFrames > 0 && invincibleFrames != 60)
        {
            std::cout << "GOING DOWN" << std::endl;
            if (invincibleFrames % 10 == 0 && invincibleFrames > 0)
            {
                std::cout << "SHOW" << std::endl;
                shipSprite = LoadTexture("assets/sprites/ship.png");
            }
            else
            {
                std::cout << "HIDE" << std::endl;
                shipSprite = LoadTexture("assets/sprites/shipBlank.png");
            }            
            std::cout << "DECREMENT" << std::endl;
            invincibleFrames--;
        }
        else
        {
            std::cout << "COMPLETE" << std::endl;
            lives--;
            alive = true;  
            deathAnimationComplete = false;
            invincibleFrames = 60;
            shipSprite = LoadTexture("assets/sprites/ship.png");
        }
    }

    void UnloadShip() {
        UnloadTexture(shipSprite);
    }
};