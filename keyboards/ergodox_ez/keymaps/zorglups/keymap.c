/* TASKS
 * - Compile and test current layout
 * - 
 * - WinCompose and Unicode https://docs.qmk.fm/#/feature_unicode?id=methods
 * - Modifiers on home row (lwin, lalt, lctrl, lshift - rshift, rctrl, ralt, rwin)
 *   https://precondition.github.io/home-row-mods
 * - LCTRL et AltGr deviennent MO(SYMFN) avec Fn à la main droite
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
#ifdef ORYX_CONFIGURATOR
  VRSN = EZ_SAFE_RANGE,
#else
  VRSN = SAFE_RANGE,
#endif
  RGB_SLD
};

enum macro_keycodes {
  KC_AG_BSLASH,
  KC_AG_SEMIC,
  KC_AG_PERIOD,
  KC_AG_LBRACKET,
  KC_AG_RBRACKET,
  KC_AG_LPAREN,
  KC_AG_RPAREN,
  KC_AG_LCURBRK,
  KC_AG_RCURBRK,
  KC_ALTTAB,
  KC_COPY_WBCK,
  KC_PASTE_WFWD,
  KC_CUT_CLOSE,
  KC_MEDIA_NEXT_PREV
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer */
[BASE] = LAYOUT_ergodox_pretty(
  // left hand
  KC_ESCAPE,       KC_1,        KC_2,          KC_3,    KC_4,    KC_5,    KC_LBRACKET,          KC_RBRACKET,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,      KC_MINS,
  KC_LBRACKET,     KC_Q,        KC_W,          KC_E,    KC_R,    KC_T,    KC_TAB,               KC_BSPACE,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      KC_EQUAL,
  KC_ENTER,        KC_A,        KC_S,          KC_D,    KC_F,    KC_G,                                        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCOLON, KC_ENTER,
  KC_NONUS_BSLASH, KC_Z,        KC_X,          KC_C,    KC_V,    KC_B,    KC_DELETE,            KC_DELETE,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_QUOTE,
  XXXXXXX,         XXXXXXX,     XXXXXXX,       KC_LALT, KC_LCTL,                                              KC_RALT, KC_RCTL, XXXXXXX, XXXXXXX, XXXXXXX,
                                                            KC_PGUP,      KC_PGDOWN,            KC_INSERT,    KC_PSCREEN,
                                                                          XXXXXXX,              XXXXXXX,
                                            MO(NAVNUM),     KC_LSHIFT,    KC_LGUI,              KC_RGUI,      KC_RSHIFT,   LT(NAVNUM,KC_SPC)
),
/* Keymap 1: Nav and Num Layer */
[NAVNUM] = LAYOUT_ergodox_pretty(
  // left hand
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,      KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  XXXXXXX, KC_GRAVE, KC_HOME, KC_UP,KC_END,KC_PGUP,_______,     KC_TRNS, KC_UP,   KC_7,    KC_8,    KC_9,    KC_ASTR, KC_F12,
  KC_TRNS, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,               KC_DOWN, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_TRNS,
  KC_TRNS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, KC_TRNS,     KC_TRNS, KC_AMPR, KC_1,    KC_2,    KC_3,    KC_BSLS, KC_TRNS,
  EEP_RST, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                         KC_TRNS, KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
                                               RGB_MOD, KC_TRNS,     RGB_TOG, RGB_SLD,
                                                        KC_TRNS,     KC_TRNS,
                                      RGB_VAD, RGB_VAI, KC_TRNS,     KC_TRNS, RGB_HUD, RGB_HUI
),
/* Keymap 2: Media and mouse keys */
[MDIA] = LAYOUT_ergodox_pretty(
  // left hand
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,                                         KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,

                                               KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,
                                                        KC_TRNS,     KC_TRNS,
                                      KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_WBAK
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case VRSN:
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        return false;
      #ifdef RGBLIGHT_ENABLE
      case RGB_SLD:
        rgblight_mode(1);
        return false;
      #endif
    }
  }
  return true;
}

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
  ergodox_right_led_3_off();

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
        ergodox_right_led_3_on();
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

// TODO: Replace this by proper Unicode handling
static uint16_t key_timer; // Use for tap/long tap mechanism
// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case KC_AG_BSLASH:
          if (record->event.pressed) {
            // SEND_STRING ("\\");
            return MACRO( D(LALT), T(KP_9), T(KP_2),  U(LALT), END  );
          }
          break;
        case KC_AG_SEMIC:
          if (record->event.pressed) {
            // SEND_STRING ("\\");
            return MACRO( D(LALT), T(KP_5), T(KP_8),  U(LALT), END  );
          }
          break;
        case KC_AG_PERIOD:
          if (record->event.pressed) {
            // SEND_STRING ("\\");
            return MACRO( D(LALT), T(KP_4), T(KP_4),  U(LALT), END  );
          }
          break;
        case KC_AG_LPAREN:
          if (record->event.pressed) {
            // SEND_STRING ("\\");
            return MACRO( D(LALT), T(KP_4), T(KP_0),  U(LALT), END  );
          }
          break;
        case KC_AG_RPAREN:
          if (record->event.pressed) {
            // SEND_STRING ("\\");
            return MACRO( D(LALT), T(KP_4), T(KP_1),  U(LALT), END  );
          }
          break;
        case KC_AG_LBRACKET:
          if (record->event.pressed) {
            // SEND_STRING ("\\");
            return MACRO( D(LALT), T(KP_9), T(KP_1),  U(LALT), END  );
          }
          break;
        case KC_AG_RBRACKET:
          if (record->event.pressed) {
            // SEND_STRING ("\\");
            return MACRO( D(LALT), T(KP_9), T(KP_3),  U(LALT), END  );
          }
          break;
        case KC_AG_LCURBRK:
          if (record->event.pressed) {
            // SEND_STRING ("\\");
            return MACRO( D(LALT), T(KP_1), T(KP_2), T(KP_3),  U(LALT), END  );
          }
          break;
        case KC_AG_RCURBRK:
          if (record->event.pressed) {
            // SEND_STRING ("\\");
            return MACRO( D(LALT), T(KP_1), T(KP_2),  T(KP_5), U(LALT), END  );
          }
          break;
        case KC_ALTTAB:
          if (record->event.pressed) {
            return MACRO( D(LALT), D(TAB), END  );
          }
          else {
            return MACRO( U(TAB), END  );
          }
          break;
        case KC_COPY_WBCK:
          if (record->event.pressed) {
            key_timer = timer_read(); // if the key is being pressed, we start the timer.
          }
          else { // this means the key was just released, so we can figure out how long it was pressed for (tap or "held down").
            if (timer_elapsed(key_timer) < 500) { // the number being the threshhold (in ms) we pick for counting something as a tap.
              return MACRO( D(LCTL), T(C), U(LCTL), END  );
            }
            else {
              return MACRO( T(WWW_BACK), END  );
            }
          }
          break;
        case KC_PASTE_WFWD:
          if (record->event.pressed) {
            key_timer = timer_read(); // if the key is being pressed, we start the timer.
          }
          else { // this means the key was just released, so we can figure out how long it was pressed for (tap or "held down").
            if (timer_elapsed(key_timer) < 500) { // the number being the threshhold (in ms) we pick for counting something as a tap.
              return MACRO( D(LCTL), T(V), U(LCTL), END  );
            }
            else {
              return MACRO( T(WWW_FORWARD), END  );
            }
          }
          break;
        case KC_CUT_CLOSE:
          if (record->event.pressed) {
            key_timer = timer_read(); // if the key is being pressed, we start the timer.
          }
          else { // this means the key was just released, so we can figure out how long it was pressed for (tap or "held down").
            if (timer_elapsed(key_timer) < 500) { // the number being the threshhold (in ms) we pick for counting something as a tap.
              return MACRO( D(LCTL), T(X), U(LCTL), END  );
            }
            else {
              return MACRO( D(LALT), T(F4), U(LALT), END  );
            }
          }
          break;
        case KC_MEDIA_NEXT_PREV:
          if (record->event.pressed) {
            key_timer = timer_read(); // if the key is being pressed, we start the timer.
          }
          else { // this means the key was just released, so we can figure out how long it was pressed for (tap or "held down").
            if (timer_elapsed(key_timer) < 500) { // the number being the threshhold (in ms) we pick for counting something as a tap.
              return MACRO( T(MEDIA_NEXT_TRACK), END  );
            }
            else {
              return MACRO( T(MEDIA_NEXT_TRACK), END  );
            }
          }
          break;        
      }
    return MACRO_NONE;
};