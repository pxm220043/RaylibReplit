#include "raylib.h"

int main() {
    // Initialization
    const int screenWidth = 500;
    const int screenHeight = 499;

    InitWindow(screenWidth, screenHeight, "Bouncing Ball Example");

    // Ball variables
    Vector2 ballPosition = { (float)screenWidth / 2, (float)screenHeight / 2 };
    Vector2 ballSpeed = { 5.0f, 5.0f };
    int ballRadius = 20;
    Color ballColor = BLUE;

    // Area variables
    Rectangle playArea = { 50, 50, screenWidth - 100, screenHeight - 100 };
    Color areaColor = RED;

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        ballPosition.x += ballSpeed.x;
        ballPosition.y += ballSpeed.y;

        // Bounce off walls
        if ((ballPosition.x + ballRadius > playArea.x + playArea.width) || (ballPosition.x - ballRadius < playArea.x)) {
            ballSpeed.x *= -1.0f;
        }
        if ((ballPosition.y + ballRadius > playArea.y + playArea.height) || (ballPosition.y - ballRadius < playArea.y)) {
            ballSpeed.y *= -1.0f;
        }

        // Draw
        BeginDrawing();
        ClearBackground(WHITE);

        // Draw play area
        DrawRectangleLinesEx(playArea, 2, areaColor);

        // Draw ball
          DrawCircleV(ballPosition, ballRadius, ballColor);


        // Draw text
        DrawText("This is a bouncing ball", screenWidth / 2 - MeasureText("This is a bouncing ball", 20) / 2, 10, 20, DARKGRAY);

        EndDrawing();

      
        
    }

    // Cleanup
    CloseWindow();

    return 0;
}
