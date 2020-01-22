#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_german.h"
#include "keymap_nordic.h"
#include "keymap_french.h"
#include "keymap_spanish.h"
#include "keymap_hungarian.h"
#include "keymap_swedish.h"
#include "keymap_br_abnt2.h"
#include "keymap_canadian_multilingual.h"
#include "keymap_german_ch.h"
#include "keymap_jp.h"
#include "keymap_bepo.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define KC_BP_CUT LCTL(BP_X)
#define KC_BP_COPY LCTL(BP_C)
#define KC_BP_PASTE LCTL(BP_V)
#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL

#define BEPO 0    // Default bépo layer
#define MISCL 1   // Misc right (parentheses, math operators, double quotes, french quotes, back tick, percent, audio play previous next)
#define MISCR 2   // Misc left
#define NUMPAD 3  // Numpad
#define MOUSE 4   // Mouse

enum custom_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
};

// Combos definitions
enum combos {
  // V + ^ -> ESCAPE
  V_DCRC__ESC,
  // G + Q -> Underscore
  G_Q__UNDERSCORE,
  // C + ' -> Ctrl + Z
  C_APOS__LCTL_Z,
  // , + K -> Ctrl + Shift + Z
  COMM_K__LSFT_LCTL_Z,
};
const uint16_t PROGMEM v_dcrc_combo[] = {BP_V, BP_DCRC, COMBO_END};
const uint16_t PROGMEM g_q_combo[] = {BP_G, BP_Q, COMBO_END};
const uint16_t PROGMEM c_apos_combo[] = {BP_C, BP_APOS, COMBO_END};
const uint16_t PROGMEM comm_k_combo[] = {BP_COMM, BP_K, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
  [V_DCRC__ESC] = COMBO(v_dcrc_combo, KC_ESC),
  [G_Q__UNDERSCORE] = COMBO_ACTION(g_q_combo),
  [C_APOS__LCTL_Z] = COMBO_ACTION(c_apos_combo),
  [COMM_K__LSFT_LCTL_Z] = COMBO_ACTION(comm_k_combo),
};
void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {

    case G_Q__UNDERSCORE:
      if (pressed) {
        uint8_t temp_mods = get_mods();
        // On veut absolutement un underscore même si shift est appuyé
        clear_mods();
        tap_code16(ALGR(KC_SPACE));
        set_mods(temp_mods);
      }
      break;

    case C_APOS__LCTL_Z:
      if (pressed) {
        register_code(KC_LCTL);
        register_code(BP_Z);
        unregister_code(BP_Z);
        unregister_code(KC_LCTL);
      }
      break;

    case COMM_K__LSFT_LCTL_Z:
      if (pressed) {
        register_code(KC_LCTL);
        register_code(KC_LSFT);
        register_code(BP_Z);
        unregister_code(BP_Z);
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
      }
      break;
  }
}

// Tap Dance Declarations
enum {
  TD_COPY_CUT  = 0,
  TD_LBRC_RBRC = 1,
  TD_LCBR_RCBR = 2,
  TD_LPRN_RPRN = 3,
  TD_LESS_GRTR = 4,
  TD_LGIL_RGIL = 5,
  TD_V_W       = 6,
  TD_Q_Z       = 7,
};

// Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_COPY_CUT]  = ACTION_TAP_DANCE_DOUBLE(KC_BP_COPY, KC_BP_CUT),
  [TD_LBRC_RBRC] = ACTION_TAP_DANCE_DOUBLE(BP_LBRC, BP_RBRC),
  [TD_LCBR_RCBR] = ACTION_TAP_DANCE_DOUBLE(BP_LCBR, BP_RCBR),
  [TD_LPRN_RPRN] = ACTION_TAP_DANCE_DOUBLE(BP_LPRN, BP_RPRN),
  [TD_LESS_GRTR] = ACTION_TAP_DANCE_DOUBLE(BP_LESS, BP_GRTR),
  [TD_LGIL_RGIL] = ACTION_TAP_DANCE_DOUBLE(BP_LGIL, BP_RGIL),
  [TD_V_W]       = ACTION_TAP_DANCE_DOUBLE(BP_V, BP_W),
  [TD_Q_Z]       = ACTION_TAP_DANCE_DOUBLE(BP_Q, BP_Z),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BEPO] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, BP_W,           KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    BP_DLR,         BP_B,           BP_ECUT,        BP_P,           BP_O,           BP_EGRV,        KC_TRANSPARENT,                                 KC_TRANSPARENT, BP_DCRC,        TD(TD_V_W),     BP_D,           BP_L,           BP_J,           KC_TRANSPARENT,
    KC_TAB,         LSFT_T(BP_A),   LCTL_T(BP_U),   LALT_T(BP_I),   LT(MISCR,BP_E), BP_COMM,                                                                        BP_C,           LT(MISCL,BP_T), LALT_T(BP_S),   RCTL_T(BP_R),   LSFT_T(BP_N),   BP_M,
    KC_TRANSPARENT, BP_AGRV,        BP_Y,           BP_X,           BP_DOT,         BP_K,           KC_TRANSPARENT,                                 KC_TRANSPARENT, BP_APOS,        TD(TD_Q_Z),     BP_G,           BP_H,           BP_F,           BP_CCED,
    KC_TRANSPARENT, KC_LGUI,        KC_TRANSPARENT, KC_TRANSPARENT, KC_SPACE,                                                                                                       KC_SPACE,       KC_RALT,        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                            LALT_T(KC_APPLICATION), WEBUSB_PAIR,    KC_CALCULATOR,  KC_ESCAPE,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                   OSM(MOD_LSFT), LT(MISCL, KC_NO), KC_TRANSPARENT, KC_TRANSPARENT, LT(MISCR, KC_NO), KC_ENTER
  ),
  [MISCL] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT,      KC_TRANSPARENT,      KC_TRANSPARENT,  KC_TRANSPARENT, TD(TD_LBRC_RBRC), KC_TRANSPARENT, KC_TRANSPARENT,                                KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT,      BP_HASH,             BP_PLUS,         BP_MINS,        TD(TD_LCBR_RCBR), BP_GRV,         KC_TRANSPARENT,                                KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    LSFT(KC_TAB),        BP_SLSH,             BP_ASTR,         BP_EQL,         TD(TD_LPRN_RPRN), BP_SCLN,                                                                       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_MEDIA_PLAY_PAUSE, BP_BSLS,             BP_AT,           BP_DQOT,        TD(TD_LESS_GRTR), BP_TILD,        KC_TRANSPARENT,                                KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, BP_DEGR,         BP_PERC,        TD(TD_LGIL_RGIL),                                                                                                KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [MISCR] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_INSERT,         LCTL(KC_DELETE), LCTL(LSFT(KC_HOME)), LCTL(LSFT(KC_UP)),   LCTL(LSFT(KC_END)),   KC_TRANSPARENT,   KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_AUDIO_VOL_UP,   KC_DELETE,       KC_HOME,             KC_UP,               KC_END,               KC_PSCREEN,       KC_TRANSPARENT,
    KC_TRANSPARENT, KC_LSHIFT,      KC_LCTRL,       KC_LALT,        KC_TRANSPARENT, KC_TRANSPARENT,                                                                    KC_BSPACE,       KC_LEFT,             KC_DOWN,             KC_RIGHT,             LALT(KC_PSCREEN), KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_AUDIO_VOL_DOWN, LCTL(KC_BSPACE), LCTL(LSFT(KC_LEFT)), LCTL(LSFT(KC_DOWN)), LCTL(LSFT(KC_RIGHT)), KC_TRANSPARENT,   KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, TD(TD_COPY_CUT),                                                                                                    KC_BP_PASTE,         LSFT(KC_INSERT),     KC_TRANSPARENT,       KC_TRANSPARENT,   KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_AUDIO_MUTE
  ),
  [NUMPAD] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_KP_PLUS,     KC_KP_MINUS,    KC_KP_SLASH,    KC_KP_ASTERISK, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_KP_1,        KC_KP_2,        KC_KP_3,        KC_KP_4,        KC_KP_5,                                                                        KC_KP_6,        KC_KP_7,        KC_KP_8,        KC_KP_9,        KC_KP_0,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_KP_DOT,      KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [MOUSE] = LAYOUT_ergodox_pretty(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_BTN3,     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_MS_WH_UP,    KC_TRANSPARENT, KC_MS_BTN1,     KC_MS_UP,       KC_MS_BTN2,     KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_MS_WH_DOWN,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
};

rgblight_config_t rgblight_config;
bool disable_layer_color = 0;

bool suspended = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
    case TOGGLE_LAYER_COLOR:
      if (record->event.pressed) {
        disable_layer_color ^= 1;
      }
      return false;
  }
  return true;
}

uint32_t layer_state_set_user(uint32_t state) {
    xprintf("layer_state_set_user %u\n", state);

    uint8_t layer = biton32(state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      case 1:
        ergodox_right_led_1_on();
        break;
      case 2:
        ergodox_right_led_2_on();
        break;
      case 3:
        ergodox_right_led_3_on();
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      default:
        break;
    }
    switch (layer) {
      case 0:
        if(!disable_layer_color) {
          rgblight_enable_noeeprom();
          rgblight_mode_noeeprom(1);
          rgblight_sethsv_noeeprom(0,0,0);
        }
        break;
      case 1:
        if(!disable_layer_color) {
          rgblight_enable_noeeprom();
          rgblight_mode_noeeprom(1);
          rgblight_sethsv_noeeprom(0,0,0);
        }
        break;
      case 2:
        if(!disable_layer_color) {
          rgblight_enable_noeeprom();
          rgblight_mode_noeeprom(1);
          rgblight_sethsv_noeeprom(0,0,0);
        }
        break;
      case 3:
        if(!disable_layer_color) {
          rgblight_enable_noeeprom();
          rgblight_mode_noeeprom(1);
          rgblight_sethsv_noeeprom(70,255,114);
        }
        break;
      case 4:
        if(!disable_layer_color) {
          rgblight_enable_noeeprom();
          rgblight_mode_noeeprom(1);
          rgblight_sethsv_noeeprom(239,223,248);
        }
        break;
      default:
        if(!disable_layer_color) {
          rgblight_config.raw = eeconfig_read_rgblight();
          if(rgblight_config.enable == true) {
            rgblight_enable();
            rgblight_mode(rgblight_config.mode);
            rgblight_sethsv(rgblight_config.hue, rgblight_config.sat, rgblight_config.val);
          }
          else {
            rgblight_disable();
          }
        }
        break;
    }
    return state;

};

void keyboard_post_init_user(void) {
  layer_state_set_user(layer_state);
  
  // Customise these values to desired behaviour
  //debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
