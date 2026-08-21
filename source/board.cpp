#include "board.hpp"
#include "raylib.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

void Board::init() {
    InitWindow(800, 600, "Snakes & Ladders");
    SetTargetFPS(30);
}

void Board::shutdown() {
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
        ClearBackground(BLACK); // Black sidescreen
        DrawRectangle(0, 0, 600, 600, RAYWHITE); // White border
        DrawRectangle(5, 5, 590, 590, RED); // Red squares

        // Yellow squares (making a checkerboard pattern)
        for(int x = 5; x < 590; x += 59) {
            for(int y = 5; y < 590; y+= 59) {
                if (x % 2 == 0) {
                    if (y % 2 == 0) {
                        DrawRectangle(x, y, 59, 59, BEIGE);    
                    }
                }
                else {
                    if (y % 2 == 1) {
                        DrawRectangle(x, y, 59, 59, BEIGE);    
                    }
                }              
            }
        }
    EndDrawing();
    // if (lastDieRoll != 0) {
    //     std::cout << "\nROLAGEM DO DADO = [" << lastDieRoll << "]\n";
    // }
    // if (slidDown) {
    //     std::cout << "Você escorregou para baixo." << std::endl;
    // }
    // if (climbedUp) {
    //     std::cout << "Você subiu a escada." << std::endl;
    // }
    // std::cout << "Você está agora no espaço " << playerPosition << std::endl
    //           << "Aperte [ENTER] para jogar.";
}

void Board::play() {
    std::string line;
    std::getline(std::cin, line);

    move();
    slidDown = slide();
    climbedUp = climb();
}

void Board::update() {
    return;
}