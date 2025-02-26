#ifndef TERMINAL_SETTINGS_MANAGER_H_INCLUDED
#define TERMINAL_SETTINGS_MANAGER_H_INCLUDED
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
// typedef struct window_settings{
//     int width;
//     int height;
// }WindowSettings_t;

void TSM_enable_RAW_mode(void);
void TSM_disable_RAW_mode(void);
int TSM_obtain_window_settings(struct winsize* window_settings);
#endif