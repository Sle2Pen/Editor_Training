//#include "Document_view.h"
#include <unistd.h>

#include "Terminal_backend/Terminal_input_event_manager.h"
//#include "Terminal_backend/Terminal_render.h"
#include "Terminal_backend/Terminal_settings_manager.h"

//#include <dlfcn.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "../extensions/text_buffer/text_buffer.h"

int main(void) {
  int result = 0;

  TSM_enable_RAW_mode();

  TIEM_init_event_listening();

  TSM_disable_RAW_mode();

  return result;
}