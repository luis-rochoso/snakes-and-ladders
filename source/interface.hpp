#include "raylib.h"

const int screenWidth {800};
const int screenHeight {600};
static int textAnimationSpeed = 8;
static int frameCounter {0};

void makeWindow() {
    InitWindow(screenWidth, screenHeight, "Snakes & Ladders");
    SetTargetFPS(30);
}

void drawBoard() {
    ClearBackground(BROWN); // Black sidescreen
    DrawRectangle(0, 0, 600, 600, RAYWHITE); // White border
    DrawRectangle(5, 5, 590, 590, DARKBLUE); // Blue squares

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
}

void renderSnakesAndLadders(Texture2D &snakesLadders) {
    DrawTexture(snakesLadders, 0, 0, WHITE);
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
    // Player is not on the board yet, draw icon on the sidebar
    if (position == 0) {
        DrawTriangle({690 - 4, 491 - 2}, {700, 516 + 4}, {710 + 4, 491 - 2}, GREEN);
        DrawTriangleLines({690 - 4, 491 - 2}, {700, 516 + 4}, {710 + 4, 491 - 2}, BLACK);
        return;
    }

    // Draws the player marker on top of its intended tile
    Vector2 playerVector = positionToVector(position);
    float x = playerVector.x;
    float y = playerVector.y;

    DrawTriangle({x - 14, y - 17}, {x, y + 14}, {x + 14, y - 17}, GREEN); // Player
    DrawTriangleLines({x - 14, y - 17}, {x, y + 14}, {x + 14, y - 17}, BLACK); // Player Outline
}

void drawDie(int roll) {
    Rectangle textbox;
    
    // Before the first play
    if (roll < 1) {
        // Draw the textbox
        textbox = {605, 150, 180, 120};
        DrawRectangleRounded(textbox, 0.25, 1, LIGHTGRAY);
        DrawRectangleRoundedLinesEx(textbox, 0.25, 1, 2.0, WHITE);

        // Draw the text
        const char* playMessage = "   Aperte\n [ESPAÇO]\npara jogar.";

        if (roll == 0) { // It is animated in the first turn
            DrawText(TextSubtext(playMessage, 0, (frameCounter * textAnimationSpeed) / 10),
                                 610, 160, 30, BLACK);
        }

        else { // After sliding or climbing, it is drawn all at once
            DrawText(playMessage, 610, 160, 30, BLACK);
        }
        
        return;
    }

    textbox = {630, 155, 145, 30};
    DrawRectangleRounded(textbox, 0.25, 1, LIGHTGRAY);
    DrawRectangleRoundedLinesEx(textbox, 0.25, 1, 2.0, WHITE);
    
    DrawText("Última jogada: ", 635, 160, 20, BLACK);

    Rectangle die = {640, 200, 120, 120};
    DrawRectangleRounded(die, 0.25, 1, RAYWHITE);

    Vector2 dieCenter = {700, 260};

    switch (roll)
    {
    case 1:
        DrawCircle(dieCenter.x, dieCenter.y, 20, RED);
        break;
    
    case 2:
        DrawCircle(dieCenter.x - 30, dieCenter.y, 10, BLUE); // Left Circle
        DrawCircle(dieCenter.x + 30, dieCenter.y, 10, BLUE); // Right Circle 
        break;

    case 3:
        DrawCircle(dieCenter.x, dieCenter.y, 10, RED);
        DrawCircle(dieCenter.x + 30, dieCenter.y - 30, 10, RED);
        DrawCircle(dieCenter.x - 30, dieCenter.y + 30, 10, RED);
        break;
    
    case 4:
        // Upper Balls
        DrawCircle(dieCenter.x - 30, dieCenter.y - 30, 10, BLUE);
        DrawCircle(dieCenter.x + 30, dieCenter.y - 30, 10, BLUE);

        // Lower Balls
        DrawCircle(dieCenter.x - 30, dieCenter.y + 30, 10, BLUE);
        DrawCircle(dieCenter.x + 30, dieCenter.y + 30, 10, BLUE);
        break;
    
    case 5:
        // Upper balls
        DrawCircle(dieCenter.x - 30, dieCenter.y - 30, 10, RED);
        DrawCircle(dieCenter.x + 30, dieCenter.y - 30, 10, RED);

        // Middle Ball
        DrawCircle(dieCenter.x, dieCenter.y, 10, RED);

        // Lower Balls
        DrawCircle(dieCenter.x - 30, dieCenter.y + 30, 10, RED);
        DrawCircle(dieCenter.x + 30, dieCenter.y + 30, 10, RED);
        break;
    
    case 6:
        // Upper balls
        DrawCircle(dieCenter.x - 30, dieCenter.y - 30, 10, BLUE);
        DrawCircle(dieCenter.x + 30, dieCenter.y - 30, 10, BLUE);

        // Middle Balls
        DrawCircle(dieCenter.x - 30, dieCenter.y, 10, BLUE);
        DrawCircle(dieCenter.x + 30, dieCenter.y, 10, BLUE);

        // Lower balls
        DrawCircle(dieCenter.x - 30, dieCenter.y + 30, 10, BLUE);
        DrawCircle(dieCenter.x + 30, dieCenter.y + 30, 10, BLUE);
        break;

    default:
        break;
    }
}

void drawMessage (bool &slidDown, bool &climbedUp, int playerPosition) {
    Rectangle textbox = {605, 330, 190, 60};

    if (slidDown) {
        // Draw the textbox
        DrawRectangleRounded(textbox, 0.25, 1, LIGHTGRAY);
        DrawRectangleRoundedLinesEx(textbox, 0.25, 1, 2.0, WHITE);

        // Draw the text animation
        const char* slideMessage = "Você escorregou\n     para baixo.";
        DrawText(TextSubtext(slideMessage, 0, (frameCounter * textAnimationSpeed) / 10),
                             610, 340, 20, BLACK);
    }
    else if (climbedUp) {
        // Draw the textbox
        DrawRectangleRounded(textbox, 0.25, 1, LIGHTGRAY);
        DrawRectangleRoundedLinesEx(textbox, 0.25, 1, 2.0, WHITE);

        // Draw the text animation
        const char * climbMessage = "Você subiu a\n    escada.";
        DrawText(TextSubtext(climbMessage, 0, (frameCounter * textAnimationSpeed) / 10),
                             635, 340, 20, BLACK);
    }
    
    textbox = {630, 400, 140, 150};

    DrawRectangleRounded(textbox, 0.25, 1, LIGHTGRAY);
    DrawRectangleRoundedLinesEx(textbox, 0.25, 1, 4.0, WHITE);
    DrawText(TextFormat("Você está\nagora no\nespaço %i.", playerPosition), 650, 420, 20, BLACK);
}