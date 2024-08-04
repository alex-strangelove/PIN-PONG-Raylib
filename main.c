#include "raylib.h"
#include <stdio.h>
#include <string.h>

int main(void) {
  const char *title = "Ping pong";
  const int screenWidth = 640;
  const int screenHeight = 480;

  int font_size = (screenWidth / screenHeight) * 50;
  InitWindow(screenWidth, screenHeight, ".");
  SetMouseCursor(MOUSE_CURSOR_ARROW);
  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  int i = 0;

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(LIGHTGRAY);
    DrawFPS(10, 10);
    DrawText(title, (screenWidth - (strlen(title) * (font_size / 2))) / 2,
             font_size / 2, font_size, WHITE);

    Vector2 mouse_pos = GetMousePosition();

    printf("x: %f y: %f\n", mouse_pos.x, mouse_pos.y);

    if (mouse_pos.x > (100 + 40) && mouse_pos.x < (screenWidth - (100 + 20))) {
      DrawCircle(mouse_pos.x, mouse_pos.y + 50, 20.0f, BLACK);
    } else {
      if ((int)mouse_pos.x <= screenWidth / 2) {
        printf("Player 1 is holder \n");
        DrawCircle(140 + i, mouse_pos.y + 50, 20.0f, BLACK);
        i += 5;
      } else {
        printf("Player 2 is holder \n");
        DrawCircle(screenWidth - 120, mouse_pos.y + 50, 20.0f, BLACK);
      }
    }

    if ((int)mouse_pos.x <= screenWidth / 2) {
      printf("Player 1 active: ");
      DrawRectangle(100, (int)mouse_pos.y, 20, 100, Fade(GREEN, 0.9f));
      DrawRectangle(screenWidth - 100, (screenHeight - 100) / 2, 20, 100,
                    Fade(RED, 0.9f));
    } else {
      printf("Player 2 active: ");
      DrawRectangle(screenWidth - 100, (int)mouse_pos.y, 20, 100,
                    Fade(RED, 0.9f));
      DrawRectangle(100, (screenHeight - 100) / 2, 20, 100, Fade(GREEN, 0.9f));
    }

    i = i < 380 ? i : 380;

    EndDrawing();
  }
  return 0;
}
