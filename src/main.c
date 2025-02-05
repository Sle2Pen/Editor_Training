#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../extensions/text_buffer/text_buffer.h"

void Load_file(TextBuffer_t text_buffer, char* file_path);

TextBuffer_t (*Create_text_buffer)(size_t);
Character_t (*Get_Character_from_text_buffer)(TextBuffer_t, int);
void (*Insert_in_text_buffer)(TextBuffer_t, Text_t, int);
void (*Delete_text_buffer)(TextBuffer_t);

int main(void) {
  int result = 0;
  int line_counter = 0;
  int is_new_line = 0;
  int continue_work_flag = 1;
  char answer = 0;
  char enter = 0;
  char file_name[1024] = {'\0'};
  char curernt_character = 0;

  TextBuffer_t file_buffer = NULL;

  Create_text_buffer = NULL;
  Get_Character_from_text_buffer = NULL;
  Insert_in_text_buffer = NULL;
  Delete_text_buffer = NULL;

  void* buffer_extension_pointer = NULL;

  buffer_extension_pointer =
      dlopen("../extensions/text_buffer/text_buffer.so", RTLD_LAZY);

  if (buffer_extension_pointer) {
    Create_text_buffer = dlsym(buffer_extension_pointer, "TextBuffer_Create");
    Get_Character_from_text_buffer =
        dlsym(buffer_extension_pointer, "TextBuffer_CharacterFrom");
    Insert_in_text_buffer =
        dlsym(buffer_extension_pointer, "TextBuffer_InsertFrom");
    Delete_text_buffer = dlsym(buffer_extension_pointer, "TextBuffer_Delete");

    printf(
        ".so pointer = %p\n\tcreation ptr = "
        "%p\n\tget char ptr = %p\n\tinsertion ptr = %p\n\tdeletion ptr = "
        "%p\n\n",
        buffer_extension_pointer, Create_text_buffer,
        Get_Character_from_text_buffer, Insert_in_text_buffer,
        Delete_text_buffer);

    while (continue_work_flag) {
      printf("\n\nDo you want to read file (y/n)?\n");
      scanf("%c", &answer);

      if (answer == 'y' || answer == 'Y') {
        printf("Please enter correct filepath...\n");
        if (scanf("%1023s%c", file_name, &enter) == 2) {
          file_buffer = Create_text_buffer(0);

          Load_file(file_buffer, file_name);

          printf(
              "\nBuffer pointer :\t%p\n\tbuffer size "
              ":\t%ld\n\tbuffer size in characters :\t%ld\n\nFile is "
              "\"%s\"\n",
              file_buffer, file_buffer->size, file_buffer->size_in_characters,
              file_name);

          for (int i = 0; file_buffer->text[i] != -1; i++) {
            curernt_character =
                (char)Get_Character_from_text_buffer(file_buffer, i);

            if (!i) is_new_line = 1;

            if (is_new_line) {
              line_counter++;
              printf("%d\t", line_counter);
              is_new_line = 0;
            }

            if (curernt_character == '\n') is_new_line = 1;

            putchar(curernt_character);
          }

          putchar('\n');

          Delete_text_buffer(file_buffer);
          file_buffer = NULL;
          line_counter = 0;
        }
      }

      if (answer == 'n' || answer == 'N') continue_work_flag = 0;
    }

    Create_text_buffer = NULL;
    Get_Character_from_text_buffer = NULL;
    Insert_in_text_buffer = NULL;
    Delete_text_buffer = NULL;
    file_buffer = NULL;

    dlclose(buffer_extension_pointer);
    buffer_extension_pointer = NULL;
  }

  return result;
}

void Load_file(TextBuffer_t text_buffer, char* file_path) {
  FILE* file_pointer = NULL;
  size_t current_path_size = 0;
  int index = 0;
  int offset = 0;
  char buffer_array[1024] = {'\0'};

  int current_string_fragment[1024] = {-1};

  file_pointer = fopen(file_path, "r");

  if (file_path)
    while ((buffer_array[index] = fgetc(file_pointer)) != EOF) {
      if (buffer_array[index] == '\n') {
        index++;

        for (int k = 0; k < index; k++)
          current_string_fragment[k] = (int)buffer_array[k];

        current_string_fragment[index] = -1;

        Insert_in_text_buffer(text_buffer, current_string_fragment, offset);

        offset += index;

        index = 0;
      } else
        index++;
    }

  if (index) {
    index++;

    for (int k = 0; k < index; k++)
      current_string_fragment[k] = (int)buffer_array[k];

    current_string_fragment[index] = -1;

    Insert_in_text_buffer(text_buffer, current_string_fragment, offset);

    offset = 0;

    index = 0;
  }

  fclose(file_pointer);
}