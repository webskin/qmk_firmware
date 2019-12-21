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

void keyboard_pre_init_kb(void) {
    setPinOutput(B5);
    setPinOutput(B4);
    setPinOutput(B3);

    writePinLow(B5);
    writePinLow(B4);
    writePinLow(B3);

    /* the array is initialized to 0, no need to re-set it here */
    // mcp23018_leds[0] = 0;  // blue
    // mcp23018_leds[1] = 0;  // green
    // mcp23018_leds[2] = 0;  // red

    keyboard_pre_init_user();
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    ML_LED_1(0);
    ML_LED_2(0);
    ML_LED_3(0);
    ML_LED_4(0);
    ML_LED_5(0);
    ML_LED_6(0);

    state = layer_state_set_user(state);
    uint8_t layer = get_highest_layer(state);
    switch (layer) {
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

// clang-format off
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
    {0, C8_14,  C7_14,  C9_14},

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
    {1, C8_14,  C7_14,  C9_14},

};

led_config_t g_led_config = { {
    {   0,  5, 10, 15, 20, 25, 29 },
    {   1,  6, 11, 16, 21, 26, 30 },
    {   2,  7, 12, 17, 22, 27, 31 },
    {   3,  8, 13, 18, 23, 28, NO_LED },
    {   4,  9, 14, 19, 24, NO_LED, NO_LED },
    {  32, 33, 34, 35, NO_LED, NO_LED, NO_LED },
    {  65, 61, 56, 51, 46, 41, 36 },
    {  66, 62, 57, 52, 47, 42, 37 },
    {  67, 63, 58, 53, 48, 43, 38 },
    {  NO_LED, 64, 59, 54, 49, 44, 39 },
    {  NO_LED, NO_LED, 60, 55, 50, 45, 40 },
    {  NO_LED, NO_LED, NO_LED, 71, 70, 69, 68 },
}, {
    {   0,   0 }, {   0,  12 }, {   0,  25 }, {   0,  38 }, {   0,  51 },
    {  17,   0 }, {  17,  12 }, {  17,  25 }, {  17,  38 }, {  17,  51 },
    {  34,   0 }, {  34,  12 }, {  34,  25 }, {  34,  38 }, {  34,  51 },
    {  51,   0 }, {  51,  12 }, {  51,  25 }, {  51,  38 }, {  51,  51 },
    {  68,   0 }, {  68,  12 }, {  68,  25 }, {  68,  38 }, {  68,  51 },
    {  86,   0 }, {  86,  12 }, {  86,  25 }, {  86,  38 },
    { 105,   0 }, { 105,  12 }, { 105,  25 },
    {  90,  55 }, { 105,  68 }, { 116,  86 }, { 116, 59 },

    { 250,   0 }, { 250,  12 }, { 250,  25 }, { 250,  38 }, { 250,  51 },
    { 233,   0 }, { 233,  12 }, { 233,  25 }, { 233,  38 }, { 233,  51 },
    { 216,   0 }, { 216,  12 }, { 216,  25 }, { 216,  38 }, { 216,  51 },
    { 198,   0 }, { 198,  12 }, { 198,  25 }, { 198,  38 }, { 198,  51 },
    { 181,   0 }, { 181,  12 }, { 181,  25 }, { 181,  38 }, { 181,  51 },
    { 163,   0 }, { 163,  12 }, { 163,  25 }, { 163,  38 },
    { 146,   0 }, { 146,  12 }, { 146,  25 },
    { 161,  55 }, { 161,  68 }, { 146,  86 }, { 131, 59 }

}, {
    1, 1, 1, 1, 1, 4,
    4, 4, 4, 1, 4, 4,
    4, 4, 1, 4, 4, 4,
    4, 1, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4,
    4, 4, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 4,
    4, 4, 4, 1, 4, 4,
    4, 4, 1, 4, 4, 4,
    4, 1, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4,
    4, 4, 1, 1, 1, 1
} };
// clang-format on
