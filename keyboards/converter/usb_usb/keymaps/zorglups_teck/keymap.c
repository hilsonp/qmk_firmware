/*
Copyright 2017 Balz Guenat <balz.guenat@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "version.h"

#include "sendstring_belgian.h"

// Custom variables
int alt_tab_count = 0;
enum layers {
    BASE, // default layer
    NAVNUM, // navigation and numeric keypad
    FN,     // Fn keys
    MDIA,  // media keys
};

// Fillers to make layering more clear
//#define _______ KC_TRNS
#define _M_M_M_ KC_TRNS // A simple KC_TRNS that shows were the layer key is and cannot be used on that layer.
#define XXXXXXX KC_NO
#define CTL_X LCTL(KC_X)
#define CTL_C LCTL(KC_C)
#define CTL_V LCTL(KC_V)
#define WIN_SHFT_RGHT LGUI(LSFT(KC_RIGHT))

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

/*
 * This mapping is a bit weird.
 * The first asciiart shows the virtual keyboard emulated by the usb_usb converter
 * The second asciiart shows the keys sent by the TECK (using the custom firmware)
 * The layout express in the virtual keyboard what should be sent instead of the TECK code.
 * This is therefore a 2 stages mapping.
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: plain Qwerty without layer switching
     *         ,---------------. ,---------------. ,---------------.
     *         |F13|F14|F15|F16| |F17|F18|F19|F20| |F21|F22|F23|F24|
     * ,---.   |---------------| |---------------| |---------------| ,-----------. ,---------------. ,-------.
     * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau| |VDn|VUp|Mut|Pwr| | Help  |
     * `---'   `---------------' `---------------' `---------------' `-----------' `---------------' `-------'
     * ,-----------------------------------------------------------. ,-----------. ,---------------. ,-------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|JPY|Bsp| |Ins|Hom|PgU| |NmL|  /|  *|  -| |Stp|Agn|
     * |-----------------------------------------------------------| |-----------| |---------------| |-------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  | |Del|End|PgD| |  7|  8|  9|  +| |Mnu|Und|
     * |-----------------------------------------------------------| `-----------' |---------------| |-------|
     * |CapsL |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  :|  #|Retn|               |  4|  5|  6|KP,| |Sel|Cpy|
     * |-----------------------------------------------------------|     ,---.     |---------------| |-------|
     * |Shft|  <|  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /| RO|Shift |     |Up |     |  1|  2|  3|KP=| |Exe|Pst|
     * |-----------------------------------------------------------| ,-----------. |---------------| |-------|
     * |Ctl|Gui|Alt|MHEN|HNJ| Space  |H/E|HENK|KANA|Alt|Gui|App|Ctl| |Lef|Dow|Rig| |  0    |  .|Ent| |Fnd|Cut|
     * `-----------------------------------------------------------' `-----------' `---------------' `-------'
     *
     * ,---.   ,---------------. ,---------------. ,---------------. ,---.
     * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| | K9|
     * `---'   `---------------' `---------------' `---------------' `---
     *                             |-----------|
     *                             |CpL|PrS|Ins|
     *                             `-----------'
     *    ,--------------------------------------------------------------.
     *    | K7|  `|  1|  2|  3|  4|  5|    K8|  6|  7|  8|  9|  0|  -|  =|
     *    |--------------------------------------------------------------|
     *    |  \|  /|  Q|  W|  E|  R|  T|   Tab|  Y|  U|  I|  O|  P|  [|  ]|
     *    |--------------------------------------------------------------|
     *    |  Enter|  A|  S|  D|  F|  G|    BS|  H|  J|  K|  L|  ;| KEnter|
     *    |--------------------------------------------------------------|
     *    |  LCtrl|  Z|  X|  C|  V|  B|   Del|  N|  M|  ,|  .|  '|  RCtrl|
     *    |--------------------------------------------------------------|
     *    |   |   |   |PgU|L  |   |   |      |   |   |R  | K+|   |   |   |
     *    | K1| K2| K3|---|Alt|     K0|RShift|  Space|Alt|---| K4| K5| K6|
     *    |   |   |   |PgD|   |   |   |      |   |   |   | K-|   |   |   |
     *    |--------------------------------------------------------------|
     *
     * BASE :
     * - K7 => KC_ESCAPE
     * -
     *
     */
//  [0] = LAYOUT_all(
//                    KC_F13,  KC_F14,  KC_F15,  KC_F16, KC_F17, KC_F18, KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,
//  KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  KC_F6,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,               KC_PSCR, KC_SLCK, KC_PAUS,    KC_VOLD, KC_VOLU, KC_MUTE, KC_PWR,     KC_HELP,
//  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_JYEN, KC_BSPC,     KC_INS,  KC_HOME, KC_PGUP,    KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,    KC_STOP, KC_AGIN,
//  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSLS,     KC_DEL,  KC_END,  KC_PGDN,    KC_P7,   KC_P8,   KC_P9,   KC_PPLS,    KC_MENU, KC_UNDO,
//  KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_NUHS, KC_ENT,                                    KC_P4,   KC_P5,   KC_P6,   KC_PCMM,    KC_SLCT, KC_COPY,
//  KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RO,   KC_RSFT,              KC_UP,               KC_P1,   KC_P2,   KC_P3,   KC_PEQL,    KC_EXEC, KC_PSTE,
//  KC_LCTL, KC_LGUI, KC_LALT, KC_MHEN, KC_HANJ,         KC_SPC,         KC_HAEN, KC_HENK, KC_KANA, KC_RALT, KC_RGUI, KC_APP,  KC_RCTL,     KC_LEFT, KC_DOWN, KC_RGHT,    KC_P0,            KC_PDOT, KC_PENT,    KC_FIND, KC_CUT
//  ),
        [BASE] = LAYOUT_all(
                        _______,  _______,  _______, _______, _______,  _______,  _______, _______,  _______, _______, _______, _______,
    _______,            _______,  _______,  _______, _______, _______,  _______,  _______, _______,  _______, _______, _______, _______,              _______,_______,_______,    _______,_______,_______,_______,    _______,
    _______,  _______,  _______,  _______,  _______, _______, _______,  _______,  _______, _______,  _______, _______, _______, _______, _______,     _______,_______,_______,    _______,_______,_______,_______,    _______,_______,
    _______,  _______,  _______,  _______,  _______, _______, _______,  _______,  _______, _______,  _______, _______, _______,          _______,     _______,_______,_______,       KC_A,_______,_______,_______,    _______,_______,
    _______,  _______,  _______,  _______,  _______, _______, _______,  _______,  _______, _______,  _______, _______,          _______, _______,                                 _______,_______,_______,_______,    _______,_______,
    _______,  _______,  _______,  _______,  _______, _______, _______,  _______,  _______, _______,  _______, _______,          _______, _______,             _______,            _______,_______,_______,_______,    _______,_______,
    _______,  _______,  _______,  _______,  _______,          _______,            _______, _______,  _______, _______, _______, _______, _______,     _______,_______,_______,    _______,        _______,_______,    _______,_______
    ),
    [NAVNUM] = LAYOUT_all(
                        _______,  _______,  _______, _______, _______,  _______,  _______, _______,  _______, _______, _______, _______,
    _______,            _______,  _______,  _______, _______, _______,  _______,  _______, _______,  _______, _______, _______, _______,              _______,_______,_______,    _______,_______,_______,_______,    _______,
    _______,  _______,  _______,  _______,  _______, _______, _______,  _______,  _______, _______,  _______, _______, _______, _______, _______,     _______,_______,_______,    _______,_______,_______,_______,    _______,_______,
    _______,  _______,  _______,  _______,  _______, _______, _______,  _______,  _______, _______,  _______, _______, _______,          _______,     _______,_______,_______,    _______,_______,_______,_______,    _______,_______,
    _______,  _______,  _______,  _______,  _______, _______, _______,  _______,  _______, _______,  _______, _______,          _______, _______,                                 _______,_______,_______,_______,    _______,_______,
    _______,  _______,  _______,  _______,  _______, _______, _______,  _______,  _______, _______,  _______, _______,          _______, _______,             _______,            _______,_______,_______,_______,    _______,_______,
    _______,  _______,  _______,  _______,  _______,          _______,            _______, _______,  _______, _______, _______, _______, _______,     _______,_______,_______,    _______,        _______,_______,    _______,_______
    ),
    [FN] = LAYOUT_all(
                        _______,  _______,  _______, _______, _______,  _______,  _______, _______,  _______, _______, _______, _______,
    _______,            _______,  _______,  _______, _______, _______,  _______,  _______, _______,  _______, _______, _______, _______,              _______,_______,_______,    _______,_______,_______,_______,    _______,
    _______,  _______,  _______,  _______,  _______, _______, _______,  _______,  _______, _______,  _______, _______, _______, _______, _______,     _______,_______,_______,    _______,_______,_______,_______,    _______,_______,
    _______,  _______,  _______,  _______,  _______, _______, _______,  _______,  _______, _______,  _______, _______, _______,          _______,     _______,_______,_______,    _______,_______,_______,_______,    _______,_______,
    _______,  _______,  _______,  _______,  _______, _______, _______,  _______,  _______, _______,  _______, _______,          _______, _______,                                 _______,_______,_______,_______,    _______,_______,
    _______,  _______,  _______,  _______,  _______, _______, _______,  _______,  _______, _______,  _______, _______,          _______, _______,             _______,            _______,_______,_______,_______,    _______,_______,
    _______,  _______,  _______,  _______,  _______,          _______,            _______, _______,  _______, _______, _______, _______, _______,     _______,_______,_______,    _______,        _______,_______,    _______,_______
    ),
};
