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

#include "moonlander.h"

bool mcp23018_leds[3] = {0, 0, 0};

void matrix_init_kb(void) {
  setPinOutput(B5);
  setPinOutput(B4);
  setPinOutput(B3);

  writePinLow(B5);
  writePinLow(B4);
  writePinLow(B3);

  mcp23018_leds[0] = 0; // blue
  mcp23018_leds[1] = 0; // green
  mcp23018_leds[2] = 0; // red

  eeconfig_init();
}

void matrix_scan_kb(void) {

}

uint32_t layer_state_set_kb(uint32_t state) {
  ML_LED_1(0);
  ML_LED_2(0);
  ML_LED_3(0);
  ML_LED_4(0);
  ML_LED_5(0);
  ML_LED_6(0);

  uint8_t layer = biton32(state);
  switch (layer) {
      case 0:
        break;
      case 1:
        ML_LED_1(1);
        ML_LED_4(1);
        break;
      case 2:
        ML_LED_2(1);
        ML_LED_5(1);
        break;
      case 3:
        ML_LED_3(1);
        break;
      case 4:
        ML_LED_4(1);
        break;
      case 5:
        ML_LED_5(1);
        break;
      case 6:
        ML_LED_6(1);
        break;
      default:
        break;
    }

  return state;
}

const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |      G location
 *   |  |      |      B location
 *   |  |      |      | */
    {0, C3_2,  C1_1,  C4_2}, // 1
    {0, C2_2,  C1_2,  C4_3},
    {0, C2_3,  C1_3,  C3_3},
    {0, C2_4,  C1_4,  C3_4},
    {0, C2_5,  C1_5,  C3_5},
    {0, C2_6,  C1_6,  C3_6},
    {0, C2_7,  C1_7,  C3_7},
    {0, C2_8,  C1_8,  C3_8},
    {0, C3_1,  C2_1,  C4_1},

    {0, C7_8,  C6_8,  C8_8}, // 10
    {0, C7_7,  C6_7,  C9_8},
    {0, C8_7,  C6_6,  C9_7},
    {0, C8_6,  C7_6,  C9_6},
    {0, C8_5,  C7_5,  C9_5},
    {0, C8_4,  C7_4,  C9_4},
    {0, C8_3,  C7_3,  C9_3},
    {0, C8_2,  C7_2,  C9_2},
    {0, C8_1,  C7_1,  C9_1},

    {0, C3_10,  C1_9,   C4_10}, // 19
    {0, C2_10,  C1_10,  C4_11},
    {0, C2_11,  C1_11,  C3_11},
    {0, C2_12,  C1_12,  C3_12},
    {0, C2_13,  C1_13,  C3_13},
    {0, C2_14,  C1_14,  C3_14},
    {0, C2_15,  C1_15,  C3_15},
    {0, C2_16,  C1_16,  C3_16},
    {0, C3_9,   C2_9,   C4_9},

    {0, C7_16,  C6_16,  C8_16}, // 28
    {0, C7_15,  C6_15,  C9_16},
    {0, C8_15,  C6_14,  C9_15},
    {0, C8_10,  C7_10,  C9_10},
    {0, C8_9,   C7_9,   C9_9},
    {0, C8_11,  C7_11,  C9_11},
    {0, C8_12,  C7_12,  C9_12},
    {0, C8_13,  C7_13,  C9_13},
//    {0, C8_14,  C7_14,  C9_4}

    {1, C3_2,  C1_1,  C4_2}, // 1
    {1, C2_2,  C1_2,  C4_3},
    {1, C2_3,  C1_3,  C3_3},
    {1, C2_4,  C1_4,  C3_4},
    {1, C2_5,  C1_5,  C3_5},
    {1, C2_6,  C1_6,  C3_6},
    {1, C2_7,  C1_7,  C3_7},
    {1, C2_8,  C1_8,  C3_8},
    {1, C3_1,  C2_1,  C4_1},

    {1, C7_8,  C6_8,  C8_8}, // 10
    {1, C7_7,  C6_7,  C9_8},
    {1, C8_7,  C6_6,  C9_7},
    {1, C8_6,  C7_6,  C9_6},
    {1, C8_5,  C7_5,  C9_5},
    {1, C8_4,  C7_4,  C9_4},
    {1, C8_3,  C7_3,  C9_3},
    {1, C8_2,  C7_2,  C9_2},
    {1, C8_1,  C7_1,  C9_1},

    {1, C3_10,  C1_9,   C4_10}, // 19
    {1, C2_10,  C1_10,  C4_11},
    {1, C2_11,  C1_11,  C3_11},
    {1, C2_12,  C1_12,  C3_12},
    {1, C2_13,  C1_13,  C3_13},
    {1, C2_14,  C1_14,  C3_14},
    {1, C2_15,  C1_15,  C3_15},
    {1, C2_16,  C1_16,  C3_16},
    {1, C3_9,   C2_9,   C4_9},

    {1, C7_16,  C6_16,  C8_16}, // 28
    {1, C7_15,  C6_15,  C9_16},
    {1, C8_15,  C6_14,  C9_15},
    {1, C8_10,  C7_10,  C9_10},
    {1, C8_9,   C7_9,   C9_9},
    {1, C8_11,  C7_11,  C9_11},
    {1, C8_12,  C7_12,  C9_12},
    {1, C8_13,  C7_13,  C9_13},

};

led_config_t g_led_config = { {
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    {  28,  33,  38,  43,  47, NO_LED },
    {  27,  32,  37,  42,  46, NO_LED },
    {  26,  31,  36,  41,  45, NO_LED },
    {  25,  30,  35,  40,  44, NO_LED },
    {  24,  29,  34,  39, NO_LED, NO_LED },
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    {   0,   5,  10,  15, NO_LED, NO_LED },
    {   1,   6,  11,  16,  20, NO_LED },
    {   2,   7,  12,  17,  21, NO_LED },
    {   3,   8,  13,  18,  22, NO_LED },
    {   4,   9,  14,  19,  23, NO_LED },
}, {
    { 137,   0 }, { 154,   0 }, { 172,   0 }, { 189,   0 }, { 206,   0 }, { 137,  12 },
    { 154,  12 }, { 172,  12 }, { 189,  12 }, { 206,  12 }, { 137,  25 }, { 154,  25 },
    { 172,  25 }, { 189,  25 }, { 206,  25 }, { 137,  38 }, { 154,  38 }, { 172,  38 },
    { 189,  38 }, { 206,  38 }, { 154,  51 }, { 172,  51 }, { 189,  51 }, { 206,  51 },
    {  86,   0 }, {  68,   0 }, {  51,   0 }, {  34,   0 }, {  17,   0 }, {  86,  12 },
    {  68,  12 }, {  51,  12 }, {  34,  12 }, {  17,  12 }, {  86,  25 }, {  68,  25 },
    {  51,  25 }, {  34,  25 }, {  17,  25 }, {  86,  38 }, {  68,  38 }, {  51,  38 },
    {  34,  38 }, {  17,  38 }, {  68,  51 }, {  51,  51 }, {  34,  51 }, {  17,  51 }
}, {
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 1, 1, 1, 1,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 1, 1, 1, 1
} };
