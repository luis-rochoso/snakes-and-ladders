#include "raylib.h"

void makeWindow() {
    InitWindow(800, 600, "Snakes & Ladders");
    SetTargetFPS(30);
}

void drawBoard() {
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

        // DrawText(TextFormat("%i", tileNumber), 48, 54, 8, BLACK);
    EndDrawing();
}