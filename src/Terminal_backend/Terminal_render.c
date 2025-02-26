#include "Terminal_render.h"
#include <unistd.h>

void TR_clean_screen(){
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
}

void TR_on_render(){
    //TR_clean_screen();
}