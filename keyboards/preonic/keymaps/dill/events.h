#pragma once

#include "pointing_device.h"
#include "keycodes.h"

#define EVENT_MOUSE_MOVE                                1
#define EVENT_MOUSE_CLICK                               2
#define EVENT_MOUSE_PRESS                               3
#define EVENT_MOUSE_RELEASE                             4

#define EVENT_KEYBOARD_TAP                              5
#define EVENT_KEYBOARD_PRESS                            6
#define EVENT_KEYBOARD_RELEASE                          7

#define EVENT_LAYER_ENABLE                              8
#define EVENT_LAYER_DISABLE                             9

#define EVENT_RGB_ENABLE                                10
#define EVENT_RGB_DISABLE                               11
#define EVENT_RGB_SET_HSV                               12
#define EVENT_RGB_INCREASE_HUE                          13
#define EVENT_RGB_DECREASE_HUE                          14
#define EVENT_RGB_INCREASE_SAT                          15
#define EVENT_RGB_DECREASE_SAT                          16
#define EVENT_RGB_INCREASE_VAL                          17
#define EVENT_RGB_DECREASE_VAL                          18
#define EVENT_RGB_MODE                                  19

#define EVENT_SET_CUSTOM                                20

#define EVENT_SET_ENCODER_MODE                          21

#define EVENT_KEY_PRESSED                               22
#define EVENT_KEY_RELEASED                              23

#define EVENT_ECHO                                      24

#define EVENT_SEND_KEY_STROKES_ENABLE                   25
#define EVENT_SEND_KEY_STROKES_DISABLE                  26


uint16_t custom_assigns[108] = { MUTE_DEAFEN };

typedef union {
    uint32_t raw;
    struct {
        uint8_t encoder_mode;
    };
} user_config_t;
bool send_key_strokes = false;
user_config_t user_config;

void procMouseMove(int8_t x_delta, int8_t y_delta) {
  report_mouse_t current;
  current = pointing_device_get_report();
  current.x = x_delta;
  current.y = y_delta;
  pointing_device_set_report(current);
  pointing_device_send();
}

void procMouseClick(uint8_t button) {
  switch (button) {
    case 1: {
      register_code16(KC_BTN1);
      unregister_code16(KC_BTN1);
    }
      break;
    case 2: {
      register_code16(KC_BTN2);
      unregister_code16(KC_BTN2);
    }
      break;
    case 3: {
      register_code16(KC_BTN3);
      unregister_code16(KC_BTN3);
    }
      break;
    case 4: {
      register_code16(KC_BTN4);
      unregister_code16(KC_BTN4);
    }
      break;
    case 5: {
      register_code16(KC_BTN5);
      unregister_code16(KC_BTN5);
    }
      break;
  }
}

void procMousePress(uint8_t button) {
  switch (button) {
    case 1: {
      register_code16(KC_BTN1);
    }
      break;
    case 2: {
      register_code16(KC_BTN2);
    }
      break;
    case 3: {
      register_code16(KC_BTN3);
    }
      break;
    case 4: {
      register_code16(KC_BTN4);
    }
      break;
    case 5: {
      register_code16(KC_BTN5);
    }
      break;
  }
}

void procMouseRelease(uint8_t button) {
  switch (button) {
    case 1: {
      unregister_code16(KC_BTN1);
    }
      break;
    case 2: {
      unregister_code16(KC_BTN2);
    }
      break;
    case 3: {
      unregister_code16(KC_BTN3);
    }
      break;
    case 4: {
      unregister_code16(KC_BTN4);
    }
      break;
    case 5: {
      unregister_code16(KC_BTN5);
    }
      break;
  }
}

void procKeyboardTap(uint8_t key) {
  register_code16(key);
  unregister_code16(key);
}

void procKeyboardPress(uint8_t key) {
  register_code16(key);
}

void procKeyboardRelease(uint8_t key) {
  unregister_code16(key);
}

void procLayerEnable(uint8_t layer) {
  layer_on(layer);
}

void procLayerDisable(uint8_t layer) {
  layer_off(layer);
}

void procRGBEnable(void) {
    rgblight_enable();
}

void procRGBDisable(void) {
    rgblight_disable();
}

void procRGBSetHSV(uint8_t hue, uint8_t sat, uint8_t val) {
    rgblight_sethsv(hue, sat, val);
}

void procRGBIncreaseHue(void) {
    rgblight_increase_hue();
}

void procRGBDecreaseHue(void) {
    rgblight_decrease_hue();
}

void procRGBIncreaseSat(void) {
    rgblight_increase_sat();
}

void procRGBDecreaseSat(void) {
    rgblight_decrease_sat();
}

void procRGBIncreaseVal(void) {
    rgblight_increase_val();
}

void procRGBDecreaseVal(void) {
    rgblight_decrease_val();
}

void procRGBMode(uint8_t mode) {
    rgblight_mode(mode);
}

void procSetCustom(uint8_t index, uint8_t code) {
    custom_assigns[index] = code;
}

void procSetEncoderMode(uint8_t mode) {
    user_config.encoder_mode = mode;
    eeconfig_update_user(user_config.raw);
}

void procEnableSendKeyStrokes(void) {
    send_key_strokes = true;
}

void procDisableSendKeyStrokes(void) {
    send_key_strokes = false;
}

void procEvent(uint8_t* event) {
  switch(event[0]) {
    case EVENT_MOUSE_MOVE: {
      procMouseMove(event[1], event[2]);
    }
      break;
    case EVENT_MOUSE_CLICK: {
      procMouseClick(event[1]);
    }
      break;
    case EVENT_MOUSE_PRESS: {
      procMousePress(event[1]);
    }
      break;
    case EVENT_MOUSE_RELEASE: {
      procMouseRelease(event[1]);
    }
      break;
    case EVENT_KEYBOARD_TAP: {
      procKeyboardTap(event[1]);
    }
      break;
    case EVENT_KEYBOARD_PRESS: {
      procKeyboardPress(event[1]);
    }
      break;
    case EVENT_KEYBOARD_RELEASE: {
      procKeyboardRelease(event[1]);
    }
      break;
    case EVENT_LAYER_ENABLE: {
      procLayerEnable(event[1]);
    }
      break;
    case EVENT_LAYER_DISABLE: {
      procLayerDisable(event[1]);
    }
      break;
    case EVENT_RGB_ENABLE: {
      procRGBEnable();
    }
      break;
    case EVENT_RGB_DISABLE: {
      procRGBDisable();
    }
      break;
    case EVENT_RGB_SET_HSV: {
      procRGBSetHSV(event[1], event[2], event[3]);
    }
      break;
    case EVENT_RGB_INCREASE_HUE: {
      procRGBIncreaseHue();
    }
      break;
    case EVENT_RGB_DECREASE_HUE: {
      procRGBDecreaseHue();
    }
      break;
    case EVENT_RGB_INCREASE_SAT: {
      procRGBIncreaseSat();
    }
      break;
    case EVENT_RGB_DECREASE_SAT: {
      procRGBDecreaseSat();
    }
      break;
    case EVENT_RGB_INCREASE_VAL: {
      procRGBIncreaseVal();
    }
      break;
    case EVENT_RGB_DECREASE_VAL: {
      procRGBDecreaseVal();
    }
      break;
    case EVENT_RGB_MODE: {
      procRGBMode(event[1]);
    }
      break;
    case EVENT_SET_CUSTOM: {
      procSetCustom(event[1], event[2]);
    }
      break;
    case EVENT_SET_ENCODER_MODE: {
      procSetEncoderMode(event[1]);
    }
      break;
    case EVENT_SEND_KEY_STROKES_ENABLE: {
      procEnableSendKeyStrokes();
    }
      break;
    case EVENT_SEND_KEY_STROKES_DISABLE: {
      procDisableSendKeyStrokes();
    }
      break;
  }
}
