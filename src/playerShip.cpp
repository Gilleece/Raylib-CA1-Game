#include <string>
#include <iostream>
#include "raylib.h"
#include "raymath.h"

//Declaring ship struct
struct {
    Texture2D shipSprite;   //ship sprite sheet
    float shipFrameWidth;   //Get the width of a single frame
    float shipFrameHeight;  //Get the height of a single frame
    float currentShipFrame; //Set the current frame
    float shipFrameMod;     //Multiplier for cycling through frames, set here to enable switching spritesheet later for more animation frames if desired 
    float shipFlameFrame;   //Used to switch vertically to flicker the flame
    int flameSpeedCounter;  //Used to calculate the speed of the flame flicker
    float shipSpeed;        //Used to modify ship speed
    Rectangle spriteRec;    //Ractangle for drawing the frame onto
    Vector2 shipPos;        //Ship position
    Vector2 shipVel;        //Ship velocity
} ship;


//initialize the ship
void initShip() {
    ship.shipSprite = LoadTexture("assets/sprites/ship.png");
    ship.shipFrameWidth = ship.shipSprite.width / 5.0f;                 //Get the width of a single frame
    ship.shipFrameHeight = ship.shipSprite.height / 2.0f;               //Get the height of a single frame
    ship.shipFrameMod = 2.0f;                                           //Set the frame selected;
    ship.currentShipFrame = ship.shipFrameWidth * ship.shipFrameMod;    //Set the current frame
    ship.shipFlameFrame = 0;                                            //Used to switch vertically to flicker the flame
    ship.flameSpeedCounter = 0;                                         //Used to calculate the speed of the flame flicker    
    ship.shipPos = {winWidth / 2.0f - (ship.shipSprite.width / 10), winHeight - (winHeight / 4)}; // Init to mid lower
    ship.shipVel = {0.0f,0.0f};                                         //Init to 0,0
    ship.shipSpeed = 2.0f;                                              //Init to 1
}

void updateShip() {
    ship.spriteRec = { ship.currentShipFrame, ship.shipFlameFrame, (float)ship.shipFrameWidth, (float)ship.shipFrameHeight };

    // Checks whether to alternate flame sprite and then resets counter
    ship.flameSpeedCounter++;
    if (ship.flameSpeedCounter == 5)
        {
            ship.shipFlameFrame == 0 ? ship.shipFlameFrame = ship.shipFrameHeight : ship.shipFlameFrame = 0; // Flip the frame vertically
            ship.flameSpeedCounter = 0;
        }
    
    
    ////////////////////////////
    // Movement 
    ////////////////////////////

    //Right
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {            //Check if key is being pressed
        //Update Position
        ship.shipPos.x < winWidth - (ship.shipSprite.width / 5) ? ship.shipVel.x = 3.0f * ship.shipSpeed : ship.shipVel.x = 0.0f; // Check if current position is within the window, add velocity if true or set to 0 if false;
        //Update Frame
        if (ship.shipFrameMod < 4.0f)                               //Check that current frame isn't out of range
        {
            ship.shipFrameMod += 1.0f;                               //Move frame over one
            ship.currentShipFrame = ship.shipFrameWidth * ship.shipFrameMod;   //Update current frame
        }
    }
    if(IsKeyReleased(KEY_RIGHT) || IsKeyReleased(KEY_D)) {      //Check if key is released
            ship.shipFrameMod = 2.0f;                                //If so, reset frame to center
            ship.shipVel.x = 0.0f;                                   //Set velocity to zero
            ship.currentShipFrame = ship.shipFrameWidth * ship.shipFrameMod;   //Update current frame
        }

    //Left
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {            //Check if key is being pressed
        //Update Position
        ship.shipPos.x > 0 ? ship.shipVel.x = -3.0f * ship.shipSpeed : ship.shipVel.x = 0.0f; // Check if current position is within the window, add velocity if true or set to 0 if false;
        //Update Frame
        if (ship.shipFrameMod > 0.0f)                               //Check that current frame isn't out of range
        {
            ship.shipFrameMod -= 1.0f;                               //Move frame over one
            ship.currentShipFrame = ship.shipFrameWidth * ship.shipFrameMod;   //Update current frame
        }
    }
    if(IsKeyReleased(KEY_LEFT) || IsKeyReleased(KEY_A)) {      //Check if key is released
            ship.shipFrameMod = 2.0f;                                //If so, reset frame to center
            ship.shipVel.x = 0.0f;                                   //Set velocity to zero
            ship.currentShipFrame = ship.shipFrameWidth * ship.shipFrameMod;   //Update current frame
        }
   //Up
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {            //Check if key is being pressed
        //Update Position
        ship.shipPos.y > 0 ? ship.shipVel.y = -2.5f * ship.shipSpeed : ship.shipVel.y = 0.0f; // Check if current position is within the window, add velocity if true or set to 0 if false;
    }
    if(IsKeyReleased(KEY_UP) || IsKeyReleased(KEY_W)) {      //Check if key is released
        ship.shipVel.y = 0.0f;                               //Set velocity to zero
    }

    ////Down
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_A)) {            //Check if key is being pressed
        //Update Position
        ship.shipPos.y < winHeight - ship.shipFrameHeight ? ship.shipVel.y = 2.5f * ship.shipSpeed : ship.shipVel.y = 0.0f; // Check if current position is within the window, add velocity if true or set to 0 if false;
    }
    if(IsKeyReleased(KEY_DOWN) || IsKeyReleased(KEY_A)) {      //Check if key is released
        ship.shipVel.y = 0.0f;                                 //Set velocity to zero
    }

    //Update Position
    ship.shipPos.x += ship.shipVel.x;
    ship.shipPos.y += ship.shipVel.y;

    ////////////////////////////
    // Weapons 
    ////////////////////////////

}

void drawShip() {
    DrawTextureRec(ship.shipSprite, ship.spriteRec, ship.shipPos, WHITE);
}

void UnloadShip() {
    UnloadTexture(ship.shipSprite);
}