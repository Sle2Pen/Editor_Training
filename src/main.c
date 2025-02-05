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

  TextBuffer_t file_buffer_1 = NULL;
  TextBuffer_t file_buffer_2 = NULL;

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
        "%p\n\tget char ptr = %p\n\tinsertion ptr = %p\n\tdeletion ptr = %p\n",
        buffer_extension_pointer, Create_text_buffer,
        Get_Character_from_text_buffer, Insert_in_text_buffer,
        Delete_text_buffer);

    file_buffer_1 = Create_text_buffer(0);

    Load_file(file_buffer_1, "main.c");

    printf(
        "\nBuffer pointer :\t%p\n\tbuffer size "
        ":\t%ld\n\tbuffer size in characters :\t%ld\n\nFile is \"main.c\"\n",
        file_buffer_1, file_buffer_1->size, file_buffer_1->size_in_characters);

    for (int i = 0; file_buffer_1->text[i] != -1; i++)
      putchar((char)Get_Character_from_text_buffer(file_buffer_1, i));

    putchar('\n');

    file_buffer_2 = Create_text_buffer(0);

    Load_file(file_buffer_2, "Makefile");

    printf(
        "\nBuffer pointer :\t%p\n\tbuffer size "
        ":\t%ld\n\tbuffer size in characters :\t%ld\n\nFile is "
        "\"Makefile\"\n",
        file_buffer_2, file_buffer_2->size, file_buffer_2->size_in_characters);

    for (int i = 0; file_buffer_2->text[i] != -1; i++)
      putchar((char)Get_Character_from_text_buffer(file_buffer_2, i));

    putchar('\n');

    Delete_text_buffer(file_buffer_1);
    Delete_text_buffer(file_buffer_2);

    Create_text_buffer = NULL;
    Get_Character_from_text_buffer = NULL;
    Insert_in_text_buffer = NULL;
    Delete_text_buffer = NULL;
    file_buffer_1 = NULL;
    file_buffer_2 = NULL;

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

  // char current_file_path[current_path_size];
  // memset(file_path, '\0', current_path_size);

  // for (int i = 0; i < (int)current_path_size - 1; i++)
  //   current_file_path[i] = (char)file_path[i];

  file_pointer = fopen(file_path, "r");

  if (file_path)
    while ((buffer_array[index] = fgetc(file_pointer)) != EOF) {
      if (buffer_array[index] == '\n') {
        index++;
        // buffer_array[index] = '\0';

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
    // buffer_array[index] = '\0';

    for (int k = 0; k < index; k++)
      current_string_fragment[k] = (int)buffer_array[k];

    current_string_fragment[index] = -1;

    Insert_in_text_buffer(text_buffer, current_string_fragment, offset);

    offset = 0;

    index = 0;
  }

  fclose(file_pointer);
}