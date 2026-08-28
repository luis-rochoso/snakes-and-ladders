#include "board.hpp"
#include "interface.hpp"
#include <cstdlib>
#include <ctime>

void Board::init() {
    // Start the random seed
    srand(time(0));

    // Build the game window
    makeWindow();
}

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

    playerPosition += lastDieRoll;
    if (100 < playerPosition) {playerPosition = 100;} // Going over tile 100 still wins the game

    moved = true; // Flag for the update function to be called
}

bool Board::slide() {
    int snakeBottom = boardTiles[playerPosition].getSnake();

    if (playerPosition == snakeBottom) {return false;}

    playerPosition = snakeBottom;
    lastDieRoll = 0;
    return true;
}

bool Board::climb() {
    int ladderTop = boardTiles[playerPosition].getLadder();

    if (playerPosition == ladderTop) {return false;}

    playerPosition = ladderTop;
    lastDieRoll = 0;
    return true;
}

void Board::render() {

    // Static so it will only be loaded once
    static Texture2D snakesLadders = LoadTexture("assets/snakesLaddersIcons.png");

    BeginDrawing();
        drawBoard();
        renderSnakesAndLadders(snakesLadders);
        drawDie(lastDieRoll);
        drawMessage(slidDown, climbedUp, playerPosition);
        drawPlayer(playerPosition);
    EndDrawing();
    
}

void Board::play() {

    if (IsKeyPressed(KEY_SPACE)) {
        move();
    }

}

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