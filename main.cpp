#include "raylib.h"
#include <cmath>

int player_score = 0;
int cpu_score = 0;

Color Green = {38, 185, 154, 255};
Color Dark_Green = {20, 160, 133, 255};
Color Light_Green = {129, 204, 184, 255};
Color Yellow = {243, 213, 91, 255};

class Ball {
public:
  float x, y;
  int speed_x, speed_y;
  int radius;
  void Draw() { DrawCircle(x, y, radius, Yellow); }

  void Update() {
    x += speed_x;
    y += speed_y;

    if (y + radius >= GetScreenHeight() || y - radius <= 0) {
      speed_y *= -1;
    }
    if (x + radius >= GetScreenWidth()) // cpu wins
    {
      cpu_score++;
      ResetBall();
    }
    if (x - radius <= 0) {
      player_score++;
      ResetBall();
    }
  }

  void ResetBall() {
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() / 2;

    int speed_choices[2] = {1, -1};
    speed_x = speed_choices[GetRandomValue(0, 1)] * std::abs(speed_x);
    speed_y = speed_choices[GetRandomValue(0, 1)] * std::abs(speed_y);
  }
};

class Paddle {

protected:
  void LimitMovement() {
    if (y + height >= GetScreenHeight()) {
      y = GetScreenHeight() - height;
    }
    if (y <= 0) {
      y = 0;
    }
  };

public:
  float x, y;
  float width, height;
  int speed;

  void Draw() {
    DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
  }

  void Update() {
    if (IsKeyDown(KEY_W)) {
      y -= speed;
    }
    if (IsKeyDown(KEY_S)) {
      y += speed;
    }
    if (y + height >= GetScreenHeight()) {
      y = GetScreenHeight() - height;
    }
    if (y <= 0) {
      y = 0;
    }
  }
}; // Added the missing semicolon here

class CpuPaddle : public Paddle {
public:
  void Update(int ball_y) {
    if (y + height / 2 > ball_y) {
      y = y - speed;
    }
    if (y + height / 2 <= ball_y) {
      y = y + speed;
    }

    LimitMovement();
  }
};

Ball ball;
Paddle player;
CpuPaddle cpu;

int main() {
  const int screenWidth = 500;
  const int screenHeight = 500;
  InitWindow(screenWidth, screenHeight, "My pong game!");
  SetTargetFPS(60);

  ball.radius = 20;
  ball.x = screenWidth / 2;
  ball.y = screenHeight / 2;
  ball.speed_x = 7;
  ball.speed_y = 7;

  player.width = 25;
  player.height = 100;
  player.x = screenWidth - player.width - 10;
  player.y = screenHeight / 2 - player.height / 2;
  player.speed = 6;

  cpu.height = 100;
  cpu.width = 25;
  cpu.x = 10;
  cpu.y = screenHeight / 2 - cpu.height / 2;
  cpu.speed = 6;

  while (!WindowShouldClose()) {
    BeginDrawing();

    ball.Update();
    player.Update();
    cpu.Update(ball.y);

    if (CheckCollisionCircleRec(
            Vector2{ball.x, ball.y}, ball.radius,
            Rectangle{player.x, player.y, player.width, player.height})) {
      ball.speed_x *= -1;
    }

    if (CheckCollisionCircleRec(
            Vector2{ball.x, ball.y}, ball.radius,
            Rectangle{cpu.x, cpu.y, cpu.width, cpu.height})) {
      ball.speed_x *= -1;
    }

    ClearBackground(Dark_Green);
    DrawRectangle(screenWidth / 2, 0, screenHeight / 2, screenHeight, Green);

    DrawCircle(screenWidth / 2, screenHeight / 2, 150, Light_Green);

    // Draw game elements here
    DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
    ball.Draw();
    cpu.Draw();
    player.Draw();
    DrawText(TextFormat("%i", cpu_score), screenWidth / 4 - 20, 20, 80, WHITE);
    DrawText(TextFormat("%i", player_score), 3 * screenWidth / 4 - 20, 20, 80,
             WHITE);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
