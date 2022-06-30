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

// Note: LAlt/Enter (ALT_ENT) is not the same thing as the keyboard shortcut Alt+Enter.
// The notation `mod/tap` denotes a key that activates the modifier `mod` when held down, and
// produces the key `tap` when tapped (i.e. pressed and released).

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: Colemak DH
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  Esc   |   Q  |   W  |   F  |   P  |   B  |                              |   J  |   L  |   U  |   Y  | ;  : | Del    |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  =  +  |   A  |   R  |   S  |   T  |   G  |                              |   M  |   N  |   E  |   I  |   O  | Enter  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |LAlt / (|   Z  |   X  |   C  |   D  |   V  |LShift| LCmd |  | RCmd |RShift|   K  |   H  | ,  < | .  > | /  ? |RAlt / )|
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |AppSw/| \  | | Sym  |BSpace|LCtrl/|  | Nav/ |Space | Sym  | `  ~ |Scrol/|
 *                        |Enter |      |      |      |Tab   |  |Enter |      |      |      |MdlMse|
 *                        `----------------------------------'  `----------------------------------'
 */
    [_COLEMAK_DH] = LAYOUT(
     KC_ESC  , KC_Q ,  KC_W   ,  KC_F  ,   KC_P ,   KC_B ,                                       KC_J,   KC_L ,  KC_U ,   KC_Y ,KC_SCLN,  KC_DEL,
     KC_EQL  , KC_A ,  KC_R   ,  KC_S  ,   KC_T ,   KC_G ,                                       KC_M,   KC_N ,  KC_E ,   KC_I ,  KC_O ,  KC_ENT,
     KC_LAPO , KC_Z ,  KC_X   ,  KC_C  ,   KC_D ,   KC_V ,LSFT_OSM, KC_LCMD,    KC_RCMD,RSFT_OSM,KC_K,   KC_H ,KC_COMM, KC_DOT ,KC_SLSH, KC_RAPC,
                                 KC_ENT, KC_BSLS,   SYM  , KC_BSPC,LCTL_TAB,    NAV_ENT,  KC_SPC, SYM, KC_GRV ,KC_BTN3
    ),

/*
 * Nav Layer: Media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |      |      |      |                              |      |      | PgDn | PgUp |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      |  ←   |   ↓  |   ↑  |   →  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |M Prev|      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |Volum/|M Next|      |      |      |  |      |      |      |      |      |
 *                        |M Play|      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAV] = LAYOUT(
      _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                                     KC_NO  , KC_NO  , KC_PGDN, KC_PGUP, KC_NO  , _______,
      _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                                     KC_NO  , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______,
      _______, KC_MPRV, KC_NO  , KC_NO  , KC_NO  , KC_NO  , _______, _______, _______, _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , _______,
                                 KC_MPLY, KC_MNXT, _______, _______, _______, COLEMAK, _______, _______, _______, _______
    ),

/*
 * Sym Layer: Numbers and symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  !   |  @   |  #   |  $   |  %   |                              |   ^  |  &   |  *   |  (   |  )   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  1   |  2   |  3   |  4   |  5   |                              |   6  |  7   |  8   |  9   |  0   |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |  [   |  ]   |  -   |  _   |      |      |  |      |      |   "  |  '   |  {   |  }   |  /   |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |  |   |      |      |      |  |      |      |      |  ~   |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYM] = LAYOUT(
     _______ , KC_EXLM,  KC_AT , KC_HASH,  KC_DLR, KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
     _______ ,   KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,                                       KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , _______,
     _______ ,   KC_NO, KC_LBRC, KC_RBRC, KC_MINS, KC_UNDS, _______, _______, _______, _______, KC_DQUO, KC_QUOT, KC_LCBR, KC_RCBR, KC_SLSH , _______,
                                 _______, KC_PIPE, _______, _______, _______,   NAV  , _______, _______,KC_TILDE, _______
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
        oled_set_cursor(16, 5);
        if (caps_word_get()) {
            oled_write_P(PSTR("CAPS \n"), false);
        } else if ((keyboard_report->mods & (MOD_BIT(KC_LSFT)))
                    | is_osm_shift_active) {
            oled_write_P(PSTR("SHIFT\n"), false);
        } else {
            oled_write_P(PSTR("     \n"), false);
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

#define HSV_INFERNO  11, 255, 255
#define HSV_GRAPE   202, 255, 255

const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_CYAN}
);
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_INFERNO}
);
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_GRAPE}
);
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer1_layer,    //
    my_layer2_layer,    // Overrides other layers
    my_layer3_layer     // Overrides other layers
);
void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
    rgblight_enable_noeeprom(); // Enables RGB, without saving settings
    rgblight_sethsv_noeeprom(HSV_CYAN);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _COLEMAK_DH));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _SYM));
    rgblight_set_layer_state(2, layer_state_cmp(state, _NAV));
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_caps_word(keycode, record)) { return false; }
    return true;
}

bool is_alt_tab_active = false;
bool is_alt_shift_tab_active = false;
uint16_t alt_tab_timer = 0;

#ifdef ENCODER_ENABLE
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
                    unregister_code(KC_LSHIFT);
                    register_code(KC_LCMD);
                }
                alt_tab_timer = timer_read();
                tap_code(KC_TAB);
            } else {
                if (!is_alt_shift_tab_active) {
                    is_alt_shift_tab_active = true;
                    is_alt_tab_active = false;
                    register_code(KC_LCMD);
                    register_code(KC_LSHIFT);
                }
                alt_tab_timer = timer_read();
                tap_code(KC_TAB);
            }
        }
    } else if (index == 1) {
        // Mouse scroll, 3x speed
        if (clockwise) {
            tap_code(KC_WH_U);
            tap_code(KC_WH_U);
            tap_code(KC_WH_U);
        } else {
            tap_code(KC_WH_D);
            tap_code(KC_WH_D);
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
                unregister_code(KC_LSHIFT);
            is_alt_tab_active = false;
            is_alt_shift_tab_active = false;
        }
    }
}
