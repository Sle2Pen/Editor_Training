#include "Terminal_render.h"
#include <unistd.h>

void TR_clean_screen(){
    write(STDOUT_FILENO,"\e[30;47m",8);
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
}

void TR_on_render(){
    //TR_clean_screen();
}

void TR_reset_screen(){
    write(STDOUT_FILENO,"\e[0m",4);
}