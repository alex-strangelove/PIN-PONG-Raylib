#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(void)
{
  const char *title = "Ping pong";
  const char *footer = "Created by two geniuses";
  const int screenWidth = 640;
  const int screenHeight = 480;

  // Circle speed
  int circle_x = 140;
  int speed = 5;
  int direction = 1;

  int font_size = (screenWidth / screenHeight) * 50;
  InitWindow(screenWidth, screenHeight, "Ping Pong Online");
  SetMouseCursor(MOUSE_CURSOR_ARROW);
  SetTargetFPS(60); // Set our game to run at 60 frames-per-second

  while (!WindowShouldClose())
  {
    // Calculate the top-left corner coordinates of the rectangle
    int rectWidth = screenWidth / 2 + 200;
    int rectHeight = screenHeight / 2 + 40;
    int rectX = (screenWidth - rectWidth) / 2;
    int rectY = (screenHeight - rectHeight) / 2;

    // Limit the player's rectangle Y position to stay within the larger rectangle
    Vector2 mouse_pos = GetMousePosition();
    int player1_y = mouse_pos.y;
    int player2_y = mouse_pos.y;

    if (player1_y < rectY)
      player1_y = rectY;
    if (player1_y + 100 > rectY + rectHeight)
      player1_y = rectY + rectHeight - 100;

    if (player2_y < rectY)
      player2_y = rectY;
    if (player2_y + 100 > rectY + rectHeight)
      player2_y = rectY + rectHeight - 100;

    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    // Playing field
    DrawRectangleLines(rectX, rectY, rectWidth, rectHeight, BLACK);
    DrawFPS(10, 10);

    DrawText(title, (screenWidth - (strlen(title) * (font_size / 2))) / 2,
             font_size / 2, font_size, WHITE);

    DrawText(footer, (screenWidth - MeasureText(footer, 14)) / 2,
             screenHeight - 35, 14, BLACK);

    // Concole output
    printf("x: %f y: %f\n", mouse_pos.x, mouse_pos.y);

    // Circle movement
    circle_x += speed * direction;
    if (circle_x >= screenWidth - 140 || circle_x <= 140)
    {
      direction *= -1;
    }
    DrawCircle(circle_x, screenHeight / 2, 20.0f, BLACK);

    // Marking players
    if ((int)mouse_pos.x <= screenWidth / 2)
    {
      printf("Player 1 active: ");
      DrawRectangle(100, player1_y, 20, 100, Fade(GREEN, 0.9f));
      DrawRectangle(screenWidth - 120, (screenHeight - 100) / 2, 20, 100, Fade(RED, 0.9f));
    }
    else
    {
      printf("Player 2 active: ");
      DrawRectangle(screenWidth - 120, player2_y, 20, 100, Fade(RED, 0.9f));
      DrawRectangle(100, (screenHeight - 100) / 2, 20, 100, Fade(GREEN, 0.9f));
    }

    EndDrawing();
  }
  return 0;
}
