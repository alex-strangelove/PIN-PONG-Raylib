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
  ball->speed = GetRandomBallSpeed(200, 300);
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

  // Pause counter
  int countdown = 3;
  float countdownTimer = 0.0f;
  bool gamePaused = true;

  // Players' positions
  short first_player_y = (screenHeight - 100) / 2;
  short seccond_player_y = (screenHeight - 100) / 2;

  while (!WindowShouldClose())
  {
    // Limit the player's rectangle Y position to stay within the larger rectangle
    if (first_player_y < rectY)
      first_player_y = rectY;
    if (first_player_y + paddleHeight > rectY + rectHeight)
      first_player_y = rectY + rectHeight - paddleHeight;

    if (seccond_player_y < rectY)
      seccond_player_y = rectY;
    if (seccond_player_y + paddleHeight > rectY + rectHeight)
      seccond_player_y = rectY + rectHeight - paddleHeight;

    Vector2 mouse_pos = GetMousePosition();
    bool mouse_on_the_frame = CheckCollisionPointRec(mouse_pos, (Rectangle){5, 5, 630, 455});
    if (mouse_on_the_frame)
    {
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
            ball.position.y >= first_player_y &&
            ball.position.y <= first_player_y + paddleHeight)
        {
          ball.speed.x *= -1;
          ball.speed.y += (ball.position.y - (first_player_y + paddleHeight / 2)) * 2;
        }

        if (ball.position.x + ball.radius >= rightPaddleX &&
            ball.position.y >= seccond_player_y &&
            ball.position.y <= seccond_player_y + paddleHeight)
        {
          ball.speed.x *= -1;
          ball.speed.y += (ball.position.y - (seccond_player_y + paddleHeight / 2)) * 2;
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
    }
    else
    {
      gamePaused = true;
      countdown = 3;
    }

    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    // Playing field
    DrawRectangleLines(rectX, rectY, rectWidth, rectHeight, BLACK);
    DrawFPS(10, 10);

    DrawText(title, (screenWidth - (strlen(title) * (font_size / 2))) / 2,
             (font_size / 2), font_size, WHITE);

    DrawText(footer, (screenWidth - MeasureText(footer, 14)) / 2,
             screenHeight - 35, 14, BLACK);

    // Draw ball
    DrawCircleV(ball.position, ball.radius, BLACK);

    // Draw players
    if (mouse_on_the_frame)
    {
      DrawRectangle(100, first_player_y, 20, 100, Fade(GREEN, 0.9f));
      // DrawRectangle(screenWidth - 120, (screenHeight - 100) / 2, 20, 100, Fade(RED, 0.9f));

      DrawRectangle(rightPaddleX, seccond_player_y, paddleWidth, paddleHeight, Fade(RED, 0.9f));
      // DrawRectangle(leftPaddleX, (screenHeight - 100) / 2, paddleWidth, paddleHeight, Fade(GREEN, 0.9f));
    }

    // Draw scores
    DrawText(TextFormat("Left: %d", scoreLeft), 70, 70, 20, BLACK);
    DrawText(TextFormat("Right: %d", scoreRight), screenWidth - 140, 70, 20, BLACK);

    // Draw countdown
    if (gamePaused && countdown > 0)
    {
      const char *countdownText = TextFormat("%d", countdown);
      int textWidth = MeasureText(countdownText, 60);
      DrawRectangle((screenWidth / 2) - (textWidth / 2) - 10, screenHeight / 2 - (60 / 2) - 10, textWidth + 20, 60 + 20, LIGHTGRAY);
      DrawText(countdownText, (screenWidth / 2) - (textWidth / 2), screenHeight / 2 - (60 / 2), 60, BLACK);
    }

    // Draw pause
    if (!mouse_on_the_frame)
    {
      int textWidth = MeasureText("Pause", 60);
      DrawRectangle((screenWidth / 2) - (textWidth / 2) - 10, screenHeight / 2 - (60 / 2) - 10, textWidth + 20, 60 + 20, LIGHTGRAY);
      DrawRectangleLines((screenWidth / 2) - (textWidth / 2) - 10, screenHeight / 2 - (60 / 2) - 10, textWidth + 20, 60 + 20, BLACK);
      DrawText("Pause", (screenWidth / 2) - (textWidth / 2), screenHeight / 2 - (60 / 2), 60, BLACK);
    }

    // Draw key pressed
    short pressed_key = GetKeyPressed();
    char key_string[2];
    if (pressed_key)
    {
      key_string[0] = pressed_key > 255 ? key_string[0] : (char)pressed_key;
    }
    if (key_string[0] != '\0')
    {
      DrawText(key_string, 27, screenHeight - 196, 14, BLUE);
      DrawRectangleLines(20, screenHeight - 200, 22, 22, BLACK);
    }

    // Player`s movement
    if (IsKeyDown((char)'W'))
    {
      first_player_y -= 7;
    }
    else if (IsKeyDown((char)'S'))
    {
      first_player_y += 7;
    }

    static const char *up_down = NULL;
    if (IsKeyDown(264))
    {
      seccond_player_y += 7;
      up_down = "Down";
    }
    else if (IsKeyDown(265))
    {
      seccond_player_y -= 7;
      up_down = "Up";
    }

    if (up_down != NULL)
    {
      DrawText(up_down, screenWidth - 40, screenHeight - 196, 14, BLUE);
      DrawRectangleLines(screenWidth - 45, screenHeight - 200, 40, 22, BLACK);
    }
    EndDrawing();
  }
  return 0;
}
