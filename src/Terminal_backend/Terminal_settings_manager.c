#include "Terminal_settings_manager.h"


//#include <stdlib.h>
#include <string.h>

static struct termios get_original_settings(){
    static int is_settings_saved=0;
    static struct termios original_mode;

    if(!is_settings_saved){
        tcgetattr(STDIN_FILENO, &original_mode);
        
        is_settings_saved=1;
    }

    return original_mode;
}

void TSM_enable_RAW_mode(){
    struct termios raw_mode;

    raw_mode=get_original_settings();
    //atexit(TSM_disable_RAW_mode);

    //memset
    tcgetattr(STDIN_FILENO, &raw_mode);

    raw_mode.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw_mode.c_oflag &= ~(OPOST);
    raw_mode.c_cflag |= (CS8);
    raw_mode.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw_mode.c_cc[VMIN] = 0;
    raw_mode.c_cc[VTIME] = 0;//без задержек и запаздываний печати

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_mode);

}

void TSM_disable_RAW_mode(){
    struct termios original_mode={0};

    original_mode=get_original_settings();

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_mode);

}

int TSM_obtain_window_settings(struct winsize* window_settings){
    int result=0;
    
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, window_settings) == -1 || !window_settings->ws_col) 
            result= -1;
    
    return result;
}