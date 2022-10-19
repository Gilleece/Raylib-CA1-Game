#include <string>
#include <iostream>
#include "raylib.h"
#include "raymath.h"

//Declaring ship variables
Texture2D shipSprite;   //ship sprite sheet
float shipFrameWidth;   //Get the width of a single frame
float shipFrameHeight;  //Get the height of a single frame
float currentShipFrame; //Set the current frame
float shipFlameFrame;   //Used to switch vertically to flicker the flame
int flameSpeedCounter;  //Used to calculate the speed of the flame flicker
Rectangle spriteRec;    //Ractangle for drawing the frame onto
Vector2 shipPos;        //Ship position
Vector2 shipVel;        //Ship velocity

//initialize the variables
void initShip() {
    shipSprite = LoadTexture("assets/sprites/ship.png");
    shipFrameWidth = shipSprite.width / 5.0f;     //Get the width of a single frame
    shipFrameHeight = shipSprite.height / 2.0f;   //Get the height of a single frame
    currentShipFrame = shipFrameWidth * 2.0f;     //Set the current frame
    shipFlameFrame = 0;                           //Used to switch vertically to flicker the flame
    flameSpeedCounter = 0;                        //Used to calculate the speed of the flame flicker
}

void updateShip() {
    spriteRec = { currentShipFrame, shipFlameFrame, (float)shipFrameWidth, (float)shipFrameHeight };
    shipPos = {winWidth / 2.0f - (shipSprite.width / 10), winHeight - (winHeight / 4)};
    shipVel = {0.0f,0.0f};

    // Checks whether to alternate flame sprite and then resets counter
    flameSpeedCounter++;
    if (flameSpeedCounter == 5)
        {
            if (shipFlameFrame == 0)
            {
                shipFlameFrame = shipFrameHeight;
            } else {
                shipFlameFrame = 0;
            }
            flameSpeedCounter = 0;
        }
}

void drawShip() {
    DrawTextureRec(shipSprite, spriteRec, shipPos, WHITE);
}

void UnloadShip() {
    UnloadTexture(shipSprite);
}