PROGRAM = FoxE
TEST_PROGRAM = FoxE_tests

CC = cc
CFLAGS = -g -Wall -Wextra -std=c11
LIBRARY = -l:text_buffer/text_buffer
INCLUDES = -I../extensions/text_buffer
CLIBS = -L../extensions $(LIBRARY) -Wl,-rpath,../extensions/
CHECK_LIB = -lcheck -lrt -lm -lsubunit 
#dlopen()
SOURCE = main.c
OBJECTS = main.o

EXTENSIONS_FOLDER = ../extensions

# TEST_SOURCE = tests/text_buffer_checking.c tests/text_buffer_create_tests.c tests/text_buffer_insert_from_tests.c tests/text_buffer_character_from_tests.c tests/text_create_tests.c tests/text_calculate_size_tests.c tests/text_copy_tests.c
# TEST_OBJECTS = text_buffer_checking.o text_buffer_create_tests.o text_buffer_insert_from_tests.o text_buffer_character_from_tests.o text_create_tests.o text_calculate_size_tests.o text_copy_tests.o

# GCOV_FLAGS = --coverage
# GCOV_REPORT_DIR = tests/gcov_report
# GCOV_RESULT = $(GCOV_REPORT_DIR)/text_buffer_checking.c.gcov $(GCOV_REPORT_DIR)/*.gcno $(GCOV_REPORT_DIR)/*.gcda
# BRANCHES = --rc lcov_branch_coverage=1

#all : clean_objects clean_gcov_files clean_report clean_library clean_tests format $(LIBRARY) test gcov_report
all : copy_extensions clean_objects clean_program format $(PROGRAM)

$(PROGRAM) : format main create_program clean_objects

create_program :
	$(CC) $(CFLAGS) -o $(PROGRAM) $(OBJECTS) 
#$(CLIBS)

main : 
	$(CC) $(CFLAGS) $(INCLUDES) -c main.c -o main.o

# test : format text_buffer_checking text_create_tests text_calculate_size_tests text_copy_tests text_buffer_create_tests text_buffer_insert_from_tests text_buffer_character_from_tests $(TEST_PROGRAM) clean_objects
# 	./$(TEST_PROGRAM)

# $(TEST_PROGRAM) :
# 	$(CC) $(CFLAGS) $(TEST_OBJECTS) -o $(TEST_PROGRAM) $(CLIBS) $(CHECK_LIB)

# text_buffer_checking :
# 	$(CC) $(CFLAGS) -c tests/text_buffer_checking.c -o text_buffer_checking.o

# text_create_tests :
# 	$(CC) $(CFLAGS) -c tests/text_create_tests.c -o text_create_tests.o

# text_calculate_size_tests :
# 	$(CC) $(CFLAGS) -c tests/text_calculate_size_tests.c -o text_calculate_size_tests.o

# text_copy_tests :
# 	$(CC) $(CFLAGS) -c tests/text_copy_tests.c -o text_copy_tests.o

# text_buffer_create_tests :
# 	$(CC) $(CFLAGS) -c tests/text_buffer_create_tests.c -o text_buffer_create_tests.o

# text_buffer_character_from_tests :
# 	$(CC) $(CFLAGS) -c tests/text_buffer_character_from_tests.c -o text_buffer_character_from_tests.o

# text_buffer_insert_from_tests :
# 	$(CC) $(CFLAGS) -c tests/text_buffer_insert_from_tests.c -o text_buffer_insert_from_tests.o



# gcov_report: clean_tests format build_report call_report create_coverage_info clean_gcov_files clean_objects

# build_report :
# 	$(CC) $(CFLAGS) $(TEST_SOURCE) $(SOURCE) -o $(TEST_PROGRAM) $(CHECK_LIB) $(GCOV_FLAGS)

# call_report :
# 	./$(TEST_PROGRAM)

# create_coverage_info :
# 	mkdir -p $(GCOV_REPORT_DIR)
# 	lcov -t "Report" -c -d . -o $(GCOV_REPORT_DIR)/coverage.info $(BRANCHES)
# 	genhtml -o $(GCOV_REPORT_DIR)/html $(GCOV_REPORT_DIR)/coverage.info $(BRANCHES)


format :
	clang-format -i *.c
#text_buffer/*.h tests/*.c tests/*.h

clean : clean_objects clean_program clean_extensions

clean_objects :
	rm -rf $(OBJECTS)

# clean_gcov_files :
# 	rm -f *.gcno *.gcda

# clean_report :
# 	rm -rf tests/gcov_report

# clean_tests :
# 	rm -f $(TEST_PROGRAM)

clean_program :
	rm -f $(PROGRAM) 

clean_extensions :
	rm -rf ../extensions/*

copy_extensions :
	mkdir -p ../extensions/text_buffer
	cp ../../Editor/src/text_buffer.so ../../Editor/src/text_buffer.h ../extensions/text_buffer
	mkdir -p ../extensions/foxe_window