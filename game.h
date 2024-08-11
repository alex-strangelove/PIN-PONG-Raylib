#include "raylib.h"
#include <string.h>
#include <sys/types.h>

// Types
typedef struct Ball {
  Vector2 position;
  Vector2 speed;
  float radius;
} Ball;

typedef struct Paddle {
  int paddleWidth;
  int paddleHeight;
  int leftPaddleX;
  int rightPaddleX;
} Paddle;

typedef struct Player {
  short position_y;
  int score;
} Player;

typedef struct WindowRect {
  int rectWidth;
  int rectHeight;
  int rectX;
  int rectY;
} WindowRect;

typedef struct GameState {
  int countdown;
  float countdownTimer;
  bool gamePaused;
} GameState;

typedef u_int32_t u32;

typedef struct WindowSettings {
  char *title;
  char *footer;
  u32 screenWidth;
  u32 screenHeight;
  u32 targetFPS;
  u32 fontSize;
} WindowSettings;

Vector2 GetRandomBallSpeed(int minSpeed, int maxSpeed);
void ResetBall(Ball *ball, int screenWidth, int screenHeight);

void main_loop(Player player1, Player player2, WindowRect rect, Paddle pd,
               GameState state, Ball ball, WindowSettings window);
