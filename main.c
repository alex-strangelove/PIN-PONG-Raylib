#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct Ball
{
  Vector2 position;
  Vector2 speed;
  float radius;
} Ball;

Vector2 GetRandomBallSpeed(int minSpeed, int maxSpeed)
{
  Vector2 speed = {
      GetRandomValue(minSpeed, maxSpeed) * (GetRandomValue(0, 1) ? 1 : -1),
      GetRandomValue(minSpeed, maxSpeed) * (GetRandomValue(0, 1) ? 1 : -1)};
  return speed;
}

void ResetBall(Ball *ball, int screenWidth, int screenHeight)
{
  ball->position = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
  ball->speed = GetRandomBallSpeed(200, 400);
}

int main(void)
{
  const char *title = "Ping pong";
  const char *footer = "Created by two geniuses";
  const int screenWidth = 640;
  const int screenHeight = 480;

  // Ball properties
  Ball ball = {.position = {screenWidth / 2.0f, screenHeight / 2.0f},
               .speed = GetRandomBallSpeed(200, 400),
               .radius = 15.0f};

  // Paddles properties
  int paddleWidth = 20;
  int paddleHeight = 100;
  int leftPaddleX = 100;
  int rightPaddleX = screenWidth - 120;

  // Scores
  int scoreLeft = 0;
  int scoreRight = 0;

  int font_size = (screenWidth / screenHeight) * 50;
  InitWindow(screenWidth, screenHeight, "Pong Online");
  SetMouseCursor(MOUSE_CURSOR_ARROW);
  SetTargetFPS(60); // Set our game to run at 60 frames-per-second

  // Calculate the top-left corner coordinates of the rectangle
  int rectWidth = screenWidth / 2 + 200;
  int rectHeight = screenHeight / 2 + 40;
  int rectX = (screenWidth - rectWidth) / 2;
  int rectY = (screenHeight - rectHeight) / 2;

  int countdown = 3;
  float countdownTimer = 0.0f;
  bool gamePaused = true;

  while (!WindowShouldClose())
  {
    // Limit the player's rectangle Y position to stay within the larger rectangle
    Vector2 mouse_pos = GetMousePosition();
    int leftPaddleY = mouse_pos.y - paddleHeight / 2;
    int rightPaddleY = mouse_pos.y - paddleHeight / 2;

    if (leftPaddleY < rectY)
      leftPaddleY = rectY;
    if (leftPaddleY + paddleHeight > rectY + rectHeight)
      leftPaddleY = rectY + rectHeight - paddleHeight;

    if (rightPaddleY < rectY)
      rightPaddleY = rectY;
    if (rightPaddleY + paddleHeight > rectY + rectHeight)
      rightPaddleY = rectY + rectHeight - paddleHeight;

    // Concole output
    // printf("x: %f y: %f\n", mouse_pos.x, mouse_pos.y);

    if (gamePaused)
    {
      countdownTimer += GetFrameTime();
      if (countdownTimer >= 1.0f)
      {
        countdownTimer = 0.0f;
        countdown--;
        if (countdown <= 0)
        {
          gamePaused = false;
        }
      }
    }
    else
    {
      // Ball movement
      ball.position.x += ball.speed.x * GetFrameTime();
      ball.position.y += ball.speed.y * GetFrameTime();

      // Ball collision with top and bottom screen boundaries
      if (ball.position.y <= ball.radius || ball.position.y >= screenHeight - ball.radius)
      {
        ball.speed.y *= -1;
      }

      // Ball collision with paddles
      if (ball.position.x - ball.radius <= leftPaddleX + paddleWidth &&
          ball.position.y >= leftPaddleY &&
          ball.position.y <= leftPaddleY + paddleHeight)
      {
        ball.speed.x *= -1;
        ball.speed.y += (ball.position.y - (leftPaddleY + paddleHeight / 2)) * 2;
      }

      if (ball.position.x + ball.radius >= rightPaddleX &&
          ball.position.y >= rightPaddleY &&
          ball.position.y <= rightPaddleY + paddleHeight)
      {
        ball.speed.x *= -1;
        ball.speed.y += (ball.position.y - (rightPaddleY + paddleHeight / 2)) * 2;
      }

      // Ball collision with center rectangle boundaries
      if (ball.position.x - ball.radius < rectX || ball.position.x + ball.radius > rectX + rectWidth)
      {
        ball.speed.x *= -1;
      }
      if (ball.position.y - ball.radius < rectY || ball.position.y + ball.radius > rectY + rectHeight)
      {
        ball.speed.y *= -1;
      }

      // Victory!
      if (ball.position.x + ball.radius > rightPaddleX + paddleWidth)
      {
        scoreLeft++;
        gamePaused = true;
        countdown = 3;
        ResetBall(&ball, screenWidth, screenHeight);
      }
      else if (ball.position.x - ball.radius < leftPaddleX)
      {
        scoreRight++;
        gamePaused = true;
        countdown = 3;
        ResetBall(&ball, screenWidth, screenHeight);
      }
    }

    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    // Playing field
    DrawRectangleLines(rectX, rectY, rectWidth, rectHeight, BLACK);
    DrawFPS(10, 10);

    DrawText(title, (screenWidth - (strlen(title) * (font_size / 2))) / 2,
             font_size / 2, font_size, WHITE);

    DrawText(footer, (screenWidth - MeasureText(footer, 14)) / 2,
             screenHeight - 35, 14, BLACK);

    // Draw ball
    DrawCircleV(ball.position, ball.radius, BLACK);

    // Draw players
    if ((int)mouse_pos.x <= screenWidth / 2)
    {
      // printf("Player 1 active: ");
      DrawRectangle(100, leftPaddleY, 20, 100, Fade(GREEN, 0.9f));
      DrawRectangle(screenWidth - 120, (screenHeight - 100) / 2, 20, 100, Fade(RED, 0.9f));
    }
    else
    {
      // printf("Player 2 active: ");
      DrawRectangle(rightPaddleX, rightPaddleY, paddleWidth, paddleHeight, Fade(RED, 0.9f));
      DrawRectangle(leftPaddleX, (screenHeight - 100) / 2, paddleWidth, paddleHeight, Fade(GREEN, 0.9f));
    }

    // Draw scores
    DrawText(TextFormat("Left: %i", scoreLeft), 70, 70, 20, BLACK);
    DrawText(TextFormat("Right: %i", scoreRight), screenWidth - 140, 70, 20, BLACK);

    // Draw countdown
    if (gamePaused && countdown > 0)
    {
      const char *countdownText = TextFormat("%i", countdown);
      int textWidth = MeasureText(countdownText, 60);
      DrawRectangle((screenWidth / 2) - (textWidth / 2) - 10, screenHeight / 2 - (60 / 2) - 10, textWidth + 20, 60 + 20, LIGHTGRAY);
      DrawText(countdownText, (screenWidth / 2) - (textWidth / 2), screenHeight / 2 - (60 / 2), 60, BLACK);
    }

    EndDrawing();
  }
  return 0;
}
