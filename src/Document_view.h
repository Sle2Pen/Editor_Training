#ifndef DOCUMENT_VIEW_H_INCLUDED
#define DOCUMENT_VIEW_H_INCLUDED

typedef struct file_descriptor{
    FILE* file_pointer;
    char* file_path;
    size_t file_size;
  }FileDescriptor_t;
  
  typedef struct document {
    PieceTable_t* document_piece_table;
    FileDescriptor_t* document_file_descriptor;
    //Cursor_t* cursor;
    size_t document_size;
    int is_document_exist;
    int is_document_opened;
  } Document_t;
  
  typedef struct cursor {
  } Cursor_t;
  
  void editor_greetings(void);
  
  void document_initialize(Document_t* document);
  void document_prepare_buffer(Document_t* document);
  void document_obtain_file_data(Document_t* document);
  char* document_read_file(Document_t* document);
  void document_clear_buffer(Document_t* document);
  void document_render(PieceTable_t*);
  void document_edit(Document_t* document);

  #endif