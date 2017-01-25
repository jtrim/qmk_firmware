#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,
  SRSFCE
};

//Tap Dance Declarations
enum {
  TD_CTRL_CMD = 0
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for Esc, twice for Caps Lock
  [TD_CTRL_CMD] = ACTION_TAP_DANCE_DOUBLE(KC_LCTRL, KC_LGUI)
// Other declarations would go here, separated by commas, if you have them
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_GRV,  KC_1,  KC_2,   KC_3,   KC_4,   KC_5,  KC_6,
        KC_TAB,  KC_Q,  KC_W,   KC_E,   KC_R,   KC_T,  TG(SYMB),
        KC_ESC,   KC_A,  KC_S,   KC_D,   KC_F,   KC_G,
        KC_LSFT, KC_Z,  KC_X,   KC_C,   KC_V,   KC_B,  LCAG_T(KC_NO),
        KC_F1,   KC_F2, KC_F3,  LALT(KC_LGUI),  KC_LGUI,
                                                       KC_HOME, KC_END,
                                                                KC_PGUP,
                                      TD(TD_CTRL_CMD), KC_LALT, KC_PGDN,
        // right hand
        MO(MDIA),     KC_7, KC_8,     KC_9,    KC_0,    KC_MINUS, KC_EQUAL,
        TG(SYMB),     KC_Y, KC_U,     KC_I,    KC_O,    KC_P,     KC_BSLS,
                      KC_H, KC_J,     KC_K,    KC_L,    KC_SCLN,  KC_QUOT,
        KC_ENTER,     KC_N, KC_M,     KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                        MO(SYMB),     KC_LEFT, KC_DOWN, KC_UP,    KC_RIGHT,
             KC_NO, KC_NO,
             KC_NO,
             KC_NO, KC_BSPC, KC_SPC
    ),

[SYMB] = KEYMAP(
       // left hand
       VRSN,    KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS,
       SRSFCE , S(KC_1), S(KC_2), S(KC_LBRC), S(KC_RBRC), S(KC_BSLS),  KC_TRNS,
       KC_TRNS, S(KC_3), S(KC_4), S(KC_9),    S(KC_0),    S(KC_MINUS),
       KC_TRNS, S(KC_5), S(KC_6), KC_LBRC,    KC_RBRC,    S(KC_8),     KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,
                                             KC_SCROLLLOCK, KC_PAUSE,
                                                             KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC__VOLDOWN, KC__VOLUP,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
[MDIA] = KEYMAP(
       // left hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                    KC_TRNS, KC_TRNS,
                                                             KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
        case 1:
        if (record->event.pressed) { // For resetting EEPROM
          eeconfig_init();
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
    case SRSFCE:
      if (record->event.pressed) {
        SEND_STRING ("OMG");
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case 1:
            ergodox_right_led_2_on();
            break;
        case 2:
            ergodox_right_led_1_on();
            break;
        default:
            // none
            break;
    }

};
