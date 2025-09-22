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
 * History
 * 2023-11-04 Added Shift home mod
 *
 */

#include "action.h"
#include "keycodes.h"
#include QMK_KEYBOARD_H
#include "version.h"

#include "sendstring_belgian.h"
//#include "keymap_french_mac_iso.h"
#include "keymap_french_mac_iso.h"
#include "os_detection.h"
#include "print.h"

// Custom variables
int alt_tab_count = 0;
int cmd_tab_count = 0;
enum layers {
    BASE_WIN, // default layer
    NAVNUM_WIN, // navigation and numeric keypad
    FN_WIN,     // Fn keys
    ALTGRFN_WIN, // AltGr and Fn
    BASE_MAC,
    NAVNUM_MAC,
    FN_MAC,
    ALTGRFN_MAC,
};

// Fillers to make layering more clear
// #define _______ KC_TRNS
#define _M_M_M_ KC_TRNS // A simple KC_TRNS that shows were the layer key is and cannot be used on that layer.
#define XXXXXXX KC_NO
#define CTL_X LCTL(KC_X)
#define CTL_C LCTL(KC_C)
#define CTL_V LCTL(KC_V)
#define CMD_X LCMD(KC_X)
#define CMD_C LCMD(KC_C)
#define CMD_V LCMD(KC_V)
#define WIN_SHFT_RGHT LGUI(LSFT(KC_RIGHT))
// https://github.com/qmk/qmk_firmware/blob/master/quantum/keymap_extras/keymap_french_mac_iso.h
#define MAC_FR_AT KC_GRV
#define MAC_FR_HASH LSFT(MAC_FR_AT)
#define MAC_FR_PIPE S(A(KC_L))
#define MAC_FR_BSLS S(A(KC_DOT))
#define MACCY LCMD(KC_GRV)

// one-mod settings
//#define ONESHOT_TAP_TOGGLE 5  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 2000  /* Time (in ms) before the one shot key is released */
#define TAPPING_TERM 200 // 200ms example

enum custom_keycodes {
    ALTTAB = SAFE_RANGE, // SAFE_RANGE is only needed on the first entry : https://github.com/qmk/qmk_firmware/blob/master/docs/custom_quantum_functions.md
    CMDTAB,
    MACHOME,
    MACEND,
    MACDOT,
    MACGRV,
    MACTILDE,
    LBRACKET,
    RBRACKET,
    LPARENT,
    RPARENT,
    RCBRACKET,
    LCBRACKET,
    BCKSLASH,
    COLON,
    FNX,
    GRV,
    TILDE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t fnx_layer_timer;
    if (record->event.pressed) {
        //uprintf("keycode %u pressed\n", keycode);
    }
    switch (keycode) {
      case FNX:
        if(record->event.pressed){
          fnx_layer_timer = timer_read();
          layer_on(FN_WIN);
        } else {
          layer_off(FN_WIN);
          if (timer_elapsed(fnx_layer_timer) < 200) {
            set_oneshot_mods(MOD_LCTL);
          }
        }
        break;
      case KC_ESC:
        if (record->event.pressed) {
          bool rc = true;
          uint8_t mods = 0;
          if ((mods = get_oneshot_mods()) && !has_oneshot_mods_timed_out()) {
            clear_oneshot_mods();
            unregister_mods(mods);
            rc = false;
          }
          if ((mods = get_oneshot_locked_mods())) {
            clear_oneshot_locked_mods();
            unregister_mods(mods);
            rc = false;
          }
          return rc;
        }
        break;
      case ALTTAB:
        if (record->event.pressed) {
          SEND_STRING(SS_DOWN(X_LALT)SS_DOWN(X_TAB));
          alt_tab_count++;
        } else {
          SEND_STRING(SS_UP(X_TAB));
        }
        break;
      case MO(NAVNUM_WIN):
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
        } else {
            // when keycode QMKBEST is released
            if (alt_tab_count > 0) {
              SEND_STRING(SS_UP(X_LALT));
            }
        }
        break;
      case CMDTAB:
        if (record->event.pressed) {
          SEND_STRING(SS_DOWN(X_LCMD)SS_DOWN(X_TAB));
          cmd_tab_count++;
        } else {
          SEND_STRING(SS_UP(X_TAB));
        }
        break;
      case MACHOME:
        if (record->event.pressed) {
            uint8_t mods = get_mods() | get_oneshot_mods();
            uprintf("MACHOME pressed, mods: %02X\n", mods);
            if (mods & MOD_LALT) { // or MOD_RALT if you use right Alt
                uprintf("MACHOME sending cmd-up\n");
                del_mods(MOD_MASK_ALT);         // clear Alt/Opt modifiers
                tap_code16(G(KC_UP));           // send Cmd+Up
                set_mods(mods);                 // restore previous modifiers
                return false; // Prevent any other action
            }
            tap_code16(G(KC_LEFT));
            return false; // Prevent any other action
        }
        break;
      case MACEND:
        if (record->event.pressed) {
            uint8_t mods = get_mods() | get_oneshot_mods();
            if (mods & MOD_LALT) { // or MOD_RALT if you use right Alt
                del_mods(MOD_MASK_ALT);         // clear Alt/Opt modifiers
                tap_code16(G(KC_DOWN)); // send Cmd+Down
                set_mods(mods);                 // restore previous modifiers
                return false; // Prevent any other action
            }
            tap_code16(G(KC_RIGHT));
            return false; // Prevent any other action
        }
        break;
      case MACDOT:
        if (record->event.pressed) {
            SEND_STRING(".");
        }
        break;
      case MO(NAVNUM_MAC):
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
        } else {
            // when keycode QMKBEST is released
            if (cmd_tab_count > 0) {
              SEND_STRING(SS_UP(X_LCMD));
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
      case GRV:
        if (record->event.pressed) {
            uprintf("GRV pressed\n");
            SEND_STRING("`");
        }
        break;
      case MACGRV:
        if (record->event.pressed) {
            uprintf("MACGRV pressed\n");
            tap_code(KC_BSLS);
            tap_code(KC_SPC);
        }
        break;
      case MACTILDE:
        if (record->event.pressed) {
            uprintf("MACTILDE pressed\n");
            tap_code16(A(KC_N));
            tap_code(KC_SPC);
        }
        break;
      case TILDE:
        if (record->event.pressed) {
            SEND_STRING("~ ");
        }
        break;
    }
    return true;
};

/* -------------------------------------- */
/*                WINDOWS                 */
/* ---------------------------------------*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic Windows layer */
[BASE_WIN] = LAYOUT_ergodox_pretty(
  // left hand
  KC_ESCAPE,       KC_1,        KC_2,          KC_3,        KC_4,        KC_5,      KC_QUOTE,             KC_RBRC,      KC_6,    KC_7,        KC_8,        KC_9,        KC_0,             KC_MINS,
  KC_LBRC,         KC_Q,        KC_W,          KC_E,        KC_R,        KC_T,      KC_TAB,               KC_BSPC,      KC_Y,    KC_U,        KC_I,        KC_O,        KC_P,             KC_EQUAL,
  KC_ENTER,        GUI_T(KC_A), ALT_T(KC_S),   CTL_T(KC_D), SFT_T(KC_F), KC_G,                                          KC_H,    SFT_T(KC_J), CTL_T(KC_K), ALT_T(KC_L), GUI_T(KC_SCLN),   KC_ENTER,
  KC_NUBS,         KC_Z,        KC_X,          KC_C,        KC_V,        KC_B,      KC_DELETE,            KC_DELETE,    KC_N,    KC_M,        KC_COMM,     KC_DOT,      KC_SLSH,          KC_QUOTE,
  XXXXXXX,         XXXXXXX,     KC_LWIN,       KC_LALT,     KC_LCTL,                                                             MO(ALTGRFN_WIN), XXXXXXX, KC_RWIN,     XXXXXXX,          XXXXXXX,
                                                                         KC_PRINT_SCREEN,   XXXXXXX,              KC_KP_0,         XXXXXXX,
                                                                                    XXXXXXX,              XXXXXXX,
                                                               MO(NAVNUM_WIN), KC_LSFT, XXXXXXX,              XXXXXXX,      KC_RSFT,    KC_SPC
),
/* Keymap 1: Nav and Num Windows Layer */
[NAVNUM_WIN] = LAYOUT_ergodox_pretty(
  // left hand
  _______,   KC_F1,           KC_F2,   KC_F3,   KC_F4,      KC_F5,         KC_F11,         KC_F12,  KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,           QK_BOOT,
  LBRACKET,  KC_GRAVE,        KC_HOME, KC_UP,   KC_END,     KC_PGUP,       _______,        _______, KC_KP_SLASH,    KC_KP_7,        KC_KP_8,        KC_KP_9,        BCKSLASH,         RBRACKET,
  LPARENT,   SFT_T(KC_ENTER), KC_LEFT, KC_DOWN, KC_RIGHT,   KC_PGDN,                                KC_KP_MINUS,    SFT_T(KC_KP_4), CTL_T(KC_KP_5), ALT_T(KC_KP_6), GUI_T(KC_KP_DOT), RPARENT,
  LCBRACKET, ALTTAB,          CTL_X,   CTL_C,   CTL_V,      WIN_SHFT_RGHT, _______,        _______, COLON,          KC_KP_1,        KC_KP_2,        KC_KP_3,        KC_APPLICATION,   RCBRACKET,
  XXXXXXX,   XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX,                                                            KC_KP_0,        G(KC_COMM),       XXXXXXX,        XXXXXXX,          XXXXXXX,
                                                            QK_BOOT,         XXXXXXX,        KC_KP_1,   XXXXXXX,
                                                                             XXXXXXX,        XXXXXXX,
                                                     _M_M_M_, DF(BASE_MAC),       XXXXXXX,        XXXXXXX, XXXXXXX, _______
),
/* Keymap 2: Fn Windows Layer */
[FN_WIN] = LAYOUT_ergodox_pretty(
  // left hand
  _______,           XXXXXXX,           KC_F10,          KC_F11,           KC_F12,          XXXXXXX,          XXXXXXX,        XXXXXXX, XXXXXXX,        KC_NUHS,        XXXXXXX,        XXXXXXX,        XXXXXXX,          XXXXXXX,
  XXXXXXX,           XXXXXXX,           KC_F7,           KC_F8,            KC_F9,           KC_PSCR,          _______,        _______, XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,          XXXXXXX,
  XXXXXXX,           XXXXXXX,           KC_F4,           KC_F5,            KC_F6,           KC_INSERT,                                 XXXXXXX,        KC_LSFT,        KC_LCTL,        KC_LALT,        KC_LGUI,          XXXXXXX,
  XXXXXXX,           XXXXXXX,           KC_F1,           KC_F2,            KC_F3,           XXXXXXX,          _______,        _______, XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,          XXXXXXX,
  XXXXXXX,           XXXXXXX,           XXXXXXX,         XXXXXXX,          _M_M_M_,                                                                    XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,          XXXXXXX,
                                                                                            QK_BOOT,            XXXXXXX,        KC_KP_2,   _______,
                                                                                                              XXXXXXX,        XXXXXXX,
                                                                                   XXXXXXX, _______,          _______,        _______, _______, _______
),
/* Keymap 3: AltGrFn Windows Layer */
[ALTGRFN_WIN] = LAYOUT_ergodox_pretty(
  // left hand
  _______,           BE_PIPE,           BE_AT,           BE_HASH,          GRV,             TILDE,            XXXXXXX,        XXXXXXX, XXXXXXX,        KC_F10,         KC_F11,         KC_F12,         XXXXXXX,          XXXXXXX,
  XXXXXXX,           XXXXXXX,           XXXXXXX,         BE_EURO,          XXXXXXX,         XXXXXXX,          _______,        _______, KC_PSCR,        KC_F7,          KC_F8,          KC_F9,          XXXXXXX,          XXXXXXX,
  _______,           KC_LGUI,           KC_LALT,         KC_LCTL,          KC_LSFT,         XXXXXXX,                                   KC_INSERT,      KC_F4,          KC_F5,          KC_F6,          XXXXXXX,          _______,
  BE_BSLS,           XXXXXXX,           XXXXXXX,         XXXXXXX,          XXXXXXX,         XXXXXXX,          _______,        _______, XXXXXXX,        KC_F1,          KC_F2,          KC_F3,          TILDE,          GRV,
  XXXXXXX,           XXXXXXX,           XXXXXXX,         XXXXXXX,          XXXXXXX,                                                                    _M_M_M_,        XXXXXXX,        XXXXXXX,        XXXXXXX,          XXXXXXX,
                                                                                            QK_BOOT,          XXXXXXX,        KC_KP_3,    _______,
                                                                                                              XXXXXXX,        XXXXXXX,
                                                                                   XXXXXXX, _______,          _______,        _______, QK_BOOT, _______
),

/* -------------------------------------- */
/*                MAC OS                  */
/* ---------------------------------------*/

/* Keymap 4: Basic Mac layer */
[BASE_MAC] = LAYOUT_ergodox_pretty(
  // left hand
  KC_ESCAPE,       KC_1,        KC_2,          KC_3,        KC_4,        KC_5,      KC_QUOTE,             KC_RBRC,      KC_6,    KC_7,        KC_8,        KC_9,        KC_0,             KC_MINS,
  KC_LBRC,         KC_Q,        KC_W,          KC_E,        KC_R,        KC_T,      KC_TAB,               KC_BSPC,      KC_Y,    KC_U,        KC_I,        KC_O,        KC_P,             KC_EQUAL,
  KC_ENTER,        CTL_T(KC_A), ALT_T(KC_S),   CMD_T(KC_D), SFT_T(KC_F), KC_G,                                KC_H,    SFT_T(KC_J), CMD_T(KC_K), ALT_T(KC_L), CTL_T(KC_SCLN),   KC_ENTER,
  KC_NUBS,         KC_Z,        KC_X,          KC_C,        KC_V,        KC_B,      KC_DELETE,            KC_DELETE,    KC_N,    KC_M,        KC_COMM,     KC_DOT,      KC_SLSH,          KC_QUOTE,
  XXXXXXX,         XXXXXXX,     KC_LCTL,       KC_LOPT,     KC_LCMD,                                                                  MO(ALTGRFN_MAC),        XXXXXXX,XXXXXXX,  XXXXXXX,       XXXXXXX,
                                                                         G(KC_F4),   G(KC_F5),              KC_KP_4,         XXXXXXX,
                                                                                    XXXXXXX,              XXXXXXX,
                                                               MO(NAVNUM_MAC), KC_LSFT, XXXXXXX,              XXXXXXX,      KC_RSFT,    KC_SPC
),
/* Keymap 5: Nav and Num Mac Layer */
[NAVNUM_MAC] = LAYOUT_ergodox_pretty(
  // left hand
  _______,   KC_F1,           KC_F2,   KC_F3,   KC_F4,      KC_F5,         KC_F11,         KC_F12,  KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,           QK_BOOT,
  FR_LBRC,   MACCY,           MACHOME, KC_UP,   MACEND,     KC_PGUP,       G(C(A(KC_LEFT))),        _______, KC_KP_SLASH,    KC_KP_7,        KC_KP_8,        KC_KP_9,        S(A(KC_DOT)),         FR_RBRC,
  FR_LPRN,   SFT_T(KC_ENTER), KC_LEFT, KC_DOWN, KC_RIGHT,   KC_PGDN,                                     KC_KP_MINUS,SFT_T(KC_KP_4), OPT_T(KC_KP_5), CMD_T(KC_KP_6), MACDOT, FR_RPRN,
  FR_LCBR,   CMDTAB,          CMD_X,   CMD_C,   CMD_V,      S(G(C(A(KC_RIGHT)))),    G(C(A(KC_RIGHT))),        _______, KC_KP_DOT,          KC_KP_1,        KC_KP_2,        KC_KP_3,        C(KC_ENTER),    FR_RCBR,
  XXXXXXX,   XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX,                                                            KC_KP_0,        C(G(KC_SPC)),       XXXXXXX,        XXXXXXX,          XXXXXXX,
                                                            QK_BOOT,         XXXXXXX,        KC_KP_5,    XXXXXXX,
                                                                             XXXXXXX,        XXXXXXX,
                                                     _M_M_M_, DF(BASE_WIN),       XXXXXXX,        XXXXXXX, XXXXXXX, _______
),
/* Keymap 6: Fn Mac Layer */
[FN_MAC] = LAYOUT_ergodox_pretty(
  // left hand
  _______,           XXXXXXX,           KC_F10,          KC_F11,           KC_F12,          XXXXXXX,          XXXXXXX,        XXXXXXX, XXXXXXX,        KC_NUHS,        XXXXXXX,        XXXXXXX,        XXXXXXX,          XXXXXXX,
  XXXXXXX,           XXXXXXX,           KC_F7,           KC_F8,            KC_F9,           KC_PSCR,          _______,        _______, XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,          XXXXXXX,
  XXXXXXX,           XXXXXXX,           KC_F4,           KC_F5,            KC_F6,           KC_INSERT,                                         XXXXXXX,        KC_LSFT,        KC_LCMD,    KC_LALT,    KC_LCTL,          XXXXXXX,
  XXXXXXX,           XXXXXXX,           KC_F1,           KC_F2,            KC_F3,           XXXXXXX,          _______,        _______, XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,          XXXXXXX,
  XXXXXXX,           XXXXXXX,           XXXXXXX,         XXXXXXX,          _M_M_M_,                                                                                    XXXXXXX,        XXXXXXX,        XXXXXXX,XXXXXXX,      XXXXXXX,
                                                                                            QK_BOOT,          XXXXXXX,        KC_KP_6,    _______,
                                                                                                              XXXXXXX,        XXXXXXX,
                                                                                   XXXXXXX, _______,          _______,        _______, _______, _______
),
/* Keymap 7: AltGrFn Mac Layer */
[ALTGRFN_MAC] = LAYOUT_ergodox_pretty(
  // left hand
  _______,           FR_PIPE,           FR_AT,           FR_HASH,          MACGRV,         MACTILDE,          XXXXXXX,        XXXXXXX, XXXXXXX,        KC_F10,         KC_F11,         KC_F12,         XXXXXXX,          XXXXXXX,
  XXXXXXX,           XXXXXXX,           XXXXXXX,         A(KC_RBRC),          XXXXXXX,         XXXXXXX,          _______,        _______, KC_PSCR,        KC_F7,          KC_F8,          KC_F9,          XXXXXXX,          XXXXXXX,
  _______,           KC_LCTL,           KC_LALT,         KC_LCMD,          KC_LSFT,         XXXXXXX,                                           KC_INSERT,      KC_F4,          KC_F5,      KC_F6,      XXXXXXX,          _______,
  FR_BSLS,           XXXXXXX,           XXXXXXX,         XXXXXXX,          XXXXXXX,         XXXXXXX,          _______,        _______, XXXXXXX,        KC_F1,          KC_F2,          KC_F3,          MACTILDE,          MACGRV,
  XXXXXXX,           XXXXXXX,           XXXXXXX,         XXXXXXX,          XXXXXXX,                                                                                    _M_M_M_,        XXXXXXX,    XXXXXXX,    XXXXXXX,      XXXXXXX,
                                                                                            QK_BOOT,          XXXXXXX,        KC_KP_7,    _______,
                                                                                                              XXXXXXX,        XXXXXXX,
                                                                                   XXXXXXX, _______,          _______,        _______, QK_BOOT, _______
),

};

// Runs just one time when the keyboard initializes.
void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

bool process_detected_host_os_kb(os_variant_t detected_os) {
    if (!process_detected_host_os_user(detected_os)) {
        return false;
    }
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            layer_move(BASE_MAC);
            break;
        case OS_WINDOWS:
            layer_move(BASE_WIN);
            break;
        case OS_LINUX:
            layer_move(BASE_WIN);
            break;
        case OS_UNSURE:
            layer_move(BASE_WIN);
            break;
    }

    return true;
}

void layer_led_set(uint8_t layer) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  switch (layer) {
      case 0:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #endif
        break;
      case 1:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_3_on();
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
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
        #endif
        break;
      default:
        break;
  }
};

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
  uint8_t layer = get_highest_layer(state | default_layer_state);
  layer_led_set(layer);
  return state;
}

/* // Runs whenever there is a default layer change.
layer_state_t default_layer_state_set_user(layer_state_t state) {
  //uint8_t layer = biton32(state);
  //uint8_t layer = get_highest_layer(state);
  //layer_led_set(layer);
  return state;
} */
