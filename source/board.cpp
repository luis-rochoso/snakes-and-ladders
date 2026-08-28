#include "board.hpp"
#include "interface.hpp"
#include <cstdlib>
#include <ctime>

void Board::init() {
    makeWindow();
}

void Board::shutdown() {
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BROWN);
            DrawText("VOCÊ VENCEU!\nAperte [ESC] para\nfechar o jogo.", 150, 250, 50, RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
}

void Board::move() {
    if (willSlide() and IsKeyPressed(KEY_SPACE)) {
        slidDown = slide();
        return;
    }
    if (willClimb() and IsKeyPressed(KEY_SPACE)) {
        climbedUp = climb();
        return;
    }

    lastDieRoll = (rand() % (6)) + 1;

    playerPosition += lastDieRoll;
    if (100 < playerPosition) {playerPosition = 100;}

    moved = true;
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
    slidDown = false; // If the current tile has a snake, slide it down
    climbedUp = false; // If the current tile has a ladder, climb it up
    moved = false;
    return;
}