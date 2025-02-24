#include "Document_view.h"

void editor_greetings() {
  int is_should_open_file = 1;
  char start_editing_status = 0;

  while (is_should_open_file) printf("Do you want to open file?[y/n]\n");
  start_editing_status = getchar();
  getchar();

  switch (start_editing_status) {
    case 'y':
      PieceTable_t* piece_table = PieceTable_create();
      Document_t document;
      break;
    case 'n':
      break;
    default:
      break;
  }
}

void document_initialize(Document_t* document) {}

void document_prepare_buffer(Document_t* document) {
  PieceTable_t* document_piece_table = NULL;

  document_piece_table = PieceTable_create();

  document->document_piece_table = document_piece_table;
}

void document_obtain_file_data(Document_t* document) {
  long file_size = -1;
  FILE* file_pointer = NULL;

  file_pointer = open_file_for_reading(document->document_path);

  if (file_pointer) {
    file_size = get_file_size(document->document_file_pointer);

    if (file_size > -1) {
      document->document_file_size = (size_t)file_size;
      document->document_file_pointer = file_pointer;
      document->document_size = document->document_file_size;
      document->is_document_exist = 1;
      document->is_document_opened = 1;
    }
  }
}

char* document_read_file(Document_t* document) {
  char* result_original_string = (char*)malloc((size_t)presize + 1);

  result_original_string[(size_t)presize] = '\0';

  for (int i = 0; !feof(file_pointer); i++) {
    current_char = (char)fgetc(file_pointer);
    result_original_string[i] = current_char;
  }

  close_file(document->document_file_pointer);

  return result_original_string;
}

void document_clear_buffer(Document_t* document) {
  PieceTable_delete_table(document->document_piece_table);
  document->document_piece_table = NULL;
}

void document_render(Document_t* document) {
  int piece_table_length = 0;
  int current_char = 0;
  int string_counter = 1;
  int is_new_line = 1;

  printf("Full text:\n\"");

  for (int i = 0; i < current_piece_table->pieces_count; i++)
    piece_table_length += current_piece_table->pieces[i].length_in_buffer;

  for (int i = 0; i < piece_table_length; i++) {
    current_char = PieceTable_index(current_piece_table, i);

    if (is_new_line) {
      printf("\t%d  ", string_counter);
      is_new_line = 0;
    }

    if (current_char == '\n') {
      string_counter++;
      is_new_line = 1;
    }

    putchar(current_char);
  }

  printf("\"\nText length = %d\n\n", piece_table_length);
}

void document_edit(Document_t* document) {}