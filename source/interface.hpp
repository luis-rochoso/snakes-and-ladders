#include "raylib.h"
#include <iostream>

void makeWindow() {
    InitWindow(800, 600, "Snakes & Ladders");
    SetTargetFPS(30);
}

void drawBoard() {
    BeginDrawing();
        ClearBackground(BROWN); // Black sidescreen
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

        // Numbers
        int tileNumber = 100;
        for (int y = 54; y <= 585; y += 59) {
            for (int x = 48; x <= 579; x += 59) {
                if (y % 2 == 0) {
                    DrawText(TextFormat("%i", tileNumber), x, y, 8, BLACK);
                }
                else {
                    DrawText(TextFormat("%i", tileNumber),590 - x, y, 8, BLACK);
                }
                --tileNumber;     
            }
        }
    EndDrawing();
}

Vector2 positionToVector(int position) {
    Vector2 playerVector;

    // If the player's position is in an even row, count from left to right
    if (((position - 1) / 10) % 2 == 0) {
        playerVector.x = 35 + (((position - 1) % 10) * 59);
    }
    // If the player's position is in an odd row, count from right to left
    else {
        playerVector.x = 590 - (25 + (((position - 1) % 10) * 59));
    }

    playerVector.y = 600 - 35 - (((position - 1) / 10) * 59);
    return playerVector;
}

void drawPlayer(int position) {
    // Player is not on the board yet
    if (position == 0) {
        BeginDrawing();
            DrawTriangle({700 - 10, 506 - 15}, {700, 506 + 10}, {700 + 10, 506 - 15}, BLUE);
        EndDrawing();
        return;
    }

    // Draws the player marker on top of its intended tile
    Vector2 playerVector = positionToVector(position);
    float x = playerVector.x;
    float y = playerVector.y;

    BeginDrawing();
        DrawTriangle({x - 10, y - 15}, {x, y + 10}, {x + 10, y - 15}, BLUE);
    EndDrawing();
}