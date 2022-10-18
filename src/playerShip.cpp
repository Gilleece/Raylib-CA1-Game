// Checks whether to alternate flame sprite and then resets counter
void flameFlicker(int *flameSpeedCounter, float *shipFlameFrame, float shipFrameHeight) {
    if (*flameSpeedCounter == 5)
        {
            if (*shipFlameFrame == 0)
            {
                *shipFlameFrame = shipFrameHeight;
            } else {
                *shipFlameFrame = 0;
            }
            *flameSpeedCounter = 0;
        }
}