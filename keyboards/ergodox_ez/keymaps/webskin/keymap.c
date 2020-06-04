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

enum {
  BEPO,
  MISCL1,
  MISCL2,
  MISCR1,
  MISCR2,
  NUMPAD,
  MOUSE,
  // F1 -> F12 one hand
  FXXOH
};

enum custom_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
  THIN_ARROW,
  FAT_ARROW,
  TILD_ARROW,
  PIPE_ARROW,
};

// Tap Dance Declarations
enum {
  TD_COPY_CUT,
  TD_PASTE_SINSERT,
  TD_LESS_LGIL,
  TD_GRTR_RGIL,
  TD_V_W,
  TD_Q_Z,      
  TD_EGRV_ESC,
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_COPY_CUT]       = ACTION_TAP_DANCE_DOUBLE(KC_BP_COPY,  KC_BP_CUT),
  [TD_PASTE_SINSERT]  = ACTION_TAP_DANCE_DOUBLE(KC_BP_PASTE, S(KC_INSERT)),

  [TD_LESS_LGIL] = ACTION_TAP_DANCE_DOUBLE(BP_LESS, BP_LGIL),
  [TD_GRTR_RGIL] = ACTION_TAP_DANCE_DOUBLE(BP_GRTR, BP_RGIL),

  [TD_V_W]       = ACTION_TAP_DANCE_DOUBLE(BP_V, BP_W),
  [TD_Q_Z]       = ACTION_TAP_DANCE_DOUBLE(BP_Q, BP_Z),
  [TD_EGRV_ESC]  = ACTION_TAP_DANCE_DOUBLE(BP_EGRV, KC_ESC),
};


uint16_t get_tapping_term(uint16_t keycode) {
  switch (keycode) {
    case CTL_T(BP_AGRV):
    case RCTL_T(BP_F):
    case CTL_T(KC_NO):
    case RCTL_T(KC_NO):
    case SFT_T(BP_P):
    case SFT_T(BP_D):
    case SFT_T(KC_F3):
    case SFT_T(KC_F8):
    case ALT_T(BP_K):
    case ALT_T(BP_APOS):
    case ALT_T(KC_NO):
      return 200;  
    case LT(MISCR1,BP_E):
    case LT(MISCR2,BP_COMM):
    case LT(MISCL1,BP_T):
    case LT(MISCL2,BP_C):
      return 150;
    default:
      return TAPPING_TERM;
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BEPO] = LAYOUT_ergodox_pretty(
    TG(FXXOH), BP_EN_DASH,     BP_EM_DASH, BP_UNDS,     _______,             _______,            KC_DELETE,                              _______, _______,          _______,         BP_MINS,     _______, _______,      _______,
    BP_DLR,    BP_B,           BP_ECUT,    SFT_T(BP_P), BP_O,                TD(TD_EGRV_ESC),    KC_BSPACE,                              _______, BP_DCRC,          TD(TD_V_W),      SFT_T(BP_D), BP_L,    BP_J,         _______,
    KC_TAB,    BP_A,           BP_U,       BP_I,        LT(MISCR1,BP_E),     LT(MISCR2,BP_COMM),                                                  LT(MISCL2, BP_C), LT(MISCL1,BP_T), BP_S,        BP_R,    BP_N,         BP_M,
    KC_RSFT,   CTL_T(BP_AGRV), BP_Y,       BP_X,        BP_DOT,              ALT_T(BP_K),        KC_ENTER,                               _______, ALT_T(BP_APOS),   TD(TD_Q_Z),      BP_G,        BP_H,    RCTL_T(BP_F), BP_CCED,
    KC_RCTL,   KC_LGUI,        _______,    _______,     LT(NUMPAD,KC_SPACE),                                                                                        KC_SPACE,        KC_RALT,     _______, _______,      _______,
                                                                               A(KC_APPLICATION), KC_UP,          KC_RIGHT, _______,
                                                                                                  KC_DOWN,        KC_LEFT,
                                                                                KC_LSFT, _______, MO(MOUSE),        _______, _______, KC_ENTER
  ),
  [MISCL1] = LAYOUT_ergodox_pretty(
    _______,             PIPE_ARROW,          TILD_ARROW, FAT_ARROW,  BP_DEGR,  _______, _______,                          _______, _______, _______, _______, _______, _______, _______,
    _______,             BP_DLR,              BP_HASH,    THIN_ARROW, BP_PERC,  BP_GRV,  _______,                          _______, _______, _______, _______, _______, _______, _______,
    S(KC_TAB),           BP_SLSH,             BP_ASTR,    BP_PLUS,    BP_EQL,   BP_SCLN,                                            _______, _______, _______, _______, _______, _______,
    KC_MEDIA_PLAY_PAUSE, BP_BSLS,             BP_AT,      BP_DQOT,    BP_COLON, BP_TILD, _______,                          _______, _______, _______, _______, _______, _______, _______,
    KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, _______,    _______,    _______,                                                              _______, _______, _______, _______, _______,
                                                                                           _______, _______,        _______, _______,
                                                                                                    _______,        _______,
                                                                                  _______, _______, _______,        _______, _______, _______
  ),
  [MISCL2] = LAYOUT_ergodox_pretty(
    _______, _______, _______,    _______,    _______,          _______,          _______,                          _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,    THIN_ARROW, BP_LBRC,          BP_RBRC,          _______,                          _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,    _______,    BP_LPRN,          BP_RPRN,                                            _______, _______, _______, _______, _______, _______,
    _______, _______, RALT(BP_Y), RALT(BP_X), TD(TD_LESS_LGIL), TD(TD_GRTR_RGIL), _______,                          _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,    _______,    _______,                                                              _______, _______, _______, _______, _______,
                                                                                           _______, _______,        _______, _______,
                                                                                                    _______,        _______,
                                                                                  _______, _______, _______,        _______, _______, _______
  ),  
  [MISCR1] = LAYOUT_ergodox_pretty(
    _______, _______, _______, _______, _______,         _______,              _______,                        KC_INSERT,         C(KC_DELETE),    C(KC_HOME),    KC_PGUP,      C(KC_END),      _______,       _______,
    _______, _______, _______, _______, _______,         _______,              _______,                        KC_AUDIO_VOL_UP,   KC_DELETE,       KC_HOME,       KC_UP,        KC_END,         KC_PSCREEN,    _______,
    _______, _______, _______, _______, _______,         _______,                                                                 KC_BSPACE,       KC_LEFT,       KC_DOWN,      KC_RIGHT,       A(KC_PSCREEN), _______,
    _______, _______, _______, _______, _______,         TD(TD_PASTE_SINSERT), _______,                        KC_AUDIO_VOL_DOWN, C(KC_BSPACE),    C(KC_LEFT),    KC_PGDN,      C(KC_RIGHT),    _______,       _______,
    _______, _______, _______, _______, TD(TD_COPY_CUT),                                                                                           _______,       _______,      _______,        _______,       _______,
                                                                  _______, _______,      _______, KC_AUDIO_MUTE,
                                                                           _______,      _______,
                                                         _______, _______, _______,      _______, _______, _______
  ),
  [MISCR2] = LAYOUT_ergodox_pretty(
    _______, _______, _______, _______, _______,         _______,              _______,                        _______,    C(KC_DELETE),    C(S(KC_HOME)), C(S(KC_UP)),   C(S(KC_END)),   _______,       _______,
    _______, _______, _______, _______, _______,         _______,              _______,                        _______,    KC_DELETE,       S(KC_HOME),    S(KC_UP),      S(KC_END),      KC_PSCREEN,    _______,
    _______, _______, _______, _______, _______,         _______,                                                          KC_BSPACE,       S(KC_LEFT),    S(KC_DOWN),    S(KC_RIGHT),    A(KC_PSCREEN), _______,
    _______, _______, _______, _______, _______,         TD(TD_PASTE_SINSERT), _______,                        _______,    C(KC_BSPACE),    C(S(KC_LEFT)), C(S(KC_DOWN)), C(S(KC_RIGHT)), _______,       _______,
    _______, _______, _______, _______, TD(TD_COPY_CUT),                                                                                    _______,       _______,       _______,        _______,       _______,
                                                                             _______, _______,      _______, _______,
                                                                                      _______,      _______,
                                                                 C(S(BP_Z)), C(BP_Z), _______,      _______, _______, _______
  ),
  [NUMPAD] = LAYOUT_ergodox_pretty(
    _______, _______,      _______, _______,      _______,   _______,      _______,                          _______, _______,      KC_KP_PLUS, KC_KP_MINUS,  KC_KP_SLASH, KC_KP_ASTERISK,  _______,
    _______, KC_F1,        KC_F2,   SFT_T(KC_F3), KC_F4,     KC_F5,        _______,                          _______, KC_F6,        KC_F7,      SFT_T(KC_F8), KC_F9,       KC_F10,          KC_F11, 
    _______, KC_KP_1,      KC_KP_2, KC_KP_3,      KC_KP_4,   KC_KP_5,                                                 KC_KP_6,      KC_KP_7,    KC_KP_8,      KC_KP_9,     KC_KP_0,         KC_F12, 
    _______, CTL_T(KC_NO), _______, _______,      KC_KP_DOT, ALT_T(KC_NO), _______,                          _______, ALT_T(KC_NO), _______,    _______,     _______,      RCTL_T(KC_NO),   _______,
    _______, _______,      _______, _______,      _______,                                                                          _______,    _______,     _______,      _______,         _______,
                                                            _______, _______,        _______, _______,
                                                                     _______,        _______,
                                                   _______, _______, _______,        _______, _______, _______
  ), 
  [MOUSE] = LAYOUT_ergodox_pretty(
    _______, _______, _______, _______, _______, _______, _______,                          _______,       _______,    _______, KC_MS_BTN3, _______,     _______, _______,
    _______, _______, _______, _______, _______, _______, _______,                          _______,       _______, KC_MS_BTN1, KC_MS_UP,   KC_MS_BTN2,  _______, _______,
    _______, _______, _______, _______, _______, _______,                                              KC_MS_WH_UP, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,                          _______, KC_MS_WH_DOWN, _______,    _______,    _______,     _______, _______,
    _______, _______, _______, _______, _______,                                                                    _______,    _______,    _______,     _______, _______,
                                                          _______, _______,        _______, _______,
                                                                   _______,        _______,
                                                 _______, _______, _______,        _______, _______, _______
  ),
  [FXXOH] = LAYOUT_ergodox_pretty(
    TG(FXXOH), _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______, _______,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,                           _______, _______, _______, _______, _______, _______, _______,
    _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                                             _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, KC_F12,                           _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,                                                              _______, _______, _______, _______, _______,
                                                          _______, _______,        _______, _______,
                                                                   _______,        _______,
                                                 _______, _______, _______,        _______, _______, _______
  ),
  /*
  [EMPTY] = LAYOUT_ergodox_pretty(
    _______, _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,                                            _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,                                                              _______, _______, _______, _______, _______,
                                                          _______, _______,        _______, _______,
                                                                   _______,        _______,
                                                 _______, _______, _______,        _______, _______, _______
  )
  */
};

rgblight_config_t rgblight_config;
bool disable_layer_color = 0;

bool suspended = false;

/*

1U << 16  <=> 1 fois (2 puissance 16)
4U <<  8  <=> 4 fois (2 puissance  8)


layer_state_t update_tri_layer_state(layer_state_t state, uint8_t layer1, uint8_t layer2, uint8_t layer3) {
    layer_state_t mask12 = (1UL << layer1) | (1UL << layer2);
    layer_state_t mask3  = 1UL << layer3;
    return (state & mask12) == mask12 ? (state | mask3) : (state & ~mask3);
}

void update_tri_layer(uint8_t layer1, uint8_t layer2, uint8_t layer3) { layer_state_set(update_tri_layer_state(layer_state, layer1, layer2, layer3)); }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    }
  return true;
}

*/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint8_t temp_mods = get_mods();

  switch (keycode) {
    // Protection de la ligne de repos si on est sur MISCR1
    case BP_A:
      if (record->event.pressed && biton32(layer_state) == MISCR1) {
        SEND_STRING("ea");
        return false;
      } else {
        break;
      }
    case BP_U:
      if (record->event.pressed && biton32(layer_state) == MISCR1) {
        SEND_STRING("eu");
        return false;
      } else {
        break;
      }
    case BP_I:
      if (record->event.pressed && biton32(layer_state) == MISCR1) {
        SEND_STRING("ei");
        return false;
      } else {
        break;
      }
    case BP_X:
      if (record->event.pressed && biton32(layer_state) == MISCR1) {
        SEND_STRING("ex");
        return false;
      } else {
        break;
      }

    // Protection de la ligne de repos si on est sur MISCL1
    case BP_C:
      if (record->event.pressed && biton32(layer_state) == MISCL1) {
        SEND_STRING("tc");
        return false;
      } else {
        break;
      }
    case BP_S:
      if (record->event.pressed && biton32(layer_state) == MISCL1) {
        SEND_STRING("ts");
        return false;
      } else {
        break;
      }
    case BP_R:
      if (record->event.pressed && biton32(layer_state) == MISCL1) {
        SEND_STRING("tr");
        return false;
      } else {
        break;
      }
    case BP_N:
      if (record->event.pressed && biton32(layer_state) == MISCL1) {
        SEND_STRING("tn");
        return false;
      } else {
        break;
      }
    case BP_M:
      if (record->event.pressed && biton32(layer_state) == MISCL1) {
        SEND_STRING("tm");
        return false;
      } else {
        break;
      }
    case BP_H:
      if (record->event.pressed && biton32(layer_state) == MISCL1) {
        SEND_STRING("th");
        return false;
      } else if (record->event.pressed && biton32(layer_state) == MISCL2) {
        SEND_STRING("ch");
        return false;
      } else {
        break;
      }
    case BP_F:
      if (record->event.pressed && biton32(layer_state) == MISCL2) {
        SEND_STRING("cf");
        return false;
      } else {
        break;
      }
    case THIN_ARROW:
      if (record->event.pressed && biton32(layer_state) == MISCL1) {
        clear_mods();
        SEND_STRING("->");
        set_mods(temp_mods);
        return false;
      } else if (record->event.pressed && biton32(layer_state) == MISCL2) {
        clear_mods();
        SEND_STRING("<-");
        set_mods(temp_mods);
        return false;
      } else {
        break;
      }
    case FAT_ARROW:
      if (record->event.pressed && biton32(layer_state) == MISCL1) {
        clear_mods();
        SEND_STRING("=>");
        set_mods(temp_mods);
        return false;
      } else {
        break;
      }
    case TILD_ARROW:
      if (record->event.pressed && biton32(layer_state) == MISCL1) {
        clear_mods();
        SEND_STRING("~>");
        set_mods(temp_mods);
        return false;
      } else {
        break;
      }
    case PIPE_ARROW:
      if (record->event.pressed && biton32(layer_state) == MISCL1) {
        clear_mods();
        SEND_STRING("|>");
        set_mods(temp_mods);
        return false;
      } else {
        break;
      }
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
    case BP_UNDS:
      if (record->event.pressed) {
        clear_mods();
        SEND_STRING("_");
        set_mods(temp_mods);
        return false;
      }
      break;
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
      case MISCL1:
        ergodox_right_led_1_on();
        break;
      case MISCL2:
        ergodox_right_led_2_on();
        break;
      case MISCR1:
        ergodox_right_led_3_on();
        break;
      case MISCR2:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        break;  
      case NUMPAD:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        break;
      case MOUSE:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
      default:
        break;
    }
    switch (layer) {
      case BEPO ... MOUSE:
        if(!disable_layer_color) {
          rgblight_enable_noeeprom();
          rgblight_mode_noeeprom(1);
          rgblight_sethsv_noeeprom(0,0,0);
        }
        break;
      case FXXOH:
        if(!disable_layer_color) {
          rgblight_enable_noeeprom();
          rgblight_mode_noeeprom(1);
          rgblight_sethsv_noeeprom(0,255,127);
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
