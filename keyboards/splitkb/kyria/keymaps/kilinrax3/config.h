/* Copyright 2022 Thomas Baart <thomas@splitkb.com>
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

#pragma once

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_TIMEOUT 300000
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#    define RGB_TRIGGER_ON_KEYDOWN
#endif

#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_MODS_ENABLE

#ifdef OLED_ENABLE
#    define OLED_TIMEOUT 300000
#    define OLED_FADE_OUT
#    define OLED_FADE_OUT_INTERVAL 10
#endif

#define LED_CAPS_LOCK_PIN 24
#define LED_PIN_ON_STATE 0

// Lets you roll mod-tap keys
#define IGNORE_MOD_TAP_INTERRUPT
