#define TERMINATING_CHAR -128

#define EVENT_FLASH 0
#define EVENT_MOUSE_MOVE 1
#define EVENT_MOUSE_CLICK 2
#define EVENT_MOUSE_PRESS 3
#define EVENT_MOUSE_RELEASE 4
#define EVENT_KEYBOARD_PRESS 5
#define EVENT_KEYBOARD_RELEASE 6
#define EVENT_KEYBOARD_RELEASE_ALL 7
#define EVENT_KEYBOARD_PRESS_AND_RELEASE 8

#define MOUSE_BUTTON_LEFT 0
#define MOUSE_BUTTON_RIGHT 1
#define MOUSE_BUTTON_MIDDLE 2

uint8_t MOUSE_MAP[3] = {
    KC_BTN1,
    KC_BTN2,
    KC_BTN3
};
