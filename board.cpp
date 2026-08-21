#include "board.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

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
    std::string line;
    std::getline(std::cin, line);

    move();
    slidDown = slide();
    climbedUp = climb();
}

void Board::update() {
    return;
}