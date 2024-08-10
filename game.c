#include "game.h"
#include "raylib.h"
#include <stdio.h>

Vector2 GetRandomBallSpeed(int minSpeed, int maxSpeed) {
  const Vector2 speed = {
      GetRandomValue(minSpeed, maxSpeed) * (GetRandomValue(0, 1) ? 1 : -1),
      GetRandomValue(minSpeed, maxSpeed) * (GetRandomValue(0, 1) ? 1 : -1)};
  return speed;
}

void ResetBall(Ball *ball, int screenWidth, int screenHeight) {
  ball->position = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
  ball->speed = GetRandomBallSpeed(200, 300);
}

void main_loop(Player player1, Player player2, WindowRect rect, Paddle pd,
               GameState state, Ball ball, WindowSettings window) {
  while (!WindowShouldClose()) {
    // Limit the player's rectangle Y position to stay within the larger
    // rectangle
    if (player1.position_y < rect.rectY)
      player1.position_y = rect.rectY;
    if (player1.position_y + pd.paddleHeight > rect.rectY + rect.rectHeight)
      player1.position_y = rect.rectY + rect.rectHeight - pd.paddleHeight;

    if (player2.position_y < rect.rectY)
      player2.position_y = rect.rectY;
    if (player2.position_y + pd.paddleHeight > rect.rectY + rect.rectHeight)
      player2.position_y = rect.rectY + rect.rectHeight - pd.paddleHeight;

    Vector2 mouse_pos = GetMousePosition();
    bool mouse_on_the_frame =
        CheckCollisionPointRec(mouse_pos, (Rectangle){5, 5, 630, 455});
    if (mouse_on_the_frame) {
      if (state.gamePaused) {
        state.countdownTimer += GetFrameTime();
        if (state.countdownTimer >= 1.0f) {
          state.countdownTimer = 0.0f;
          state.countdown--;
          if (state.countdown <= 0) {
            state.gamePaused = false;
          }
        }
      } else {
        // Ball movement
        ball.position.x += ball.speed.x * GetFrameTime();
        ball.position.y += ball.speed.y * GetFrameTime();

        // Ball collision with top and bottom screen boundaries
        if (ball.position.y <= ball.radius ||
            ball.position.y >= window.screenHeight - ball.radius) {
          ball.speed.y *= -1;
        }

        // Ball collision with paddles
        if (ball.position.x - ball.radius <= pd.leftPaddleX + pd.paddleWidth &&
            ball.position.y >= player1.position_y &&
            ball.position.y <= player1.position_y + pd.paddleHeight) {
          ball.speed.x *= -1;
          ball.speed.y +=
              (ball.position.y - (player1.position_y + pd.paddleHeight / 2)) *
              2;
        }

        if (ball.position.x + ball.radius >= pd.rightPaddleX &&
            ball.position.y >= player2.position_y &&
            ball.position.y <= player2.position_y + pd.paddleHeight) {
          ball.speed.x *= -1;
          ball.speed.y +=
              (ball.position.y - (player2.position_y + pd.paddleHeight / 2)) *
              2;
        }

        // Ball collision with center rectangle boundaries
        if (ball.position.x - ball.radius < rect.rectX ||
            ball.position.x + ball.radius > rect.rectX + rect.rectWidth) {
          ball.speed.x *= -1;
        }
        if (ball.position.y - ball.radius < rect.rectY ||
            ball.position.y + ball.radius > rect.rectY + rect.rectHeight) {
          ball.speed.y *= -1;
        }

        // Victory!
        if (ball.position.x + ball.radius > pd.rightPaddleX + pd.paddleWidth) {
          player1.score++;
          state.gamePaused = true;
          state.countdown = 3;
          ResetBall(&ball, window.screenWidth, window.screenHeight);
        } else if (ball.position.x - ball.radius < pd.leftPaddleX) {
          player2.score++;
          state.gamePaused = true;
          state.countdown = 3;
          ResetBall(&ball, window.screenWidth, window.screenHeight);
        }
      }
    } else {
      state.gamePaused = true;
      state.countdown = 3;
    }

    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    // Playing field
    DrawRectangleLines(rect.rectX, rect.rectY, rect.rectWidth, rect.rectHeight,
                       BLACK);
    DrawFPS(10, 10);

    DrawText(
        window.title,
        (window.screenWidth - (strlen(window.title) * (window.fontSize / 2))) /
            2,
        (window.fontSize / 2), window.fontSize, WHITE);

    DrawText(window.footer,
             (window.screenWidth - MeasureText(window.footer, 14)) / 2,
             window.screenHeight - 35, 14, BLACK);

    // Draw ball
    DrawCircleV(ball.position, ball.radius, BLACK);

    // Draw players
    if (mouse_on_the_frame) {
      DrawRectangle(100, player1.position_y, 20, 100, Fade(GREEN, 0.9f));
      // DrawRectangle(screenWidth - 120, (screenHeight - 100) / 2, 20, 100,
      // Fade(RED, 0.9f));

      DrawRectangle(pd.rightPaddleX, player2.position_y, pd.paddleWidth,
                    pd.paddleHeight, Fade(RED, 0.9f));
      // DrawRectangle(leftPaddleX, (screenHeight - 100) / 2, paddleWidth,
      // paddleHeight, Fade(GREEN, 0.9f));
    }

    // Draw scores
    DrawText(TextFormat("Player 1: %d", player1.score), 70, 70, 20, BLACK);
    DrawText(TextFormat("Player 2: %d", player2.score),
             window.screenWidth - 140, 70, 20, BLACK);

    // Draw countdown
    if (state.gamePaused && state.countdown > 0) {
      const char *countdownText = TextFormat("%d", state.countdown);
      int textWidth = MeasureText(countdownText, 60);
      DrawRectangle((window.screenWidth / 2) - (textWidth / 2) - 10,
                    window.screenHeight / 2 - (60 / 2) - 10, textWidth + 20,
                    60 + 20, LIGHTGRAY);
      DrawText(countdownText, (window.screenWidth / 2) - (textWidth / 2),
               window.screenHeight / 2 - (60 / 2), 60, BLACK);
    }

    // Draw pause
    if (!mouse_on_the_frame) {
      int textWidth = MeasureText("Pause", 60);
      DrawRectangle((window.screenWidth / 2) - (textWidth / 2) - 10,
                    window.screenHeight / 2 - (60 / 2) - 10, textWidth + 20,
                    60 + 20, LIGHTGRAY);
      DrawRectangleLines((window.screenWidth / 2) - (textWidth / 2) - 10,
                         window.screenHeight / 2 - (60 / 2) - 10,
                         textWidth + 20, 60 + 20, BLACK);
      DrawText("Pause", (window.screenWidth / 2) - (textWidth / 2),
               window.screenHeight / 2 - (60 / 2), 60, BLACK);
    }

    // Draw key pressed
    short pressed_key = GetKeyPressed();
    char key_string[2];
    if (pressed_key) {
      key_string[0] = pressed_key > 255 ? key_string[0] : (char)pressed_key;
    }
    if (key_string[0] != '\0') {
      DrawText(key_string, 27, window.screenHeight - 196, 14, BLUE);
      DrawRectangleLines(20, window.screenHeight - 200, 22, 22, BLACK);
    }

    // Player`s movement
    if (IsKeyDown((char)'W')) {
      player1.position_y -= 7;
      printf("char W is pressed\n");
    } else if (IsKeyDown((char)'S')) {
      printf("char S is pressed\n");
      player1.position_y += 7;
    }

    static const char *up_down = NULL;
    if (IsKeyDown(264)) {
      player2.position_y += 7;
      up_down = "Down";
    } else if (IsKeyDown(265)) {
      player2.position_y -= 7;
      up_down = "Up";
    }

    if (up_down != NULL) {
      DrawText(up_down, window.screenWidth - 40, window.screenHeight - 196, 14,
               BLUE);
      DrawRectangleLines(window.screenWidth - 45, window.screenHeight - 200, 40,
                         22, BLACK);
    }
    EndDrawing();
  }
}
