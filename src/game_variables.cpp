////////////////////////////
// General Game Loop
////////////////////////////

// Window size
const int winHeight = 900;
const int winWidth = 700;

// Game speed
float gameSpeed = 1.0f;

// Game progress
int frameCounter = 0; // For tracking progress of the level, when to spawn enemies etc

// Tracking variables
int playerScore = 0;
bool gameOver = false;


////////////////////////////
// UI
////////////////////////////


// Text
const char* gameOverText = nullptr;
const char* replayText = nullptr;
const char* scoreText = "SCORE: ";

// Elements
Texture2D lifeSprite;
Rectangle lifeRec;

void initUI() {
    lifeSprite = LoadTexture("assets/sprites/shipLife.png");
    lifeRec = {0, 0, (float)lifeSprite.width, (float)lifeSprite.height};
}


void drawUI(Font mainFont, int lives) {
    //Draw Score
    DrawTextEx(mainFont, scoreText, (Vector2) {10.0f, 10.0f }, (float)mainFont.baseSize, 0, RED);
    DrawTextEx(mainFont, TextFormat("%05i", playerScore), (Vector2) {160.0f, 10.0f }, (float)mainFont.baseSize, 0, RED); // The 05 in %05i is to format the score to 5 zeroes, purely for aesthetic purporses

    //Draw Lives
    if (lives > 0) { DrawTextureRec(lifeSprite, lifeRec, (Vector2){winWidth - (float)lifeSprite.width - 10, 2}, WHITE);};
    if (lives > 1) { DrawTextureRec(lifeSprite, lifeRec, (Vector2){winWidth - ((float)lifeSprite.width*2) - 15, 2}, WHITE);};
    if (lives > 2) { DrawTextureRec(lifeSprite, lifeRec, (Vector2){winWidth - ((float)lifeSprite.width*3) - 20, 2}, WHITE);};
    
    


    if (gameOver) {
        int textWidth = MeasureText(gameOverText, 60);
        int replayTextWidth = MeasureText(replayText, 30);
        DrawText(gameOverText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, GOLD);
        DrawText(replayText, GetScreenWidth() / 2 - replayTextWidth / 2, GetScreenHeight() / 2 + 60, 30, RED);
    }    
}


////////////////////////////
// Game state
////////////////////////////


void checkGameState(int *lives, Vector2 *shipPos, Vector2 *shipVel, Vector2 startPos) {
    if (frameCounter % 600 == 0 && gameSpeed > 0.1f) {gameSpeed -= 0.1f;} // Speeds up date every 10 seconds, until max speed
    if (*lives == 0) {gameOver = true;}                                                                        // Set Game over state to true on 0 lives
    if (gameOver) {                                                                                            // Applies the text to be displayed
        gameOverText = "Game Over!";
        replayText = "Press Enter to Play Again.";
    }
    if (replayText && IsKeyPressed(KEY_ENTER))                                                                 // If player presses enter, while replaytext is displayed, then reset game state and restart game
    {
        gameOverText = nullptr;
        replayText = nullptr;
        gameSpeed = 1.0f;
        playerScore = 0;
        frameCounter = 0;
        *lives = 3;
        *shipPos = startPos;
        *shipVel = {0.0f, 0.0f};
        gameOver = false;
    }
    
}