#include "Terminal_input_event_manager.h"
#include "Terminal_settings_manager.h"
#include "Terminal_render.h"
#include "../Terminal_frontend/TPF.h"
#include <unistd.h>
#include <ctype.h>

//for removing
#include <stdio.h>
#include <string.h>
#define GREENF "\e[2;32m"
#define BLACKF "\e[30m"
#define BLUEF "\e[34m"
#define REDF "\e[31m"

#define GREENF_B "\e[1;32m"


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

static int TIEM_handle_incoming_event(IncomingEvent_t *incoming_event,char* str,size_t *str_length){
    char exit=0x1f & 'q';
    char buffer[1024]={0};
    size_t buffer_length=0;

    char* event_type="Incoming key press event";
    int result=1;
    
    if(incoming_event->key==exit){
        result=0;
        TR_reset_screen();
    }else{


        if(incoming_event->key_type==TEXT){
            buffer[0]=incoming_event->key;
            buffer[1]='\0';
            buffer_length=1;
            //sprintf(buffer,"%sevent data:\r\n\t%scharacter type %s= %s\r\n\t%skey %s= %d\r\n\t%sevent type %s= %s\r\n\t%skey char %s= %s'%c'%s\r\n",BLUEF,GREENF,BLACKF,"TEXT",GREENF,BLACKF,incoming_event->key,GREENF,BLACKF,event_type,GREENF,BLACKF,REDF,incoming_event->key,BLACKF);
        }

        if(incoming_event->key_type==CONTROL){
            if(incoming_event->key==13){
                buffer[0]='\r';
                buffer[1]='\n';
                buffer[2]='\0';
                buffer_length=2;
            }
            //sprintf(buffer,"%sevent data:\r\n\t%scharacter type %s= %s\r\n\t%skey %s= %d\r\n\t%sevent type %s= %s\r\n",BLUEF,GREENF,BLACKF,"TEXT",GREENF,BLACKF,incoming_event->key,GREENF,BLACKF,event_type,GREENF,BLACKF);
        }   

        if((*str_length+buffer_length)<=4095){
            strncat(str,buffer,buffer_length);
            *str_length+=buffer_length;

            TR_clean_screen();
            write(STDOUT_FILENO,str,*str_length);
        }
    }

    return result;
}

void TIEM_init_event_listening(){
    TerminalWiget_t *window=NULL;
    TerminalWiget_t *editor_panel=NULL;
    struct winsize window_size;
    int result=0;
    IncomingEvent_t incoming_event={.event_type=INCOMING_KEYBOARD_EVENT,.key=-1};
    int is_should_continue=1;
    char str[4096]={0};
    size_t str_length=0;
    
    result=TSM_obtain_window_settings(&window_size);

    if(!result){
        TR_clean_screen();

        window=Wiget_create();
        Wiget_set_width(window,window_size.ws_col);
        Wiget_set_height(window,window_size.ws_row);

        editor_panel=Wiget_create();
        Wiget_set_width(editor_panel,window_size.ws_col-2);
        Wiget_set_height(editor_panel,window_size.ws_row-2);

        window->child=editor_panel;

        printf("\rresult = %d\r\nwindow size:\r\n\twidth = %d\r\n\theight = %d\r\n\n",result,window_size.ws_col,window_size.ws_row);
        
        while(is_should_continue){
            TIEM_listen_input_event(&incoming_event);

            Wiget_Draw(window);

            if(incoming_event.key!=-1)
                is_should_continue=TIEM_handle_incoming_event(&incoming_event,str,&str_length);

            incoming_event.key=-1;
            
            
        }

        Wiget_delete(editor_panel);
        Wiget_delete(window);
    }

}