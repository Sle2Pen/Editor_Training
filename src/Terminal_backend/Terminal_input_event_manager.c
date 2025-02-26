#include "Terminal_input_event_manager.h"
#include "Terminal_settings_manager.h"
#include "Terminal_render.h"
#include <unistd.h>
#include <ctype.h>

#include <stdio.h>

static void TIEM_listen_input_event(IncomingEvent_t *incoming_event){
    int input=0;
    char pressed_key=0;

    while((input=read(STDIN_FILENO, &pressed_key, 1)) == 1){
        if (iscntrl(pressed_key)) {
            incoming_event->key_type=CONTROL;
        }else {
            incoming_event->key_type=TEXT;
        }

        incoming_event->key=(int)pressed_key;

        if(pressed_key=='q')
            break;
    }

    
}

static int TIEM_handle_incoming_event(IncomingEvent_t *incoming_event){
    char exit=0x1f & 'q';

    char* event_type="Incoming key press event";
    int result=1;
    if(incoming_event->key==exit){
        result=0;
        TR_clean_screen();
    }

    printf("event data:\r\n\tcharacter type = %s\r\n\tkey = %d\r\n\tevent type = %s",(incoming_event->key_type==TEXT)?"TEXT":"CONTROL",incoming_event->key,event_type);
    
    if(incoming_event->key_type==TEXT)
        printf("\r\n\tkey char = '%c'",incoming_event->key);
    
    printf("\r\n\n");

    return result;
}

void TIEM_init_event_listening(){
    struct winsize window_size;
    int result=0;
    IncomingEvent_t incoming_event={.event_type=INCOMING_KEYBOARD_EVENT,.key=-1};
    int is_should_continue=1;
    
    result=TSM_obtain_window_settings(&window_size);

    if(!result){
        TR_clean_screen();

        printf("\rresult = %d\r\nwindow size:\r\n\twidth = %d\r\n\theight = %d\r\n\n",result,window_size.ws_col,window_size.ws_row);
        
        while(is_should_continue){
            TIEM_listen_input_event(&incoming_event);

            if(incoming_event.key!=-1)
                is_should_continue=TIEM_handle_incoming_event(&incoming_event);

            incoming_event.key=-1;
            
            
        }
    }

}