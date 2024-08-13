#include "raylib.h"

#define WIDTH 640
#define HEIGHT 480

typedef struct
{
    unsigned char ip[4];
    short port;
} IpSettings;

extern bool show_start_popup;
extern bool show_ipset_popup;
extern bool on_window_quit;
extern bool singleplayer;

int start_menu(void);
void PopWelcome(Rectangle pop);
void PopIPSettings(Rectangle pop, IpSettings *sets, char ip_str[], char port_str[], bool ip_active, bool port_active);