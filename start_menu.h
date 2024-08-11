#include "raylib.h"

#define WIDTH 640
#define HEIGHT 480

typedef struct
{
    unsigned char ip[4];
    short port;
} IpSettings;

bool start_menu();
bool PopWelcome(Rectangle pop);
void PopIPSettings(Rectangle pop, IpSettings *sets, char ip_str[], char port_str[], bool ip_active, bool port_active);