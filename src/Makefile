PROGRAM = FoxE
TEST_PROGRAM = FoxE_tests

CC = cc
CFLAGS = -g -Wall -Wextra -std=c11
CHECK_LIB = -lcheck -lrt -lm -lsubunit 
SOURCE = main.c
TERMINAL_BACKEND_SOURCE = Terminal_backend/Terminal_settings_manager.c Terminal_backend/Terminal_render.c Terminal_backend/Terminal_input_event_manager.c
TERMINAL_FRONTEND_SOURCE = Terminal_frontend/TPF.c
OBJECTS = main.o terminal_settings.o terminal_render.o terminal_events.o tpf.o

all : clean_objects clean_program format $(PROGRAM)

$(PROGRAM) : format terminal_backend terminal_frontend main create_program clean_objects

create_program :
	$(CC) $(CFLAGS) -o $(PROGRAM) $(OBJECTS) 

main : 
	$(CC) $(CFLAGS) -c main.c -o main.o



terminal_backend : terminal_render terminal_settings terminal_events

terminal_events : 
	$(CC) $(CFLAGS) $(INCLUDES) -c Terminal_backend/Terminal_input_event_manager.c -o terminal_events.o

terminal_render : 
	$(CC) $(CFLAGS) $(INCLUDES) -c Terminal_backend/Terminal_render.c -o terminal_render.o

terminal_settings :
	$(CC) $(CFLAGS) $(INCLUDES) -c Terminal_backend/Terminal_settings_manager.c -o terminal_settings.o



terminal_frontend : tpf

tpf :
	$(CC) $(CFLAGS) -c Terminal_frontend/TPF.c -o tpf.o



format :
	clang-format -i *.c



clean : clean_objects clean_program

clean_objects :
	rm -rf $(OBJECTS)

clean_program :
	rm -f $(PROGRAM) 