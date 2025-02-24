#ifndef TEXT_BUFFER_H_INCLUDED
#define TEXT_BUFFER_H_INCLUDED

#include <stdlib.h>

typedef int* Text_t;

#define T TextBuffer_t
typedef struct T* T;
struct T {
  Text_t text;
  size_t size;
  size_t size_in_characters;
};

typedef int Character_t;

T TextBuffer_Create(size_t buffer_size);
Character_t TextBuffer_CharacterFrom(TextBuffer_t current_buffer, int offset);
void TextBuffer_InsertFrom(T current_buffer, Text_t string_fragment,
                           int offset);
void TextBuffer_Delete(T removing_buffer);

#undef TextBuffer_t
#endif