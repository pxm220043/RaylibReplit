#include "raylib.h"
#include <iostream>

int main() {
  // Initialize raylib
  InitWindow(800, 600, "Raylib Example");

  // Main game loop
  while (!WindowShouldClose()) {
    // Update and draw here

    BeginDrawing();
    ClearBackground(RED); // Change background color to green
    DrawText("Hello, Raylib!!!!", 10, 10, 20, DARKGRAY);
    EndDrawing();
  }

  // Close raylib
  CloseWindow();

  return 0;
}
//working version vanilla
