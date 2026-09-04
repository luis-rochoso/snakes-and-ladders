#include "board.hpp"
#include "interface.hpp"
#include <cstdlib>
#include <ctime>

/**
 * Prepares the game for initialization
 */
void Board::init() {
    // Start the random seed
    srand(time(0));

    // Build the game window
    makeWindow();
}

/**
 * Shows the ending screen and closes the game
 */
void Board::shutdown() {
    // Draws the end screen
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BROWN);
            DrawText("VOCÊ VENCEU!\nAperte [ESC] para\nfechar o jogo.", 150, 250, 50, RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
}

/**
 * Moves the player after a play
 */
void Board::move() {
    // Makes the next move be sliding down a snake if the player is on top of one
    if (willSlide() and IsKeyPressed(KEY_SPACE)) {
        slidDown = slide();
        return;
    }
    // Makes the next move be climbing up a ladder if the player is at the bottom of one
    if (willClimb() and IsKeyPressed(KEY_SPACE)) {
        climbedUp = climb();
        return;
    }


    // Default random movement
    lastDieRoll = (rand() % (6)) + 1;
    
    prevPlayerPosition = playerPosition;
    playerPosition += lastDieRoll;
    if (100 < playerPosition) {playerPosition = 100;} // Going over tile 100 still wins the game

    dieIsRolling = true; // Flag for the dice roll animation to be called
    moved = true; // Flag for the update function to be called
}

/**
 * Slides the player down a snake
 * @return True if the player slid down, False if not
 */
bool Board::slide() {
    int snakeBottom = boardTiles[playerPosition].getSnake();

    if (playerPosition == snakeBottom) {return false;}

    playerPosition = snakeBottom;
    lastDieRoll = -1;
    return true;
}

/**
 * Moves the player up a ladder
 * @return True if the player climbed up, False if not
 */
bool Board::climb() {
    int ladderTop = boardTiles[playerPosition].getLadder();

    if (playerPosition == ladderTop) {return false;}

    playerPosition = ladderTop;
    lastDieRoll = -1;
    return true;
}

/**
 * Renders all the information in the screen
 */
void Board::render() {

    // Static so it will only be loaded once
    static Texture2D snakesLadders = LoadTexture("assets/snakesLaddersIcons.png");

    BeginDrawing();
        drawBoard();
        renderSnakesAndLadders(snakesLadders);

        if (dieIsRolling) {
            dieIsRolling = drawDieRolling();
            drawPlayer(prevPlayerPosition);
            drawMessage(slidDown, climbedUp, prevPlayerPosition);
        }

        else {
            drawDieResult(lastDieRoll);
            drawMessage(slidDown, climbedUp, playerPosition);
            drawPlayer(playerPosition);
        }
        
    EndDrawing();

}

/**
 * Makes a play
 */
void Board::play() {

    if (IsKeyPressed(KEY_SPACE)) {
        move();
    }

}

/**
 * Updates universal variables
 */
void Board::update() {
    
    // Counts the frames since last movement
    ++frameCounter;
    if (IsKeyPressed(KEY_SPACE)) {
        frameCounter = 0;
    }

    if (moved) {
        // Makes sure the sliding/climbing message disappears after 1 move
        slidDown = false;
        climbedUp = false;
        moved = false;
    }

}