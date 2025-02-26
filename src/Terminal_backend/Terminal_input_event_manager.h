#ifndef TERMINAL_INPUT_EVENT_MANAGER_H_INCLUDED
#define TERMINAL_INPUT_EVENT_MANAGER_H_INCLUDED
typedef enum event_type{
    INCOMING_KEYBOARD_EVENT,
    KEYBOARD_EVENT,
    INTERNAL_EVENT
}EventType_t;

typedef enum incoming_key_type{
    CONTROL,
    TEXT
}IncomingKeyType_t;

typedef struct text_input_event{
    EventType_t event_type;
    int bytes_count;
    short character;
}TextInputEvent_t;

typedef struct key_press_event{
    EventType_t event_type;
    int key;
}KeyPressEvent_t;

typedef struct incoming_event{
    EventType_t event_type;
    IncomingKeyType_t key_type;
    int key;
}IncomingEvent_t;

typedef union event{
    KeyPressEvent_t key_press_event;
    TextInputEvent_t text_input_event;
}Event_t;

void TIEM_init_event_listening(void);
#endif