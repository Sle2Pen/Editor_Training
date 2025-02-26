#ifndef TERMINAL_RENDER_H_INCLUDED
#define TERMINAL_RENDER_H_INCLUDED

#include <stdio.h>
#define BS 1024
typedef struct line{
    size_t line_width;
    char line_buffer[BS];
}Line_t;

typedef struct screen_buffer{
    int max_width;
    int max_height;
    int current_width;
    int current_height;
    Line_t lines[BS];
}ScreenBuffer_t;

void TR_clean_screen(void);
void TR_on_render(ScreenBuffer_t* buffer);
void TR_reset_screen(void);
#endif