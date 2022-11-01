////////////////////////////
// General Game Loop
////////////////////////////

// Window size
const int winHeight = 900;
const int winWidth = 700;

// Game speed
float gameSpeed = 0.1f;

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


drawUI() {
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


checkGameState(int *lives, Vector2 *shipPos, Vector2 *shipVel, Vector2 startPos) {
    if (*lives == 0) {gameOver = true;}
    if (gameOver) {
        gameOverText = "Game Over!";
        replayText = "Press Enter to Play Again.";
    }
    if (replayText && IsKeyPressed(KEY_ENTER))
    {
        gameOverText = nullptr;
        replayText = nullptr;
        playerScore = 0;
        frameCounter = 0;
        *lives = 3;
        *shipPos = startPos;
        *shipVel = {0.0f, 0.0f};
        gameOver = false;
    }
    
}