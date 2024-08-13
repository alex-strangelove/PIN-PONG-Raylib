#include "start_menu.h"
#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

const int rectWidth = 300;
const int rectHeight = 200;
Rectangle pop = {
    .x = (WIDTH / 2) - (rectWidth / 2),
    .y = (HEIGHT / 2) - (rectHeight / 2),
    .width = rectWidth,
    .height = rectHeight};

IpSettings sets = {{0, 0, 0, 0}, 5600};
char ip_str[16];
char port_str[6];

static bool ip_active = false;
static bool port_active = false;

bool show_start_popup = true;
bool show_ipset_popup = false;
bool on_window_quit = false;
bool singleplayer = false;

int start_menu(void)
{
  BeginDrawing();
  ClearBackground(LIGHTGRAY);

  if (on_window_quit || WindowShouldClose())
  {
    return 1;
  }

  if (show_start_popup)
  {
    PopWelcome(pop);
  }

  if (show_ipset_popup)
  {
    PopIPSettings(pop, &sets, ip_str, port_str, ip_active, port_active);
  }

  EndDrawing();
  return 0;
}

void PopWelcome(Rectangle pop)
{
  // GuiDrawRectangle(pop, 2, BLACK, RAYWHITE);
  if (GuiWindowBox(pop, "Pong start"))
  {
    on_window_quit = true;
  }
  const char *up_title = "Hello and Welcome to the";
  int up_title_size = 18;
  const char *title = "Pong";
  int title_size = 24;

  int up_title_width = MeasureText(up_title, up_title_size);
  int title_width = MeasureText(title, title_size);

  Rectangle quit_button = {
      .x = (WIDTH / 2) - ((pop.width / 4) / 2),
      .y = HEIGHT - pop.height + 15,
      .width = (pop.width / 4),
      .height = (pop.height / 7)};

  Rectangle central_buttons = {
      .x = (WIDTH / 2) - 80,
      .y = HEIGHT / 2 + 17,
      .width = 80,
      .height = (pop.height / 7)};

  DrawText(up_title, pop.x + (pop.width / 2) - (up_title_width / 2),
           pop.y + 35, up_title_size, BLACK);
  DrawText(title, pop.x + (pop.width / 2) - (title_width / 2),
           pop.y + 60, title_size, VIOLET);

  const char *text_mode = "Choose the game mode";
  GuiDrawText(text_mode, (Rectangle){WIDTH / 2 - 60, HEIGHT / 2 - 7, 120, (pop.height / 7)}, 1, BLACK);

  if (GuiButton(quit_button, "Quit"))
  {
    on_window_quit = true;
  }

  if (GuiButton(central_buttons, "Singleplayer"))
  {
    show_start_popup = false;
    show_ipset_popup = false;
    singleplayer = true;
  }

  if (GuiButton((Rectangle){WIDTH / 2, central_buttons.y, central_buttons.width, central_buttons.height}, "Multiplayer"))
  {
    show_start_popup = false;
    show_ipset_popup = true;
  }
}

void PopIPSettings(Rectangle pop, IpSettings *sets, char ip_str[], char port_str[], bool ip_active, bool port_active)
{
  // GuiDrawRectangle(pop, 2, BLACK, RAYWHITE);
  if (GuiWindowBox(pop, "IP Settings"))
  {
    on_window_quit = true;
  }
  const char *up_title = "IP Settings";
  int up_title_size = 24;
  const char *title = "Please, enter the data";
  int title_size = 18;
  const char *ip_title = "IP Adress";
  const char *port_title = "Port";
  int ip_port_size = 12;

  int up_title_width = MeasureText(up_title, up_title_size);
  int title_width = MeasureText(title, title_size);
  int port_width = MeasureText(port_title, ip_port_size);

  Rectangle cancel_button = {
      .x = (WIDTH / 2) - (pop.width / 3),
      .y = HEIGHT - pop.height + 15,
      .width = (pop.width / 4),
      .height = (pop.height / 7)};

  Rectangle apply_button = {
      .x = (WIDTH / 2) + (pop.width / 3) - (pop.width / 4),
      .y = HEIGHT - pop.height + 15,
      .width = (pop.width / 4),
      .height = (pop.height / 7)};

  DrawText(up_title, pop.x + (pop.width / 2) - (up_title_width / 2),
           pop.y + 35, up_title_size, BLACK);
  DrawText(title, pop.x + (pop.width / 2) - (title_width / 2),
           pop.y + 63, title_size, BLACK);

  DrawText(ip_title, (WIDTH / 2) - 90,
           (HEIGHT / 2) - 7, ip_port_size, BLACK);
  DrawText(port_title, (WIDTH / 2) + 75 - port_width,
           (HEIGHT / 2) - 7, ip_port_size, BLACK);

  Rectangle ip_input_box = {
      .x = (WIDTH / 2) - 105,
      .y = (HEIGHT / 2) + 10,
      .height = 30,
      .width = 90};
  // Rectangle port_input_box = {
  //     .x = (WIDTH / 2) + 20,
  //     .y = (HEIGHT / 2) + 10,
  //     .height = 30,
  //     .width = 90};

  if (GuiTextBox(ip_input_box, ip_str, 16, true))
  {
    // ip_active = true;
    // port_active = false;
    sscanf(ip_str, "%hhu.%hhu.%hhu.%hhu", &sets->ip[0], &sets->ip[1], &sets->ip[2], &sets->ip[3]);
    printf("Updated IP: %d.%d.%d.%d\n", sets->ip[0], sets->ip[1], sets->ip[2], sets->ip[3]);
  }
  // if (GuiTextBox(port_input_box, port_str, 5, true))
  // {
  //   ip_active = false;
  //   port_active = true;
  //   sets->port = (short)atoi(port_str);
  //   printf("Updated port: %d\n", sets->port);
  // }

  if (GuiButton(cancel_button, "Cancel"))
  {
    show_ipset_popup = false;
    show_start_popup = true;
  }
  if (GuiButton(apply_button, "Apply"))
  {
    // Actions for save the data
    printf("Your ip: %s\nYour port: %s\n", ip_str, port_str);
  }
}