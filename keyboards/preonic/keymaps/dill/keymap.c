/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

//#include QMK_KEYBOARD_H
#include "keycodes.h"
#include "events.h"
#include "pointing_device.h"
#include "virtser.h"
#include "raw_hid.h"

#define SEND_SERIAL_KEY_STROKES true

enum preonic_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid(
  MUTE_DEAFEN,  KC_1,     KC_2,    KC_3,    KC_4,     KC_5,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
  KC_TAB,       KC_Q,     KC_W,    KC_E,    KC_R,     KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_MINUS,
  KC_LCTL,      KC_A,     KC_S,    KC_D,    KC_F,     KC_G,   KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, MT(MOD_RCTL, KC_QUOT),
  KC_LSPO,      KC_Z,     KC_X,    KC_C,    KC_V,     KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
  LOWER,        RAISE,    KC_LALT, KC_LGUI, KC_ENT,   KC_SPC, KC_SPC, KC_BSPC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid(
  KC_ESC, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_LCBR, KC_RCBR, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,S(KC_NUHS),S(KC_NUBS),KC_HOME, KC_END, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / | Pg Up| Pg Dn|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_LBRC, KC_RBRC, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset| Debug|      |      |      |      |TermOf|TermOn|      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |Aud cy|Aud on|AudOff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,     KC_F9,        KC_F10,   KC_F11,  KC_F12,
  PASS,    RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON,   TERM_OFF,     KC_1,     KC_2,    KC_3,
  _______, _______, _______, _______, _______, _______, _______, QWERTY,    _______,      KC_4,     KC_5,    KC_6,
  _______, _______, _______, _______, _______, _______, _______, _______,   KC_UP,        KC_7,     KC_8,    KC_9,
  _______, _______, _______, _______, _______, _______, _______, KC_LEFT,   KC_DOWN,      KC_RIGHT, KC_0,    KC_BSLS
)

};

uint16_t clayer = QWERTY;
uint16_t llayer = QWERTY;

void send_key_stroke(uint16_t keycode, bool pressed) {
  if (send_key_strokes) {
    if (pressed) {
      virtser_send(EVENT_KEY_PRESSED);
    } else {
      virtser_send(EVENT_KEY_RELEASED);
    }

    uint8_t fHalf = (uint8_t)(keycode & 0xFF00);
    uint8_t bHalf = (uint8_t)(keycode & 0x00FF);

    virtser_send(fHalf);
    virtser_send(bHalf);

    virtser_send(-128);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool result = true;
  static uint16_t key_timer;
  key_timer = timer_read();

  switch (keycode) {

    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      result = false;
      break;
    case LOWER:
      if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
            llayer = clayer;
            clayer = LOWER;
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
            clayer = llayer;
            llayer = LOWER;
          }
      result = false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        llayer = clayer;
        clayer = RAISE;
      } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
            clayer = llayer;
            llayer = RAISE;
          }
      result = false;
      break;
    case MUTE_DEAFEN:
      if (!record->event.pressed) {
        if (timer_elapsed(key_timer) < 1000) {
            register_code16(KC_F23);
            unregister_code16(KC_F23);
        } else {
            register_code16(KC_F24);
            unregister_code16(KC_F24);
        }
      }
      break;
    case PASS:
      if (record->event.pressed) {
          SEND_STRING("4379627Tg862g279ed2!" SS_TAP(X_ENTER));
      }
      result = false;
      break;
    case CUSTOM_0:
      if (record->event.pressed) {
        register_code16(custom_assigns[0]);
      } else {
        unregister_code16(custom_assigns[0]);
      }
      result = false;
      break;
  }

  send_key_stroke(keycode, record->event.pressed);

  return result;
};

void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();

    #ifdef RGBLIGHT_ENABLE
    rgblight_disable();
    #endif
}

void encoder_update_user(uint8_t index, bool clockwise) {
  switch (0) {
    case 0:
    {
      if (clockwise) {
        send_string(SS_TAP(X_RIGHT));
      } else {
        send_string(SS_TAP(X_LEFT));
      }
    }
      break;
    case 1:
    {
      if (clockwise) {
        send_string(SS_TAP(X_DOWN));
      } else {
        send_string(SS_TAP(X_UP));
      }
    }
      break;
    case 2:
    {
      if (clockwise) {
        send_string(SS_TAP(X_AUDIO_VOL_UP));
      } else {
        send_string(SS_TAP(X_AUDIO_VOL_DOWN));
      }
    }
      break;
    case 3:
    {
      report_mouse_t current;
      current = pointing_device_get_report();
      current.v = clockwise ? 1 : -1;
      pointing_device_set_report(current);
      pointing_device_send();
    }
      break;
    case 4:
    {
      report_mouse_t current;
      current = pointing_device_get_report();
      current.h = clockwise ? 1 : -1;
      pointing_device_set_report(current);
      pointing_device_send();
    }
      break;
  };
}

void dip_switch_update_user(uint8_t index, bool active) {
  switch (index) {
    case 0:
      if (active) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      break;
  }
}

void eeconfig_init_user(void) {
    user_config.raw = 0;
    user_config.encoder_mode = 0;
    eeconfig_update_user(user_config.raw);
}

void matrix_scan_user(void) {
}

#ifdef VIRTSER_ENABLE

uint8_t marker = 0;
uint8_t buffer[25];

void virtser_recv(uint8_t serIn)
{
  int8_t read_byte = (int8_t)serIn;
  if (read_byte == -128)
  {
    virtser_send(read_byte);
    procEvent(buffer);
    marker = 0;
  }
  else
  {
    buffer[marker++] = read_byte;
    virtser_send(serIn);
  }
}

#endif
