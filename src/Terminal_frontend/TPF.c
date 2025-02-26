#include "TPF.h"
#include <stdlib.h>

void Draw(TerminalWiget_t* terminal_wiget);

TerminalWiget_t* Wiget_create(){
    TerminalWiget_t* result_wiget=NULL;

    result_wiget=(TerminalWiget_t*)malloc(sizeof(TerminalWiget_t));

    return result_wiget;
}

void Wiget_delete(TerminalWiget_t* terminal_wiget){
    free(terminal_wiget);
}

void Wiget_set_width(TerminalWiget_t* terminal_wiget,int width){
    if(terminal_wiget)
        terminal_wiget->width=width;
}

void Wiget_set_height(TerminalWiget_t* terminal_wiget,int height){
    if(terminal_wiget)
        terminal_wiget->height=height;
}