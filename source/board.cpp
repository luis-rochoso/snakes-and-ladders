#include "board.hpp"
#include "interface.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iostream>
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
    lastDieRoll = (rand() % (6)) + 1;

    playerPosition += lastDieRoll;
    if (100 < playerPosition) {playerPosition = 100;}
}

bool Board::slide() {
    int snakeBottom = boardTiles[playerPosition].getSnake();

    if (playerPosition == snakeBottom) {return false;}

    playerPosition = snakeBottom;
    return true;
}

bool Board::climb() {
    int ladderTop = boardTiles[playerPosition].getLadder();

    if (playerPosition == ladderTop) {return false;}

    playerPosition = ladderTop;
    return true;
}

void Board::render() {

    BeginDrawing();
        drawBoard();
        drawDie(lastDieRoll);
        drawMessage(slidDown, climbedUp, playerPosition);
        drawPlayer(playerPosition);
    EndDrawing();

    if (lastDieRoll != 0) {
        std::cout << "\nROLAGEM DO DADO = [" << lastDieRoll << "]\n";
    }
    if (slidDown) {
        std::cout << "Você escorregou para baixo." << std::endl;
    }
    if (climbedUp) {
        std::cout << "Você subiu a escada." << std::endl;
    }
    std::cout << "Você está agora no espaço " << playerPosition << std::endl
              << "Aperte [ENTER] para jogar.";
}

void Board::play() {

    if (IsKeyPressed(KEY_SPACE)) {
        move();
        moved = true;
    }

}

void Board::update() {
    slidDown = slide(); // If the current tile has a snake, slide it down
    climbedUp = climb(); // If the current tile has a ladder, climb it up
    moved = false;
    return;
}