/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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
#include QMK_KEYBOARD_H
#include "features/caps_word.h"

enum layers {
    _COLEMAK_DH = 0,
    _SYM,
    _NAV,
};

// Aliases for readability
#define COLEMAK  TO(_COLEMAK_DH)
#define SYM      OSL(_SYM)
#define NAV      TO(_NAV)

#define LSFT_OSM OSM(MOD_LSFT)
#define RSFT_OSM OSM(MOD_RSFT)

#define LCTL_SPC MT(MOD_LCTL, KC_SPC)
#define LCTL_ENT MT(MOD_LCTL, KC_ENT)
#define LCTL_TAB MT(MOD_LCTL, KC_TAB)
#define RSFT_BSP MT(MOD_RSFT, KC_BSPC)
#define LSFT_SPC MT(MOD_LSFT, KC_SPC)
#define NAV_BSPC LT(_NAV, KC_BSPC)
#define NAV_TAB  LT(_NAV, KC_TAB)
#define NAV_ENT  LT(_NAV, KC_ENT)

#define PREVWIN LSA(KC_TAB)
#define NEXTWIN LALT(KC_TAB)

#define PLS_MIN LSFT(KC_NUBS)

// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).
//

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: Colemak DH
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Esc   |   Q  |   W  |   F  |   P  |   B  |                              |   J  |   L  |   U  |   Y  | ;  : | Del    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  `  ~  |   A  |   R  |   S  |   T  |   G  |                              |   M  |   N  |   E  |   I  |   O  | =  +   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |  LAlt  |   Z  |   X  |   C  |   D  |   V  |LShift| LCmd |  | RCmd |RShift|   K  |   H  | ,  < | .  > | /  ? | RAlt   |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |AppSw/| §  ± | Sym  |BSpace|LCtrl/|  | Nav/ |Space | Sym  | \  | |Scrol/|
 *                        |Enter |      |      |      |Tab   |  |Enter |      |      |      |MdlMse|
 *                        `----------------------------------'  `----------------------------------'
 */
    [_COLEMAK_DH] = LAYOUT(
     KC_ESC  , KC_Q ,  KC_W   ,  KC_F  ,   KC_P ,   KC_B ,                                       KC_J,   KC_L ,  KC_U ,   KC_Y ,KC_SCLN,  KC_DEL,
     KC_GRV  , KC_A ,  KC_R   ,  KC_S  ,   KC_T ,   KC_G ,                                       KC_M,   KC_N ,  KC_E ,   KC_I ,  KC_O ,  KC_EQL,
     KC_LALT , KC_Z ,  KC_X   ,  KC_C  ,   KC_D ,   KC_V ,LSFT_OSM, KC_LCMD,    KC_RCMD,RSFT_OSM,KC_K,   KC_H ,KC_COMM, KC_DOT ,KC_SLSH, KC_RALT,
                                 KC_ENT, KC_NUBS,   SYM  , KC_BSPC,LCTL_TAB,    NAV_ENT,  KC_SPC, SYM, KC_NUHS,KC_BTN3
    ),

/*
 * Nav Layer: Media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |                              |      |      | PgDn | PgUp |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  F6  |  F7  |  F8  |  F9  |  F10 |                              |      |  ←   |   ↓  |   ↑  |   →  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  F11 |  F12 |      |      |      |      |      |  |      |      |      |      | PgDn | PgUp |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |Volum/|M Next|      |      |      |  |      |      |      |      |      |
 *                        |M Play|      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                                     KC_NO  , KC_NO  , KC_PGDN, KC_PGUP, KC_NO  , _______,
      _______, KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,                                     KC_NO  , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______,
      _______, KC_F11 , KC_F12 , KC_NO  , KC_NO  , KC_NO  , _______, _______, _______, _______, KC_NO  , KC_NO  , KC_PGDN, KC_PGUP, KC_NO  , _______,
                                 KC_MPLY, KC_MNXT, _______, _______, _______, COLEMAK, _______, _______, _______, _______
    ),

/*
 * Sym Layer: Numbers and symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  !   |  @   |  #   |  $   |  %   |                              |   ^  |  &   |  *   |  (   |  )   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  ~     |  1   |  2   |  3   |  4   |  5   |                              |   6  |  7   |  8   |  9   |  0   |  +     |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |  {   |  }   |  -   |  _   |      |      |  |      |      |   "  |  '   |  [   |  ]   |  /   |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |  ±   |      |      |      |  |      |      |      |  |   |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYM] = LAYOUT(
     _______ , KC_EXLM,  KC_AT , KC_HASH,  KC_DLR, KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
     KC_TILDE,   KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,                                       KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , KC_PLUS,
     _______ ,   KC_NO, KC_LCBR, KC_RCBR, KC_MINS, KC_UNDS, _______, _______, _______, _______, KC_DQUO, KC_QUOT, KC_LBRC, KC_RBRC, KC_SLSH , _______,
                                 _______, PLS_MIN, _______, _______, _______,   NAV  , _______, _______, KC_PIPE, _______
    ),

// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

/* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/kyria/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap.c
 * For your convenience, here's a copy of those settings so that you can uncomment them if you wish to apply your own modifications.
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

bool is_osm_shift_active = false;
void oneshot_mods_changed_user(uint8_t mods) {
    oled_set_cursor(16, 5);
    if (mods & MOD_MASK_SHIFT) {
        is_osm_shift_active = true;
        oled_write_P(PSTR("SHIFT\n"), false);
    } else {
        is_osm_shift_active = false;
        // let oled_task user handle blanking, otherwise it'll flicker
    }
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // QMK Logo and version information
        // clang-format off
        static const char PROGMEM colemak_logo[] = {
// 'colemak2', 128x32px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 
0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x18, 0x38, 0x38, 0x38, 0x38, 0x38, 0xf8, 0xf8, 0xf0, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 
0xf8, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xf0, 0xfe, 0xff, 0x1f, 0x07, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
0x01, 0x03, 0x03, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0x78, 0x38, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 
0x38, 0x78, 0xf0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xf0, 0xf8, 0x38, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 
0x38, 0xf8, 0xf0, 0xe0, 0x80, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0xf0, 0x30, 0x18, 0x1c, 0x0c, 0xfc, 
0xf8, 0xf0, 0x30, 0x18, 0x1c, 0x0c, 0xfc, 0xf8, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x60, 0x70, 0x38, 
0x18, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x78, 0xf8, 0xf0, 0x80, 0x00, 0x00, 0x00, 0x00, 0xff, 
0xff, 0xff, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0x0e, 0x06, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x07, 0x3f, 0x7f, 0xfc, 0xf0, 0xc0, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x80, 0xc0, 
0xc0, 0xe0, 0x60, 0x00, 0x00, 0x00, 0x3f, 0x7f, 0xff, 0xe0, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x80, 
0xc0, 0xe0, 0xff, 0x7f, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x80, 0x80, 0x80, 
0x80, 0x80, 0x80, 0x00, 0x00, 0x1f, 0x7f, 0xff, 0xe6, 0xc6, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 
0x86, 0xc6, 0xc7, 0xc7, 0x03, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 
0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x60, 0xf8, 0xfc, 0xdc, 
0x8e, 0x06, 0x07, 0x83, 0x83, 0x83, 0xc3, 0xe7, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 
0xff, 0xff, 0x1e, 0x0f, 0x07, 0x03, 0x0f, 0x1f, 0x7c, 0xf8, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 
0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 
0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 
0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 
0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00
        };
        static const char PROGMEM sym_logo[] = {
// 'symbols', 128x32px
0x00, 0x00, 0x00, 0x30, 0xf0, 0xf0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0x10, 0x10, 0x10, 0x10, 0x10, 
0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0xf0, 0xf0, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 
0xf0, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 
0x1c, 0x3c, 0x70, 0xe0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x3f, 0xfe, 0xf0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 
0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
0x7f, 0x7f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 
0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x3f, 0xfe, 0xf0, 0x80, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 
0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x3f, 0x3e, 0x30, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x30, 0x30, 0x30, 0x30, 0x30, 
0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3f, 0x3f, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        };
        static const char PROGMEM nav_logo[] = {
// 'arrows2', 128x32px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 
0xe0, 0xe0, 0xf0, 0xe0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0xf0, 0x70, 0x70, 0x70, 
0x70, 0x70, 0x70, 0x70, 0x70, 0xf0, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xf0, 0x78, 0x38, 
0x38, 0x78, 0xf0, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xe0, 0xf0, 0xe0, 0xe0, 
0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0x70, 0x38, 0x3c, 0x1c, 0x0e, 0x0f, 0x07, 0x03, 0x03, 
0x01, 0x00, 0x00, 0x0f, 0x0f, 0x0f, 0x0e, 0x0e, 0x0e, 0x0e, 0xfe, 0xfe, 0xfc, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xf0, 0xf8, 0xf8, 0x38, 0x3f, 0x3f, 0x3f, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x3f, 0x3f, 0x38, 0xf8, 0xf8, 0xf0, 0x40, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf8, 0x7c, 0x1f, 0x0f, 0x03, 0x01, 0x00, 0x00, 
0x00, 0x00, 0x01, 0x03, 0x0f, 0x1f, 0x7c, 0xf8, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xfc, 0xfe, 0xfe, 0x0e, 0x0e, 0x0e, 0x0e, 0x0f, 0x0f, 0x0f, 0x00, 0x00, 0x01, 
0x03, 0x03, 0x07, 0x0f, 0x0e, 0x1c, 0x3c, 0x38, 0x70, 0xf0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x0e, 0x1c, 0x3c, 0x38, 0x70, 0xf0, 0xe0, 0xc0, 0xc0, 
0x80, 0x00, 0x00, 0xf0, 0xf0, 0xf0, 0x70, 0x70, 0x70, 0x70, 0x7f, 0x7f, 0x3f, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x1f, 0x3e, 0xf8, 0xf0, 0xc0, 0x80, 0x00, 
0x00, 0x00, 0x00, 0x80, 0xc0, 0xf0, 0xf8, 0x3e, 0x1f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x02, 0x0f, 0x1f, 0x1f, 0x1c, 0xfc, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0xfc, 0x1c, 0x1f, 0x1f, 0x0f, 0x02, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x3f, 0x7f, 0x7f, 0x70, 0x70, 0x70, 0x70, 0xf0, 0xf0, 0xf0, 0x00, 0x00, 0x80, 
0xc0, 0xc0, 0xe0, 0xf0, 0x70, 0x38, 0x3c, 0x1c, 0x0e, 0x0f, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 
0x07, 0x07, 0x0f, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0f, 0x1e, 
0x1c, 0x1c, 0x1e, 0x0f, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0f, 0x0f, 0x0e, 0x0e, 0x0e, 0x0e, 
0x0e, 0x0e, 0x0e, 0x0e, 0x0f, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07, 0x0f, 0x07, 0x07, 
0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        };
        // clang-format on

        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _COLEMAK_DH:
                oled_write_P(PSTR("Colemak-DH\n"), false);
                oled_write_raw_P(colemak_logo, sizeof(colemak_logo));
                break;
            case _SYM:
                oled_write_P(PSTR("Symbols\n"), false);
                oled_write_raw_P(sym_logo, sizeof(sym_logo));
                break;
            case _NAV:
                oled_write_P(PSTR("Navgation\n"), false);
                oled_write_raw_P(nav_logo, sizeof(nav_logo));
                break;
            default:
                oled_write_P(PSTR("Undefined\n"), false);
        }
        oled_set_cursor(14, 5);
        if (caps_word_get()) {
            oled_write_P(PSTR("CAPS \n"), false);
        } else if ((keyboard_report->mods & (MOD_BIT(KC_LSFT)))
                    | is_osm_shift_active) {
            oled_write_P(PSTR("SHIFT\n"), false);
        } else {
            oled_write_P(PSTR("     \n"), false);
        }
        oled_set_cursor(10, 5);
        if (get_mods() & (MOD_BIT(KC_LCMD)|MOD_BIT(KC_RCMD))) {
            oled_write_P(PSTR("CMD"), false);
        } else {
            oled_write_P(PSTR("   "), false);
        }
        oled_set_cursor(5, 5);
        if (get_mods() & (MOD_BIT(KC_LCTL)|MOD_BIT(KC_RCTL))) {
            oled_write_P(PSTR("CTRL"), false);
        } else {
            oled_write_P(PSTR("    "), false);
        }
        oled_set_cursor(1, 5);
        if (get_mods() & (MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))) {
            oled_write_P(PSTR("ALT"), false);
        } else {
            oled_write_P(PSTR("   "), false);
        }
    } else {
        // clang-format off
        static const char PROGMEM kyria_logo[] = {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
            0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
            0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
        };
        // clang-format on
        oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
    }
    return false;
}
#endif

#define RGB_INFERNO 255,  66,   0
#define RGB_GRAPE   191,   0, 255

#define HSV_C64BLUE 160, 255, 255
#define HSV_YAMGOLD  28, 255, 255
#define HSV_HEATWAV  21, 255, 255
#define HSV_VIVORNG  16, 255, 255
#define HSV_PHASER   13, 255, 255
#define HSV_MAGMA     8, 255, 255
#define HSV_GRAPE   202, 255, 255

void rgb_matrix_set_color_hsv(unsigned char index, unsigned char h, unsigned char s, unsigned char v) {
    unsigned char region, remainder, p, q, t, r, g, b;
    if (s == 0) {
        r = v; g = v; b = v;
    } else {
        region = h / 43;
        remainder = (h - (region * 43)) * 6;

        p = (v * (255 - s)) >> 8;
        q = (v * (255 - ((s * remainder) >> 8))) >> 8;
        t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

        switch (region)
        {
            case 0:
                r = v; g = t; b = p;
                break;
            case 1:
                r = q; g = v; b = p;
                break;
            case 2:;
                r = p; g = v; b = t;
                break;
            case 3:
                r = p; g = q; b = v;
                break;
            case 4:
                r = t; g = p; b = v;
                break;
            default:
                r = v; g = p; b = q;
        }
    }
    rgb_matrix_set_color(index, r, g, b);
}

void rgb_matrix_set_color_hsv_pair(unsigned char index, unsigned char h, unsigned char s, unsigned char v) {
    rgb_matrix_set_color_hsv(index,    h, s, v);
    rgb_matrix_set_color_hsv(index+31, h, s, v);
}

void rgb_matrix_set_color_hsv_gradient(unsigned char h, unsigned char s, unsigned char v, signed char width) {
    unsigned char start_h = h - width/2;
    /* underglow - mirrored */
    rgb_matrix_set_color_hsv_pair( 0, start_h + width*6.2/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 1, start_h + width*9.4/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 2, start_h + width*13.6/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 3, start_h + width*10.4/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 4, start_h + width*6.2/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 5, start_h + width*1.3/15.1, s, v );
    /* backlight */
    rgb_matrix_set_color_hsv_pair( 11, start_h + width*0, s, v );
    rgb_matrix_set_color_hsv_pair( 6,  start_h + width*0.7/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 12, start_h + width*2.6/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 7,  start_h + width*2.9/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 13, start_h + width*5.1/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 8,  start_h + width*5.2/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 19, start_h + width*5.8/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 25, start_h + width*6.5/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 14, start_h + width*7/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 9,  start_h + width*7.4/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 20, start_h + width*7.7/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 26, start_h + width*8.4/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 15, start_h + width*9/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 10, start_h + width*9.1/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 21, start_h + width*9.7/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 27, start_h + width*10.4/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 16, start_h + width*11/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 22, start_h + width*11.3/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 28, start_h + width*11.9/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 17, start_h + width*12/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 23, start_h + width*12.6/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 29, start_h + width*13.3/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 18, start_h + width*13.6/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 24, start_h + width*14.3/15.1, s, v );
    rgb_matrix_set_color_hsv_pair( 30, start_h + width*15.1/15.1, s, v );
}

bool rgb_matrix_indicators_user(void) {
    uint8_t layer = biton32(layer_state);
    switch (layer) {
        case 0:
            //rgb_matrix_set_color_all(RGB_CYAN);
            rgb_matrix_set_color_hsv_gradient(HSV_C64BLUE, -40);
            break;
        case 1:
            //rgb_matrix_set_color_all(RGB_INFERNO);
            rgb_matrix_set_color_hsv_gradient(HSV_PHASER, 10);
            break;
        case 2:
            //rgb_matrix_set_color_all(RGB_GRAPE);
            rgb_matrix_set_color_hsv_gradient(HSV_GRAPE, -30);
            break;
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_caps_word(keycode, record)) { return false; }
    return true;
}

#ifdef ENCODER_ENABLE
bool is_alt_tab_active = false;
bool is_alt_shift_tab_active = false;
uint16_t alt_tab_timer = 0;

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (get_highest_layer(layer_state|default_layer_state) == _NAV) {
						if (clockwise) {
								tap_code(KC_VOLD);
						} else {
								tap_code(KC_VOLU);
						}
        } else {
            // Task switcher
            if (!clockwise) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    is_alt_shift_tab_active = false;
                    unregister_code(KC_LSFT);
                    register_code(KC_LCMD);
                }
                alt_tab_timer = timer_read();
                tap_code(KC_TAB);
            } else {
                if (!is_alt_shift_tab_active) {
                    is_alt_shift_tab_active = true;
                    is_alt_tab_active = false;
                    register_code(KC_LCMD);
                    register_code(KC_LSFT);
                }
                alt_tab_timer = timer_read();
                tap_code(KC_TAB);
            }
        }
    } else if (index == 1) {
        // Mouse scroll, 1x speed
        if (clockwise) {
            tap_code(KC_WH_U);
        } else {
            tap_code(KC_WH_D);
        }
    }
    return false;
}
#endif

void matrix_scan_user(void) {
    if (is_alt_tab_active || is_alt_shift_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LCMD);
            if (is_alt_shift_tab_active)
                unregister_code(KC_LSFT);
            is_alt_tab_active = false;
            is_alt_shift_tab_active = false;
        }
    }
}
