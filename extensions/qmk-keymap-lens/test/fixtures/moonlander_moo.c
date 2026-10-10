// PRIMARY KEYMAP

#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_us_international.h"

#define ML_SAFE_RANGE SAFE_RANGE
#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_REDO LGUI(KC_Y)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)
#define MOON_LED_LEVEL LED_LEVEL
#define UID "REDACTED"
#define PWD "REDACTED"

enum custom_keycodes {
  RGB_SLD = ML_SAFE_RANGE,
  MAC_UID,
  MAC_PWD,
  RGB_TOGGLE,
};

enum tap_dance_codes {
  WIN_ESCAPE,
  WIN_LBRACKET,
  WIN_RBRACKET,
  MAC_ESCAPE,
  MAC_LBRACKET,
  MACCOPYPASTA,
  MAC_RBRACKET,
  MAC_VOL_DOWN_MUTE,
  MAC_REPLACE,
  MAC_FIND,
  WIN_REPLACE,
  WIN_FIND,
  WINCOPYPASTA,
  ENTER_MAC,
  ENTER_WIN,
  MAC_SPACE,
  MAC_CREDS,
  LAYER_SWAP,
  TOGGLE_BACKLIGHT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    //WIN main
  [0] = LAYOUT_moonlander(
    KC_ESCAPE,     KC_1,           KC_2,       KC_3,           KC_4,               KC_5,                   TD(TOGGLE_BACKLIGHT),                             KC_F5,       KC_6,           KC_7,               KC_8,           KC_9,           KC_0,    KC_MINUS,
    KC_TAB,             KC_Q,           KC_W,       KC_E,           KC_R,    KC_T,                   LCTL(KC_SLASH),                          RCS(KC_C),  KC_Y,           KC_U,               KC_I,           KC_O,           KC_P,           KC_EQUAL,
    MO(2),              KC_A,           KC_S,       KC_D,           KC_F,       KC_G,                   TD(WIN_LBRACKET),                        TD(WIN_RBRACKET),  KC_H,           KC_J,               KC_K,           KC_L,           KC_SEMICOLON,      KC_QUOTE,
    KC_LSFT,          KC_Z,           KC_X,       KC_C,           KC_V,               KC_B,                                                            KC_N,           KC_M,               KC_COMMA,           KC_DOT,         KC_SLASH,      KC_BACKSLASH,
    KC_LCTL,           KC_LALT,        KC_LGUI,    TD(LAYER_SWAP), KC_HOME,            LSFT_T(KC_LEFT),                                                 TD(ENTER_WIN),           KC_END,    KC_MEDIA_PLAY_PAUSE,KC_AUDIO_MUTE,  KC_AUDIO_VOL_DOWN,   KC_AUDIO_VOL_UP,
                                                                            KC_BACKSPACE,      KC_DELETE,       TD(WINCOPYPASTA),                                   KC_PGDN,       KC_PGUP,   KC_SPACE
  ),
  //MAC main
  [1] = LAYOUT_moonlander(
    TD(MAC_ESCAPE),   KC_1,            KC_2,        KC_3,           KC_4,               KC_5,           TD(TOGGLE_BACKLIGHT),                                      LGUI(LSFT(KC_R)),       KC_6,           KC_7,               KC_8,           KC_9,           KC_0   ,        KC_MINUS,
    KC_TAB,         KC_Q,               KC_W,       KC_E,           TD(MAC_REPLACE),    KC_T,           LCTL(KC_BACKSLASH),                                RCS(KC_T), KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_EQUAL,
    MO(3),          KC_A,               KC_S,       KC_D,           TD(MAC_FIND),       KC_G,           TD(MAC_LBRACKET),                               TD(MAC_RBRACKET), KC_H,           KC_J,               KC_K,           KC_L,           KC_SEMICOLON,   KC_QUOTE,
    KC_LSFT,      KC_Z,               KC_X,       KC_C,           KC_V,               KC_B,                                                           KC_N,   KC_M,           KC_COMMA,       KC_DOT,          KC_SLASH,          KC_BACKSLASH,
    KC_LCTL,       KC_LALT,            KC_LGUI,        TD(LAYER_SWAP), LGUI(KC_LEFT),  LSFT_T(KC_LEFT),                                                TD(ENTER_MAC),       LGUI(KC_RIGHT),        RCS(KC_S),LCTL(KC_SPACE),    TD(MAC_VOL_DOWN_MUTE),   KC_AUDIO_VOL_UP,
                                                                            KC_BACKSPACE,  KC_DELETE,      TD(MACCOPYPASTA),                                    KC_PGDN,   KC_PGUP,   TD(MAC_SPACE)
  ),

  //win alt
[2] = LAYOUT_moonlander(
    KC_GRAVE,       KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,        KC_NO,                                              LALT(KC_F4),  KC_F6,       KC_F7,             KC_F8,          KC_F9,          KC_F10,        KC_KP_MINUS,
    KC_TAB,         KC_NO, KC_UP,   KC_NO,          KC_NO,          KC_NO,          KC_NO,          LSA(KC_A),                                          KC_F7,      KC_F8,          KC_F9,          KC_NO,          KC_NO,          KC_KP_PLUS,
    KC_TRANSPARENT, KC_LEFT,        KC_DOWN,        KC_RIGHT,       LCTL(KC_F),          KC_NO,          KC_NO,                                         KC_NO,      KC_NO,          LALT(KC_DOWN),          LALT(KC_UP),          KC_NO,          KC_NO,          KC_DQUO,
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                                              KC_NO,      KC_NO,          KC_NO,          KC_KP_DOT,      KC_NO,          KC_PIPE,
    KC_LCTL,       RGB_VAD,        RGB_VAI,        KC_NO, KC_TRANSPARENT, KC_MEDIA_STOP,                                                               KC_MEDIA_PLAY_PAUSE,KC_F10,         KC_TRANSPARENT, KC_TRANSPARENT, KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,
                                                            LCTL(KC_Z), LCTL(KC_Y), LSFT(KC_TAB),                                                       KC_TAB,KC_NO,   KC_TRANSPARENT
  ),

  //mac alt
  [3] = LAYOUT_moonlander(
    KC_GRAVE,       KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          TD(MAC_CREDS),                                              LGUI(KC_Q),      KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_UNDS,
    KC_TAB,         KC_F11,         KC_UP,          KC_F13,         KC_F14,         KC_F15,         LCTL(KC_PIPE),                                      KC_NO,       KC_NO,         KC_NO,         KC_NO,         KC_NO, KC_NO,           KC_PLUS,
    KC_TRANSPARENT, KC_LEFT,        KC_DOWN,        KC_RIGHT,       LCA(KC_F),          KC_NO,          KC_NO,                                          KC_NO,       KC_NO,        LOPT(KC_DOWN),        LOPT(KC_UP),         KC_NO,    KC_COLN,        KC_DQUO,
    KC_NO,          KC_F14,         KC_F15,         KC_NO,          KC_NO,          KC_NO,                                                              KC_NO,     KC_NO,         KC_NO,         KC_NO,     KC_QUES,        KC_PIPE,
    KC_LCTL,       RGB_VAD,        RGB_VAI,        KC_LCTL, LCTL(KC_LEFT), LCTL(KC_SPACE),                                                      RCS(KC_S),LCTL(KC_RIGHT),   KC_KP_DOT,      KC_KP_MINUS,    KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,
                                                                 KC_MAC_UNDO, KC_MAC_REDO, LSFT(KC_TAB),                                                KC_TAB,KC_NO,   KC_TAB
  ),

    //WIN gaming
  [4] = LAYOUT_moonlander(
    KC_ESCAPE,     KC_1,           KC_2,       KC_3,           KC_4,               KC_5,                   TD(TOGGLE_BACKLIGHT),                             KC_F5,       KC_6,           KC_7,               KC_8,           KC_9,           KC_0,    KC_MINUS,
    KC_TAB,             KC_Q,           KC_W,       KC_E,           KC_R,    KC_T,                   LCTL(KC_SLASH),                          RCS(KC_C),  KC_Y,           KC_U,               KC_I,           KC_O,           KC_P,           KC_EQUAL,
    KC_CAPS_LOCK,              KC_A,           KC_S,       KC_D,           KC_F,       KC_G,                   TD(WIN_LBRACKET),                        TD(WIN_RBRACKET),  KC_H,           KC_J,               KC_K,           KC_L,           KC_SEMICOLON,      KC_QUOTE,
    KC_LSFT,          KC_Z,           KC_X,       KC_C,           KC_V,               KC_B,                                                            KC_N,           KC_M,               KC_COMMA,           KC_DOT,         KC_SLASH,      KC_BACKSLASH,
    KC_LCTL,           KC_LALT,        KC_LGUI,    TD(LAYER_SWAP), KC_HOME,            LSFT_T(KC_LEFT),                                                 TD(ENTER_WIN),           KC_END,    KC_MEDIA_PLAY_PAUSE,KC_AUDIO_MUTE,  KC_AUDIO_VOL_DOWN,   KC_AUDIO_VOL_UP,
                                                                            KC_BACKSPACE,      KC_DELETE,       KC_SPACE,                                   KC_PGDN,       KC_PGUP,   KC_SPACE
  ),
};

extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    //win main
    [0] = { {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255}, {146,224,255} },

    //mac main
    [1] = { {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255} },

    //win alt
    [2] = { {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255}, {35,255,255} },

    //mac alt
    [3] = { {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255} },

};

/* void led_set_keymap(uint8_t usb_led) {
  if (!(usb_led & (1<<USB_LED_NUM_LOCK))) {
    register_code(KC_NUM_LOCK);
    unregister_code(KC_NUM_LOCK);
  }
}
 */

void set_layer_color(int layer) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

bool rgb_matrix_indicators_user(void) {
  if (keyboard_config.disable_layer_led) { return false; }
  switch (biton32(layer_state)) {
    case 0:
      set_layer_color(0);
      break;
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(255, 0, 0);
    break;
  }
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {
    case MAC_UID:
    if (record->event.pressed) {
      SEND_STRING(UID);
    }
    break;
    case MAC_PWD:
    if (record->event.pressed) {
        SEND_STRING(PWD);
    }
    break;
    case RGB_TOGGLE:
    if (record->event.pressed) {
      rgblight_toggle();
    }
    break;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
  }
  return true;
}

typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

// static tap dance_state[69];

static tap dance_state = {
    .is_press_action = true,
    .step = 0
};

uint8_t dance_step(tap_dance_state_t *state);

uint8_t dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}

void on_win_escape(tap_dance_state_t *state, void *user_data);
void win_escape_finished(tap_dance_state_t *state, void *user_data);
void win_escape_reset(tap_dance_state_t *state, void *user_data);

void on_win_escape(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_ESCAPE);
        tap_code16(KC_ESCAPE);
        tap_code16(KC_ESCAPE);
    }
    if(state->count > 3) {
        tap_code16(KC_ESCAPE);
    }
}

uint8_t win_escape_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void win_escape_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = win_escape_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_ESCAPE); break;
        case DOUBLE_TAP: register_code16(KC_GRAVE); break;
        case DOUBLE_HOLD: register_code16(LSFT(KC_GRAVE)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_ESCAPE); register_code16(KC_ESCAPE);
    }
}

void win_escape_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_ESCAPE); break;
        case DOUBLE_TAP: unregister_code16(KC_GRAVE); break;
        case DOUBLE_HOLD: unregister_code16(LSFT(KC_GRAVE)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_ESCAPE); break;
    }
    dance_state.step = 0;
}

void on_win_lbracket(tap_dance_state_t *state, void *user_data);
void win_lbracket_finished(tap_dance_state_t *state, void *user_data);
void win_lbracket_reset(tap_dance_state_t *state, void *user_data);

void on_win_lbracket(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_LBRC);
        tap_code16(KC_LBRC);
        tap_code16(KC_LBRC);
    }
    if(state->count > 3) {
        tap_code16(KC_LBRC);
    }
}

uint8_t win_lbracket_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void win_lbracket_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = win_lbracket_dance_step(state);
    switch (dance_state.step) {
        case DOUBLE_TAP: register_code16(KC_LBRC); break;
        case SINGLE_HOLD: register_code16(LSFT(KC_9)); break;
        case SINGLE_TAP: register_code16(LSFT(KC_LBRC)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_LBRC); register_code16(KC_LBRC);
    }
}

void win_lbracket_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case DOUBLE_TAP: unregister_code16(KC_LBRC); break;
        case SINGLE_HOLD: unregister_code16(LSFT(KC_9)); break;
        case SINGLE_TAP: unregister_code16(LSFT(KC_LBRC)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_LBRC); break;
    }
    dance_state.step = 0;
}


void on_win_rbracket(tap_dance_state_t *state, void *user_data);
void win_rbracket_finished(tap_dance_state_t *state, void *user_data);
void win_rbracket_reset(tap_dance_state_t *state, void *user_data);

void on_win_rbracket(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_RBRC);
        tap_code16(KC_RBRC);
        tap_code16(KC_RBRC);
    }
    if(state->count > 3) {
        tap_code16(KC_RBRC);
    }
}

uint8_t win_rbracket_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void win_rbracket_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = win_rbracket_dance_step(state);
    switch (dance_state.step) {
        case DOUBLE_TAP: register_code16(KC_RBRC); break;
        case SINGLE_HOLD: register_code16(LSFT(KC_0)); break;
        case SINGLE_TAP: register_code16(LSFT(KC_RBRC)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_RBRC); register_code16(KC_RBRC);
    }
}

void win_rbracket_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case DOUBLE_TAP: unregister_code16(KC_RBRC); break;
        case SINGLE_HOLD: unregister_code16(LSFT(KC_0)); break;
        case SINGLE_TAP: unregister_code16(LSFT(KC_RBRC)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_RBRC); break;
    }
    dance_state.step = 0;
}

void on_mac_escape(tap_dance_state_t *state, void *user_data);
void mac_escape_finished(tap_dance_state_t *state, void *user_data);
void mac_escape_reset(tap_dance_state_t *state, void *user_data);

void on_mac_escape(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_ESCAPE);
        tap_code16(KC_ESCAPE);
        tap_code16(KC_ESCAPE);
    }
    if(state->count > 3) {
        tap_code16(KC_ESCAPE);
    }
}

uint8_t mac_escape_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void mac_escape_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = mac_escape_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_ESCAPE); break;
        case SINGLE_HOLD: register_code16(KC_GRAVE); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_GRAVE)); break;
        case DOUBLE_HOLD: break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_ESCAPE); register_code16(KC_ESCAPE);
    }
}

void mac_escape_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_ESCAPE); break;
        case SINGLE_HOLD: unregister_code16(KC_GRAVE); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_GRAVE)); break;
        case DOUBLE_HOLD: break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_ESCAPE); break;
    }
    dance_state.step = 0;
}

void on_mac_lbracket(tap_dance_state_t *state, void *user_data);
void mac_lbracket_finished(tap_dance_state_t *state, void *user_data);
void mac_lbracket_reset(tap_dance_state_t *state, void *user_data);

void on_mac_lbracket(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_LBRC);
        tap_code16(KC_LBRC);
        tap_code16(KC_LBRC);
    }
    if(state->count > 3) {
        tap_code16(KC_LBRC);
    }
}

uint8_t mac_lbracket_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void mac_lbracket_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = mac_lbracket_dance_step(state);
    switch (dance_state.step) {
        case DOUBLE_TAP: register_code16(KC_LBRC); break;
        case SINGLE_HOLD: register_code16(LSFT(KC_9)); break;
        case SINGLE_TAP: register_code16(LSFT(KC_LBRC)); break;
        case DOUBLE_HOLD: register_code16(LGUI(KC_LBRC)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_LBRC); register_code16(KC_LBRC);
    }
}

void mac_lbracket_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {

        case DOUBLE_TAP: unregister_code16(KC_LBRC); break;
        case SINGLE_HOLD: unregister_code16(LSFT(KC_9)); break;
        case SINGLE_TAP: unregister_code16(LSFT(KC_LBRC)); break;
        case DOUBLE_HOLD: register_code16(LGUI(KC_LBRC)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_LBRC); break;
    }
    dance_state.step = 0;
}

void on_mac_copypasta(tap_dance_state_t *state, void *user_data);
void mac_copypasta_finished(tap_dance_state_t *state, void *user_data);
void mac_copypasta_reset(tap_dance_state_t *state, void *user_data);

void on_mac_copypasta(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(LGUI(KC_C));
    }
    if(state->count > 3) {
        tap_code16(LGUI(KC_C));
    }
}

uint8_t mac_copypasta_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void mac_copypasta_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = mac_copypasta_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(LGUI(KC_V)); break;
        case SINGLE_HOLD: register_code16(LGUI(KC_V)); break;
        case DOUBLE_TAP: register_code16(LGUI(KC_C)); break;
        case DOUBLE_HOLD: register_code16(LGUI(KC_X)); break;
        case DOUBLE_SINGLE_TAP: register_code16(LGUI(KC_V)); break;
    }
}

void mac_copypasta_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(50);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(LGUI(KC_V)); break;
        case SINGLE_HOLD: unregister_code16(LGUI(KC_V)); break;
        case DOUBLE_TAP: unregister_code16(LGUI(KC_C)); break;
        case DOUBLE_HOLD: unregister_code16(LGUI(KC_X)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(LGUI(KC_V)); break;
    }
    dance_state.step = 0;
}

void on_mac_rbracket(tap_dance_state_t *state, void *user_data);
void mac_rbracket_finished(tap_dance_state_t *state, void *user_data);
void mac_rbracket_reset(tap_dance_state_t *state, void *user_data);

void on_mac_rbracket(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_RBRC);
        tap_code16(KC_RBRC);
        tap_code16(KC_RBRC);
    }
    if(state->count > 3) {
        tap_code16(KC_RBRC);
    }
}

uint8_t mac_rbracket_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void mac_rbracket_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = mac_rbracket_dance_step(state);
    switch (dance_state.step) {
        case DOUBLE_TAP: register_code16(KC_RBRC); break;
        case SINGLE_HOLD: register_code16(LSFT(KC_0)); break;
        case SINGLE_TAP: register_code16(LSFT(KC_RBRC)); break;
        case DOUBLE_HOLD: register_code16(LGUI(KC_RBRC)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_RBRC); register_code16(KC_RBRC);
    }
}

void mac_rbracket_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case DOUBLE_TAP: unregister_code16(KC_RBRC); break;
        case SINGLE_HOLD: unregister_code16(LSFT(KC_0)); break;
        case SINGLE_TAP: unregister_code16(LSFT(KC_RBRC)); break;
        case DOUBLE_HOLD: unregister_code16(LGUI(KC_RBRC)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_RBRC); break;
    }
    dance_state.step = 0;
}

void on_mac_voldown_mute(tap_dance_state_t *state, void *user_data);
void mac_voldown_mute_finished(tap_dance_state_t *state, void *user_data);
void mac_voldown_mute_reset(tap_dance_state_t *state, void *user_data);

void on_mac_voldown_mute(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_AUDIO_VOL_DOWN);
        tap_code16(KC_AUDIO_VOL_DOWN);
        tap_code16(KC_AUDIO_VOL_DOWN);
    }
    if(state->count > 3) {
        tap_code16(KC_AUDIO_VOL_DOWN);
    }
}

uint8_t mac_voldown_mute_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void mac_voldown_mute_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = mac_voldown_mute_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_AUDIO_VOL_DOWN); break;
        case SINGLE_HOLD: register_code16(KC_SPACE); break;
        case DOUBLE_TAP: register_code16(KC_AUDIO_VOL_DOWN); break;
        case DOUBLE_HOLD: register_code16(KC_AUDIO_MUTE); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_AUDIO_VOL_DOWN); register_code16(KC_AUDIO_VOL_DOWN);
    }
}

void mac_voldown_mute_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_AUDIO_VOL_DOWN); break;
        case SINGLE_HOLD: unregister_code16(KC_SPACE); break;
        case DOUBLE_TAP: unregister_code16(KC_AUDIO_VOL_DOWN); break;
        case DOUBLE_HOLD: unregister_code16(KC_AUDIO_MUTE); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_AUDIO_VOL_DOWN); break;
    }
    dance_state.step = 0;
}

void on_mac_replace(tap_dance_state_t *state, void *user_data);
void mac_replace_finished(tap_dance_state_t *state, void *user_data);
void mac_replace_reset(tap_dance_state_t *state, void *user_data);

void on_mac_replace(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_R);
        tap_code16(KC_R);
        tap_code16(KC_R);
    }
    if(state->count > 3) {
        tap_code16(KC_R);
    }
}

uint8_t mac_replace_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void mac_replace_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = mac_replace_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_R); break;
        case SINGLE_HOLD: register_code16(LGUI(KC_H)); break;
        case DOUBLE_TAP: register_code16(KC_R); register_code16(KC_R); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_R); register_code16(KC_R);
    }
}

void mac_replace_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_R); break;
        case SINGLE_HOLD: unregister_code16(LGUI(KC_H)); break;
        case DOUBLE_TAP: unregister_code16(KC_R); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_R); break;
    }
    dance_state.step = 0;
}
void on_mac_find(tap_dance_state_t *state, void *user_data);
void mac_find_finished(tap_dance_state_t *state, void *user_data);
void mac_find_reset(tap_dance_state_t *state, void *user_data);

void on_mac_find(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_F);
        tap_code16(KC_F);
        tap_code16(KC_F);
    }
    if(state->count > 3) {
        tap_code16(KC_F);
    }
}

uint8_t mac_find_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void mac_find_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = mac_find_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_F); break;
        case SINGLE_HOLD: register_code16(LGUI(KC_F)); break;
        case DOUBLE_TAP: register_code16(KC_F); register_code16(KC_F); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_F); register_code16(KC_F);
    }
}

void mac_find_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_F); break;
        case SINGLE_HOLD: unregister_code16(LGUI(KC_F)); break;
        case DOUBLE_TAP: unregister_code16(KC_F); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_F); break;
    }
    dance_state.step = 0;
}

void on_win_replace(tap_dance_state_t *state, void *user_data);
void win_replace_finished(tap_dance_state_t *state, void *user_data);
void win_replace_reset(tap_dance_state_t *state, void *user_data);

void on_win_replace(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_R);
        tap_code16(KC_R);
        tap_code16(KC_R);
    }
    if(state->count > 3) {
        tap_code16(KC_R);
    }
}

uint8_t win_replace_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void win_replace_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = win_replace_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_R); break;
        case SINGLE_HOLD: register_code16(LCTL(KC_H)); break;
        case DOUBLE_TAP: register_code16(KC_R); register_code16(KC_R); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_R); register_code16(KC_R);
    }
}

void win_replace_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_R); break;
        case SINGLE_HOLD: unregister_code16(LCTL(KC_H)); break;
        case DOUBLE_TAP: unregister_code16(KC_R); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_R); break;
    }
    dance_state.step = 0;
}
void on_win_find(tap_dance_state_t *state, void *user_data);
void win_find_finished(tap_dance_state_t *state, void *user_data);
void win_find_reset(tap_dance_state_t *state, void *user_data);

void on_win_find(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_F);
        tap_code16(KC_F);
        tap_code16(KC_F);
    }
    if(state->count > 3) {
        tap_code16(KC_F);
    }
}

uint8_t win_find_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void win_find_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = win_find_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_F); break;
        case SINGLE_HOLD: register_code16(LCTL(KC_F)); break;
        case DOUBLE_TAP: register_code16(KC_F); register_code16(KC_F); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_F); register_code16(KC_F);
    }
}

void win_find_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_F); break;
        case SINGLE_HOLD: unregister_code16(LCTL(KC_F)); break;
        case DOUBLE_TAP: unregister_code16(KC_F); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_F); break;
    }
    dance_state.step = 0;
}

void on_mouse_3(tap_dance_state_t *state, void *user_data);
void mouse_3_finished(tap_dance_state_t *state, void *user_data);
void mouse_3_reset(tap_dance_state_t *state, void *user_data);

void on_mouse_3(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_MS_BTN3);
        tap_code16(KC_MS_BTN3);
        tap_code16(KC_MS_BTN3);
    }
    if(state->count > 3) {
        tap_code16(KC_MS_BTN3);
    }
}

uint8_t mouse_3_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void mouse_3_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = mouse_3_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_MS_BTN3); break;
        case SINGLE_HOLD: register_code16(KC_MS_BTN3); break;
        case DOUBLE_TAP: register_code16(SGUI(KC_R)); break;
        case DOUBLE_HOLD: register_code16(SGUI(KC_R)); break;
        case DOUBLE_SINGLE_TAP: register_code16(KC_MS_BTN3); break;
    }
}

void mouse_3_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_MS_BTN3); break;
        case SINGLE_HOLD: unregister_code16(KC_MS_BTN3); break;
        case DOUBLE_TAP: unregister_code16(SGUI(KC_R)); break;
        case DOUBLE_HOLD: unregister_code16(SGUI(KC_R)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_MS_BTN3); break;
    }
    dance_state.step = 0;
}

void on_win_copypasta(tap_dance_state_t *state, void *user_data);
void win_copypasta_finished(tap_dance_state_t *state, void *user_data);
void win_copypasta_reset(tap_dance_state_t *state, void *user_data);

void on_win_copypasta(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(LCTL(LCTL(KC_Z)));
        tap_code16(LCTL(LCTL(KC_Z)));
        tap_code16(LCTL(LCTL(KC_Z)));
    }
    if(state->count > 3) {
        tap_code16(LCTL(LCTL(KC_Z)));
    }
}

uint8_t win_copypasta_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void win_copypasta_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = mouse_3_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(LCTL(KC_V)); break;
        case SINGLE_HOLD: register_code16(LCTL(KC_V)); break;
        case DOUBLE_TAP: register_code16(LCTL(KC_C)); break;
        case DOUBLE_HOLD: register_code16(LCTL(KC_X)); break;
        case DOUBLE_SINGLE_TAP: register_code16(LCTL(KC_V)); break;
    }
}

void win_copypasta_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(50);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(LCTL(KC_V)); break;
        case SINGLE_HOLD: unregister_code16(LCTL(KC_V)); break;
        case DOUBLE_TAP: unregister_code16(LCTL(KC_C)); break;
        case DOUBLE_HOLD: unregister_code16(LCTL(KC_X)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(LCTL(KC_C)); break;
    }
    dance_state.step = 0;
}

void on_enter_mac(tap_dance_state_t *state, void *user_data);
void enter_mac_finished(tap_dance_state_t *state, void *user_data);
void enter_mac_reset(tap_dance_state_t *state, void *user_data);

void on_enter_mac(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_ENT);
        tap_code16(KC_ENT);
        tap_code16(KC_ENT);
    }
    if(state->count > 3) {
        tap_code16(KC_ENT);
    }
}

uint8_t enter_mac_dance_step(tap_dance_state_t *state) {
   if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}

void enter_mac_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = enter_mac_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_ENT); break;
        case SINGLE_HOLD: layer_on(3); break;
        case DOUBLE_TAP:  register_code16(KC_ENT); break;
        case DOUBLE_HOLD: break;
        case DOUBLE_SINGLE_TAP: register_code16(KC_ENT); break;
    }
}

void enter_mac_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_ENT); break;
        case SINGLE_HOLD: layer_off(3); break;
        case DOUBLE_TAP: unregister_code16(KC_ENT); break;
        case DOUBLE_HOLD: break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_ENT); break;
    }
    dance_state.step = 0;
}

void on_enter_win(tap_dance_state_t *state, void *user_data);
void enter_win_finished(tap_dance_state_t *state, void *user_data);
void enter_win_reset(tap_dance_state_t *state, void *user_data);

void on_enter_win(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_ENT);
        tap_code16(KC_ENT);
        tap_code16(KC_ENT);
    }
    if(state->count > 3) {
        tap_code16(KC_ENT);
    }
}

uint8_t enter_win_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void enter_win_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = enter_win_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_ENT); break;
        case SINGLE_HOLD: layer_on(2); break;
        case DOUBLE_TAP: register_code16(KC_ENT); break;
        case DOUBLE_SINGLE_TAP: register_code16(KC_ENT); break;
    }
}

void enter_win_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(19);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_ENT); break;
        case SINGLE_HOLD: layer_off(2); break;
        case DOUBLE_TAP: unregister_code16(KC_ENT); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_ENT); break;
    }
    dance_state.step = 0;
}

void on_mac_creds(tap_dance_state_t *state, void *user_data);
void mac_creds_finished(tap_dance_state_t *state, void *user_data);
void mac_creds_reset(tap_dance_state_t *state, void *user_data);

void on_mac_creds(tap_dance_state_t *state, void *user_data) {
}

uint8_t mac_creds_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}

void mac_creds_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = mac_creds_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: rgblight_toggle(); break;
        case SINGLE_HOLD : SEND_STRING(UID); register_code16(KC_TAB); unregister_code16(KC_TAB); break;
        case DOUBLE_TAP: break;
        case DOUBLE_HOLD: SEND_STRING(PWD); break;
    }
}

void mac_creds_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(19);
    switch (dance_state.step) {
        case SINGLE_TAP: break;
        case SINGLE_HOLD: unregister_code16(KC_TAB); break;
        case DOUBLE_TAP: break;
        case DOUBLE_HOLD: break;
    }
    dance_state.step = 0;
}

void on_layer_swap(tap_dance_state_t *state, void *user_data);
void layer_swap_finished(tap_dance_state_t *state, void *user_data);
void layer_swap_reset(tap_dance_state_t *state, void *user_data);
void on_layer_swap(tap_dance_state_t *state, void *user_data) {}

uint8_t layer_swap_dance_step(tap_dance_state_t *state) {
    return SINGLE_TAP;
}

void layer_swap_finished(tap_dance_state_t *state, void *user_data) {
    wait_ms(20);
    dance_state.step = layer_swap_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP:
        switch (biton32(layer_state)) {
        case 0 :
            layer_invert(1);
            // register_code16(LGUI(KC_2));
            break;
        default :
            layer_off(1);
            // register_code16(LGUI(KC_1));
            break;
        }
        break;
    }
}

void layer_swap_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP:
        switch (biton32(layer_state)) {
        case 1 :
            unregister_code16(LGUI(KC_2));
            break;
        default:
            unregister_code16(LGUI(KC_1));
            break;
        }
        break;
    }
    dance_state.step = 0;
}

void on_space_mac(tap_dance_state_t *state, void *user_data);
void space_mac_finished(tap_dance_state_t *state, void *user_data);
void space_mac_reset(tap_dance_state_t *state, void *user_data);

void on_space_mac(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_ENT);
        tap_code16(KC_ENT);
        tap_code16(KC_ENT);
    }
    if(state->count > 3) {
        tap_code16(KC_ENT);
    }
}

uint8_t space_mac_dance_step(tap_dance_state_t *state) {
   if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}

void space_mac_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = space_mac_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_SPACE); break;
        case SINGLE_HOLD: register_code16(KC_SPACE); break;
        case DOUBLE_TAP:  register_code16(KC_TAB); break;
        case DOUBLE_HOLD: break;
        case DOUBLE_SINGLE_TAP: register_code16(KC_SPACE); break;
    }
}

void space_mac_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(15);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_SPACE); break;
        case SINGLE_HOLD: unregister_code16(KC_SPACE); break;
        case DOUBLE_TAP: unregister_code16(KC_TAB); break;
        case DOUBLE_HOLD: break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_SPACE); break;
    }
    dance_state.step = 0;
}

void on_tgl_backlight(tap_dance_state_t *state, void *user_data);
void tgl_backlight_finished(tap_dance_state_t *state, void *user_data);
void tgl_backlight_reset(tap_dance_state_t *state, void *user_data);

void on_tgl_backlight(tap_dance_state_t *state, void *user_data) {}

uint8_t tgl_backlight_dance_step(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}

void tgl_backlight_finished(tap_dance_state_t *state, void *user_data) {
    dance_state.step = tgl_backlight_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: rgblight_toggle(); break;
        case SINGLE_HOLD :  rgblight_toggle(); break;
        case DOUBLE_TAP: rgblight_toggle(); break;
        case DOUBLE_HOLD:  rgblight_toggle(); break;
    }
}

void tgl_backlight_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(19);
    switch (dance_state.step) {
        case SINGLE_TAP: break;
        case SINGLE_HOLD: break;
        case DOUBLE_TAP: break;
        case DOUBLE_HOLD: break;
    }
    dance_state.step = 0;
}

tap_dance_action_t tap_dance_actions[] = {
        [WIN_ESCAPE] = ACTION_TAP_DANCE_FN_ADVANCED(on_win_escape, win_escape_finished, win_escape_reset),
        [WIN_LBRACKET] = ACTION_TAP_DANCE_FN_ADVANCED(on_win_lbracket, win_lbracket_finished, win_lbracket_reset),
        [WIN_RBRACKET] = ACTION_TAP_DANCE_FN_ADVANCED(on_win_rbracket, win_rbracket_finished, win_rbracket_reset),
        [MAC_ESCAPE] = ACTION_TAP_DANCE_FN_ADVANCED(on_mac_escape, mac_escape_finished, mac_escape_reset),
        [MAC_LBRACKET] = ACTION_TAP_DANCE_FN_ADVANCED(on_mac_lbracket, mac_lbracket_finished, mac_lbracket_reset),
        [MACCOPYPASTA] = ACTION_TAP_DANCE_FN_ADVANCED(on_mac_copypasta, mac_copypasta_finished, mac_copypasta_reset),
        [MAC_RBRACKET] = ACTION_TAP_DANCE_FN_ADVANCED(on_mac_rbracket, mac_rbracket_finished, mac_rbracket_reset),
        [MAC_VOL_DOWN_MUTE] = ACTION_TAP_DANCE_FN_ADVANCED(on_mac_voldown_mute, mac_voldown_mute_finished, mac_voldown_mute_reset),
        [MAC_REPLACE] = ACTION_TAP_DANCE_FN_ADVANCED(on_mac_replace, mac_replace_finished, mac_replace_reset),
        [MAC_FIND] = ACTION_TAP_DANCE_FN_ADVANCED(on_mac_find, mac_find_finished, mac_find_reset),
        [WIN_REPLACE] = ACTION_TAP_DANCE_FN_ADVANCED(on_win_replace, win_replace_finished, win_replace_reset),
        [WIN_FIND] = ACTION_TAP_DANCE_FN_ADVANCED(on_win_find, win_find_finished, win_find_reset),
        [WINCOPYPASTA] = ACTION_TAP_DANCE_FN_ADVANCED(on_win_copypasta, win_copypasta_finished, win_copypasta_reset),
        [ENTER_MAC] = ACTION_TAP_DANCE_FN_ADVANCED(on_enter_mac, enter_mac_finished, enter_mac_reset),
        [MAC_SPACE] = ACTION_TAP_DANCE_FN_ADVANCED(on_space_mac, space_mac_finished, space_mac_reset),
        [ENTER_WIN] = ACTION_TAP_DANCE_FN_ADVANCED(on_enter_win, enter_win_finished, enter_win_reset),
        [MAC_CREDS] = ACTION_TAP_DANCE_FN_ADVANCED(on_mac_creds, mac_creds_finished, mac_creds_reset),
        [LAYER_SWAP] = ACTION_TAP_DANCE_FN_ADVANCED(on_layer_swap, layer_swap_finished, layer_swap_reset),
        [TOGGLE_BACKLIGHT] = ACTION_TAP_DANCE_FN_ADVANCED(on_tgl_backlight,tgl_backlight_finished, tgl_backlight_reset),
};
