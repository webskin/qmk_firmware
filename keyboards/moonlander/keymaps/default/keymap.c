/*
Copyright 2018 Jack Humbert <jack.humb@gmail.com>

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT_moonlander(
  RGB_MOD, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_BSPC,
  KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_DEL,
  KC_ESC,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
  KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_ENT,
  MO(1),   KC_LCTL,KC_LALT,KC_LGUI,KC_RALT,                                KC_RALT,KC_LGUI,KC_LALT,KC_LCTL,MO(2),
  KC_BSPC, KC_SPC, KC_ENT, KC_DEL,                                                 KC_DEL, KC_ENT,KC_SPC, KC_BSPC
),

[1] = LAYOUT_moonlander(
  RGB_MOD, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_BSPC,
  KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_DEL,
  KC_ESC,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
  KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,
  MO(1),  KC_LCTL, KC_LALT,KC_LGUI,KC_RALT,                                KC_RALT,KC_LGUI,KC_LALT,KC_LCTL,MO(2),
  KC_BSPC, KC_SPC, KC_ENT, KC_DEL,                                                 KC_DEL, KC_ENT,KC_SPC, KC_BSPC

),

[1] = LAYOUT_moonlander(
  RGB_MOD, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_BSPC,
  KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_DEL,
  KC_ESC,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
  KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,
  MO(1),KC_LCTL,KC_LALT,KC_LGUI,KC_RALT,                                   KC_RALT,KC_LGUI,KC_LALT,KC_LCTL,MO(2),
  KC_BSPC, KC_SPC, KC_ENT, KC_DEL,                                                 KC_DEL, KC_ENT,KC_SPC, KC_BSPC
)

};
