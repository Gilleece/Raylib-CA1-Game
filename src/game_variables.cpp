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
int scoreTextWidth;


void drawUI() {
    DrawText(scoreText, 10, 10, 30, RED);
    scoreTextWidth = MeasureText(scoreText, 30);
    DrawText(TextFormat("%05i", playerScore), scoreTextWidth + 5, 10, 30, RED);

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
    if (frameCounter % 600 == 0 && gameSpeed > 0.1f) {gameSpeed -= 0.1f; std::cout << gameSpeed << std::endl;} // Speeds up date every 10 seconds, until max speed
    if (*lives == 0) {gameOver = true;}                                                                        // Set Game over state to true on 0 lives
    if (gameOver) {                                                                                            // Applies the text to be displayed
        gameOverText = "Game Over!";
        replayText = "Press Enter to Play Again.";
    }
    if (replayText && IsKeyPressed(KEY_ENTER))                                                                 // If player presses enter, while replaytext is displayed, then reset game state and restart game
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