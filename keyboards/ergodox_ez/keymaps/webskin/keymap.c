#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_french.h"
#include "keymap_bepo.h"
#include "sendstring_bepo.h"
#include "print.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO  C(KC_Z)
#define KC_PC_CUT   C(KC_X)
#define KC_PC_COPY  C(KC_C)
#define KC_PC_PASTE C(KC_V)
#define KC_BP_CUT   C(BP_X)
#define KC_BP_COPY  C(BP_C)
#define KC_BP_PASTE C(BP_V)
#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC S(KC_GRAVE)
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

// Tap Dance Declarations
enum {
  TD_COPY_CUT,
  TD_LBRC_RBRC,
  TD_LCBR_RCBR,
  TD_LPRN_RPRN,
  TD_LESS_GRTR,
  TD_LGIL_RGIL,
  TD_V_W,
  CT_Q_Z,      
  TD_EGRV_ESC,   
  TD_DLR_HASH,
};

bool q_g__underscore_combo_occured = false;

// Tap Dance Definitions

#    define ACTION_TAP_DANCE_DOUBLE_COMBO_AWARE(kc1, kc2) \
        { .fn = {my_tap_dance_pair_on_each_tap, my_tap_dance_pair_finished, my_tap_dance_pair_reset}, .user_data = (void *)&((qk_tap_dance_pair_t){kc1, kc2}), }

void my_tap_dance_pair_on_each_tap(qk_tap_dance_state_t *state, void *user_data) {
  qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

  if (state->count == 2) {
      register_code16(pair->kc2);
      state->finished = true;
  }
}

void my_tap_dance_pair_finished(qk_tap_dance_state_t *state, void *user_data) {
  qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

  if (state->count == 1) {
    if (
      !(pair->kc1 == BP_Q && q_g__underscore_combo_occured) 
      ) {
      register_code16(pair->kc1);
    }
  } else if (state->count == 2) {
    register_code16(pair->kc2);
  }
}

void my_tap_dance_pair_reset(qk_tap_dance_state_t *state, void *user_data) {
  qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

  if (state->count == 1) {
    if (
      !(pair->kc1 == BP_Q && q_g__underscore_combo_occured) 
      ) {
      unregister_code16(pair->kc1);
    }
  } else if (state->count == 2) {
    unregister_code16(pair->kc2);
  }

  if (q_g__underscore_combo_occured) {
    q_g__underscore_combo_occured = false;
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_COPY_CUT]  = ACTION_TAP_DANCE_DOUBLE(KC_BP_COPY, KC_BP_CUT),
  [TD_LBRC_RBRC] = ACTION_TAP_DANCE_DOUBLE(BP_LBRC, BP_RBRC),
  [TD_LCBR_RCBR] = ACTION_TAP_DANCE_DOUBLE(BP_LCBR, BP_RCBR),
  [TD_LPRN_RPRN] = ACTION_TAP_DANCE_DOUBLE(BP_LPRN, BP_RPRN),
  [TD_LESS_GRTR] = ACTION_TAP_DANCE_DOUBLE(BP_LESS, BP_GRTR),
  [TD_LGIL_RGIL] = ACTION_TAP_DANCE_DOUBLE(BP_LGIL, BP_RGIL),
  [TD_V_W]       = ACTION_TAP_DANCE_DOUBLE(BP_V, BP_W),
  [CT_Q_Z]       = ACTION_TAP_DANCE_DOUBLE_COMBO_AWARE(BP_Q, BP_Z),
  [TD_EGRV_ESC]  = ACTION_TAP_DANCE_DOUBLE(BP_EGRV, KC_ESC),
  [TD_DLR_HASH]  = ACTION_TAP_DANCE_DOUBLE(BP_DLR, BP_HASH),
};

// Combos definitions
enum combos {
  // G + Q -> Underscore
  G_Q__UNDERSCORE,
  // C + ' -> Ctrl + Z
  C_APOS__LCTL_Z,
  // , + K -> Ctrl + Shift + Z
  COMM_K__LSFT_LCTL_Z,
};

const uint16_t PROGMEM g_q_combo[] = {BP_G, BP_Q, COMBO_END};
const uint16_t PROGMEM c_apos_combo[] = {BP_C, BP_APOS, COMBO_END};
const uint16_t PROGMEM comm_k_combo[] = {BP_COMM, BP_K, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
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
        q_g__underscore_combo_occured = true;
      }
      break;

    case C_APOS__LCTL_Z:
      if (pressed) {
        tap_code16(C(BP_Z));
      }
      break;

    case COMM_K__LSFT_LCTL_Z:
      if (pressed) {
        tap_code16(C(S(BP_Z)));
      }
      break;
  }
}

uint16_t get_tapping_term(uint16_t keycode) {
  switch (keycode) {
    case CTL_T(BP_A):
    case RCTL_T(BP_N):
    case SFT_T(BP_U):
    case SFT_T(BP_R):
      return 350;
    case LT(MISCR,BP_E):
    case LT(MISCL,BP_T):
      return 180;
    default:
      return TAPPING_TERM;
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BEPO] = LAYOUT_ergodox_pretty(
    _______, _______,     _______,     _______, _______,             _______,         _______,                                _______, _______,        _______,        _______, _______,     _______,      _______,
    BP_DLR,  BP_B,        BP_ECUT,     BP_P,    BP_O,                TD(TD_EGRV_ESC), _______,                                _______, BP_DCRC,        TD(TD_V_W),     BP_D,    BP_L,        BP_J,         _______,
    KC_TAB,  CTL_T(BP_A), SFT_T(BP_U), BP_I,    LT(MISCR,BP_E),      BP_COMM,                                                             BP_C,        LT(MISCL,BP_T), BP_S,    SFT_T(BP_R), RCTL_T(BP_N), BP_M,
    _______, BP_AGRV,     BP_Y,        BP_X,    BP_DOT,              BP_K,            _______,                                _______, BP_APOS,        TD(CT_Q_Z),     BP_G,    BP_H,        BP_F,         BP_CCED,
    _______, KC_LGUI,     _______,     _______, LT(NUMPAD,KC_SPACE),                                                                                   KC_SPACE,       KC_RALT, _______,     _______,      _______,
                                                                            A(KC_APPLICATION), _______,        KC_CALCULATOR, _______,
                                                                                               _______,        _______,
                                                     OSM(MOD_LSFT), LT(MISCL, KC_NO), LT(MOUSE, KC_NO),        _______, LT(MISCR, KC_NO), KC_ENTER
  ),
  [MISCL] = LAYOUT_ergodox_pretty(
    _______,             _______,             _______, _______, TD(TD_LBRC_RBRC), _______, _______,                          _______, _______, _______, _______, _______, _______, _______,
    _______,             TD(TD_DLR_HASH),     BP_PLUS, BP_MINS, TD(TD_LCBR_RCBR), BP_GRV,  _______,                          _______, _______, _______, _______, _______, _______, _______,
    S(KC_TAB),           BP_SLSH,             BP_ASTR, BP_EQL,  TD(TD_LPRN_RPRN), BP_SCLN,                                            _______, _______, _______, _______, _______, _______,
    KC_MEDIA_PLAY_PAUSE, BP_BSLS,             BP_AT,   BP_DQOT, TD(TD_LESS_GRTR), BP_TILD, _______,                          _______, _______, _______, _______, _______, _______, _______,
    KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, BP_DEGR, BP_PERC, TD(TD_LGIL_RGIL),                                                              _______, _______, _______, _______, _______,
                                                                                           _______, _______,        _______, _______,
                                                                                                    _______,        _______,
                                                                                  _______, _______, _______,        _______, _______, _______
  ),
  [MISCR] = LAYOUT_ergodox_pretty(
    _______, _______, _______, _______, _______,         _______, _______,                        KC_INSERT,         C(KC_DELETE),    S(KC_HOME),          S(KC_UP),        S(KC_END),            _______,          _______,
    _______, _______, _______, _______, _______,         _______, _______,                        KC_AUDIO_VOL_UP,   KC_DELETE,       KC_HOME,             KC_UP,           KC_END,               KC_PSCREEN,       _______,
    _______, _______, _______, _______, _______,         _______,                                                    KC_BSPACE,       KC_LEFT,             KC_DOWN,         KC_RIGHT,             A(KC_PSCREEN),    _______,
    _______, _______, _______, _______, _______,         _______, _______,                        KC_AUDIO_VOL_DOWN, C(KC_BSPACE),    C(S(KC_LEFT)),       S(KC_DOWN),      C(S(KC_RIGHT)),       _______,          _______,
    _______, _______, _______, _______, TD(TD_COPY_CUT),                                                                              KC_BP_PASTE,         S(KC_INSERT),    _______,              _______,          _______,
                                                                  _______, _______,      _______, _______,
                                                                           _______,      _______,
                                                         _______, _______, _______,      _______, _______, KC_AUDIO_MUTE
  ),
  [NUMPAD] = LAYOUT_ergodox_pretty(
    _______, _______, _______, _______, _______,   _______, _______,                          _______, _______, KC_KP_PLUS, KC_KP_MINUS, KC_KP_SLASH, KC_KP_ASTERISK, _______,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,     KC_F5,   _______,                          _______, KC_F6,   KC_F7,      KC_F8,       KC_F9,       KC_F10,         KC_F11, 
    _______, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_4,   KC_KP_5,                                            KC_KP_6, KC_KP_7,    KC_KP_8,     KC_KP_9,     KC_KP_0,        KC_F12, 
    _______, _______, _______, _______, KC_KP_DOT, _______, _______,                          _______, _______, _______,    _______,     _______,     _______,        _______,
    _______, _______, _______, _______, _______,                                                                _______,    _______,     _______,     _______,        _______,
                                                            _______, _______,        _______, _______,
                                                                     _______,        _______,
                                                   _______, _______, _______,        _______, _______, _______
  ), 
  [MOUSE] = LAYOUT_ergodox_pretty(
    _______, _______, _______, _______, _______, _______, _______,                          _______,       _______, _______,    KC_MS_BTN3, _______,     _______, _______,
    _______, _______, _______, _______, _______, _______, _______,                          KC_MS_WH_UP,   _______, KC_MS_BTN1, KC_MS_UP,   KC_MS_BTN2,  _______, _______,
    _______, _______, _______, _______, _______, _______,                                                  _______, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,                          KC_MS_WH_DOWN, _______, _______,    _______,    _______,     _______, _______,
    _______, _______, _______, _______, _______,                                                                    _______,    _______,    _______,     _______, _______,
                                                          _______, _______,        _______, _______,
                                                                   _______,        _______,
                                                 _______, _______, _______,        _______, _______, _______
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
          rgblight_sethsv_noeeprom(0,0,0);
        }
        break;
      case 4:
        if(!disable_layer_color) {
          rgblight_enable_noeeprom();
          rgblight_mode_noeeprom(1);
          rgblight_sethsv_noeeprom(0,0,0);
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
