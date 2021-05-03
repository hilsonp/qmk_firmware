/* TASKS
 * - Compile and test current layout
 * - 
 * - WinCompose and Unicode https://docs.qmk.fm/#/feature_unicode?id=methods
 * - Modifiers on home row (lwin, lalt, lctrl, lshift - rshift, rctrl, ralt, rwin)
 *   https://precondition.github.io/home-row-mods
 * - LCTRL et AltGr deviennent MO(SYMFN) avec Fn a la main droite
 * - Move to QWERTY
 * - Move to Colemak using Tarmak
 * - Tune layout 
 *   - https://github.com/precondition/dactyl-manuform-keymap
 * - Pimoroni trackball https://github.com/drashna/qmk_firmware/blob/drashna_keymaps/users/drashna/pimoroni_trackball.c
 *                      https://www.reddit.com/r/Trackballs/comments/gtm36a/its_not_large_but_its_mine/
 * 
 * 
 */ 

#include QMK_KEYBOARD_H
#include "version.h"

#include "sendstring_belgian.h"

// Custom variables
int alt_tab_count = 0;
enum layers {
    BASE, // default layer
    NAVNUM, // symbols
    MDIA,  // media keys
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define _M_M_M_ KC_TRNS // A simple KC_TRNS that shows were the layer key is and cannot be used on that layer.
#define XXXXXXX KC_NO

enum custom_keycodes {
    ALTTAB = SAFE_RANGE,
    LBRACKET,
    RBRACKET,
    LPARENT,
    RPARENT,
    RCBRACKET,
    LCBRACKET,
    BCKSLASH,
    COLON,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case ALTTAB:
        if (record->event.pressed) {
          SEND_STRING(SS_DOWN(X_LALT)SS_DOWN(X_TAB));
          alt_tab_count++;
        } else {
          SEND_STRING(SS_UP(X_TAB));
        }
        break;
      case MO(NAVNUM):
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
        } else {
            // when keycode QMKBEST is released
            if (alt_tab_count > 0) {
              SEND_STRING(SS_UP(X_LALT));;
            }
        }
        break;
      case LBRACKET:
        if (record->event.pressed) {
            SEND_STRING("[");
        }
        break;
      case RBRACKET:
        if (record->event.pressed) {
            SEND_STRING("]");
        }
        break;
      case LPARENT:
        if (record->event.pressed) {
            SEND_STRING("(");
        }
        break;
      case RPARENT:
        if (record->event.pressed) {
            SEND_STRING(")");
        }
        break;
      case LCBRACKET:
        if (record->event.pressed) {
            SEND_STRING("{");
        }
        break;
      case RCBRACKET:
        if (record->event.pressed) {
            SEND_STRING("}");
        }
        break;
      case BCKSLASH:
        if (record->event.pressed) {
            SEND_STRING("\\");
        }
        break;
      case COLON:
        if (record->event.pressed) {
            SEND_STRING(":");
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer */
[BASE] = LAYOUT_ergodox_pretty(
  // left hand
  KC_ESCAPE,       KC_1,        KC_2,          KC_3,        KC_4,    KC_5,    KC_LBRACKET,          KC_RBRACKET,  KC_6,    KC_7,    KC_8,        KC_9,        KC_0,      KC_MINS,
  KC_LBRACKET,     KC_Q,        KC_W,          KC_E,        KC_R,    KC_T,    KC_TAB,               KC_BSPACE,    KC_Y,    KC_U,    KC_I,        KC_O,        KC_P,      KC_EQUAL,
  KC_ENTER,        GUI_T(KC_A), ALT_T(KC_S),   CTL_T(KC_D), KC_F,    KC_G,                                        KC_H,    KC_J,    CTL_T(KC_K), ALT_T(KC_L), GUI_T(KC_SCOLON), KC_ENTER,
  KC_NONUS_BSLASH, KC_Z,        KC_X,          KC_C,        KC_V,    KC_B,    KC_DELETE,            KC_DELETE,    KC_N,    KC_M,    KC_COMM,     KC_DOT,      KC_SLSH,   KC_QUOTE,
  XXXXXXX,         XXXXXXX,     XXXXXXX,       KC_LALT,     KC_LCTL,                                              KC_RALT, KC_RCTL, XXXXXXX,     XXXXXXX,     XXXXXXX,
                                                                KC_PGUP,      KC_PGDOWN,            KC_INSERT,    KC_PSCREEN,
                                                                          XXXXXXX,              XXXXXXX,
                                                MO(NAVNUM),     KC_LSHIFT,    KC_LGUI,              KC_RGUI,      KC_RSHIFT,   LT(NAVNUM,KC_SPC)
),
/* Keymap 1: Nav and Num Layer */
[NAVNUM] = LAYOUT_ergodox_pretty(
  // left hand
  _______,           KC_F1,           KC_F2,            KC_F3,           KC_F4,            KC_F5,                KC_F11,         KC_F12,  KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,           RESET,
  LBRACKET,          KC_GRAVE,        KC_HOME,          KC_UP,           KC_END,           KC_PGUP,              _______,        _______, KC_KP_SLASH,    KC_KP_7,        KC_KP_8,        KC_KP_9,        BCKSLASH,         RBRACKET,
  LPARENT,           SFT_T(KC_ENTER), KC_LEFT,          KC_DOWN,         KC_RIGHT,         KC_PGDOWN,                                     KC_KP_MINUS,    SFT_T(KC_KP_4), CTL_T(KC_KP_5), ALT_T(KC_KP_6), GUI_T(KC_KP_DOT), RPARENT,
  LCBRACKET,         ALTTAB,          LCTL(KC_X),       LCTL(KC_C),      LCTL(KC_V),       LGUI(LSFT(KC_RIGHT)), _______,        _______, COLON,          KC_KP_1,        KC_KP_2,        KC_KP_3,        KC_APPLICATION,   RCBRACKET,
  XXXXXXX,           XXXXXXX,         XXXXXXX,          KC_LALT,         KC_LCTL,                                                                         KC_KP_0,        KC_RCTRL,       XXXXXXX,        XXXXXXX,          XXXXXXX,
                                               RESET,   XXXXXXX,         XXXXXXX, _______,
                                                        XXXXXXX,         XXXXXXX,
                                      _M_M_M_, _______, _______,         _______, _______, _______
),
};

// Runs just one time when the keyboard initializes.
void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_on();

  uint8_t layer = get_highest_layer(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
        #endif
        break;
      default:
        break;
    }

  return state;
};