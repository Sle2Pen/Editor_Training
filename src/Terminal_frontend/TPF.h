#ifndef TPF_H_INCLUDED
#define TPF_H_INCLUDED

typedef struct point{
    int x;
    int y;
}Point_t;

typedef struct size{
    int width;
    int height;
} Size_t;

typedef struct rectangle{
    Point_t origin;
    Size_t size;
}Rectangle_t;

typedef struct terminal_wiget{
    struct terminal_wiget* child;
    int width;
    int height;
    Rectangle_t wiget_area;
}TerminalWiget_t;

void Wiget_Draw(TerminalWiget_t*);
TerminalWiget_t* Wiget_create();
void Wiget_delete(TerminalWiget_t*);
void Wiget_set_width(TerminalWiget_t*,int);
void Wiget_set_height(TerminalWiget_t*,int);

#endif