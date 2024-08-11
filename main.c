#include "game.h"
#include "start_menu.h"
#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>

WindowSettings window = {
    .title = "Ping pong",
    .footer = "Created by two geniuses",
    .screenWidth = WIDTH,
    .screenHeight = HEIGHT,
    .targetFPS = 60,
    .fontSize = (WIDTH / HEIGHT) * 50,
};
WindowRect rect = {
    .rectWidth = WIDTH / 2 + 200,
    .rectHeight = HEIGHT / 2 + 40,
    .rectX = (WIDTH - (WIDTH / 2 + 200)) / 2,
    .rectY = (HEIGHT - (HEIGHT / 2 + 40)) / 2,
};

GameState state = {.countdown = 3, .countdownTimer = 0.0f, .gamePaused = true};

// Ball properties
Ball ball = {
    .position = {WIDTH / 2.0f, HEIGHT / 2.0f}, .speed = {350}, .radius = 15.0f};

// Paddles properties
Paddle pd = {.paddleWidth = 20,
             .paddleHeight = 100,
             .leftPaddleX = 100,
             .rightPaddleX = WIDTH - 120};

Player player1 = {
    .score = 0,
    .position_y = (HEIGHT - 100) / 2,
};

Player player2 = {
    .score = 0,
    .position_y = (HEIGHT - 100) / 2,
};

bool multiplayer_mode = false;
bool singleplayer_mode = false;

int main(void)
{
    // Init window
    InitWindow(WIDTH, HEIGHT, "Pong Online");
    SetMouseCursor(MOUSE_CURSOR_ARROW);
    SetTargetFPS(window.targetFPS);

    singleplayer_mode = start_menu();

    while (!WindowShouldClose())
    {
        if (singleplayer_mode)
        {
            // Main game loop
            printf("%s\n", "true");
            main_loop(player1, player2, rect, pd, state, ball, window);
        }
        else if (multiplayer_mode)
        {
            // Function for multiplayer start
        }
    }

    return 0;
}
