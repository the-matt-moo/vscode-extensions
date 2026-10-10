#include QMK_KEYBOARD_H
#include "version.h"
#define MOON_LED_LEVEL LED_LEVEL
#define ML_SAFE_RANGE SAFE_RANGE

enum custom_keycodes {
  RGB_SLD = ML_SAFE_RANGE,
  ST_MACRO_0,
  ST_MACRO_1,
};

enum tap_dance_codes {
  DANCE_0,
  DANCE_1,
  DANCE_2,
  DANCE_3,
  DANCE_4,
  DANCE_5,
  DANCE_6,
  DANCE_7,
  DANCE_8,
  DANCE_9,
  DANCE_10,
  DANCE_11,
  DANCE_12,
  DANCE_13,
  DANCE_14,
  DANCE_15,
  DANCE_16,
  DANCE_17,
  DANCE_18,
  DANCE_19,
  DANCE_20,
  DANCE_21,
  DANCE_22,
  DANCE_23,
  DANCE_24,
  DANCE_25,
  DANCE_26,
  DANCE_27,
  DANCE_28,
  DANCE_29,
  DANCE_30,
  DANCE_31,
  DANCE_32,
  DANCE_33,
  DANCE_34,
  DANCE_35,
  DANCE_36,
  DANCE_37,
  DANCE_38,
  DANCE_39,
  DANCE_40,
  DANCE_41,
  DANCE_42,
  DANCE_43,
  DANCE_44,
  DANCE_45,
  DANCE_46,
  DANCE_47,
  DANCE_48,
  DANCE_49,
  DANCE_50,
  DANCE_51,
  DANCE_52,
  DANCE_53,
  DANCE_54,
  DANCE_55,
  DANCE_56,
  DANCE_57,
  DANCE_58,
  DANCE_59,
  DANCE_60,
  DANCE_61,
  DANCE_62,
  DANCE_63,
  DANCE_64,
  DANCE_65,
  DANCE_66,
  DANCE_67,
  DANCE_68,
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_moonlander(
    TD(DANCE_0),    KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           ST_MACRO_0,                                     TD(DANCE_12),   KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           TD(DANCE_13),
    KC_TAB,         KC_Q,           TD(DANCE_1),    KC_E,           TD(DANCE_2),    KC_T,           KC_TRANSPARENT,                                 LALT(LGUI(KC_B)),KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           TD(DANCE_14),
    MO(2),          TD(DANCE_3),    TD(DANCE_4),    TD(DANCE_5),    TD(DANCE_6),    KC_G,           TD(DANCE_7),                                                                    TD(DANCE_15),   TD(DANCE_16),   TD(DANCE_17),   TD(DANCE_18),   TD(DANCE_19),   TD(DANCE_20),   TD(DANCE_21),
    KC_LEFT_SHIFT,  TD(DANCE_8),    TD(DANCE_9),    TD(DANCE_10),   TD(DANCE_11),   KC_B,                                           KC_N,           KC_M,           TD(DANCE_22),   TD(DANCE_23),   TD(DANCE_24),   TD(DANCE_25),
    KC_LEFT_CTRL,   KC_LEFT_ALT,    KC_LEFT_GUI,    TG(1),          KC_HOME,        KC_LEFT_SHIFT,                                                                                                  KC_ENTER,       KC_END,         LGUI(KC_R),     LALT(KC_F),     TD(DANCE_26),   KC_AUDIO_VOL_UP,
    KC_BSPC,        KC_DELETE,      KC_TRANSPARENT,                 TD(DANCE_27),   TD(DANCE_28),   KC_SPACE
  ),
  [1] = LAYOUT_moonlander(
    TD(DANCE_29),   TD(DANCE_30),   TD(DANCE_31),   TD(DANCE_32),   TD(DANCE_33),   TD(DANCE_34),   ST_MACRO_1,                                     TD(DANCE_47),   TD(DANCE_48),   TD(DANCE_49),   TD(DANCE_50),   TD(DANCE_51),   TD(DANCE_52),   TD(DANCE_53),
    KC_TAB,         KC_Q,           TD(DANCE_35),   KC_E,           TD(DANCE_36),   KC_T,           KC_TRANSPARENT,                                 LCTL(LSFT(KC_T)),KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           TD(DANCE_54),
    MO(3),          TD(DANCE_37),   TD(DANCE_38),   TD(DANCE_39),   TD(DANCE_40),   KC_G,           TD(DANCE_41),                                                                   TD(DANCE_55),   TD(DANCE_56),   TD(DANCE_57),   TD(DANCE_58),   TD(DANCE_59),   TD(DANCE_60),   TD(DANCE_61),
    KC_LEFT_SHIFT,  TD(DANCE_42),   TD(DANCE_43),   TD(DANCE_44),   TD(DANCE_45),   KC_B,                                           KC_N,           KC_M,           TD(DANCE_62),   TD(DANCE_63),   TD(DANCE_64),   TD(DANCE_65),
    KC_LEFT_CTRL,   KC_LEFT_ALT,    KC_LEFT_GUI,    KC_TRANSPARENT, KC_HOME,        KC_LEFT_SHIFT,                                                                                                  KC_ENTER,       KC_END,         LGUI(LCTL(KC_G)),LCTL(KC_F2),    TD(DANCE_66),   KC_AUDIO_VOL_UP,
    KC_BSPC,        KC_DELETE,      TD(DANCE_46),                   TD(DANCE_67),   TD(DANCE_68),   KC_SPACE
  ),
  [2] = LAYOUT_moonlander(
    KC_GRAVE,       KC_KP_1,        KC_KP_2,        KC_KP_3,        KC_KP_4,        KC_KP_5,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_KP_6,        KC_KP_7,        KC_KP_8,        KC_KP_9,        KC_KP_0,        KC_KP_MINUS,
    KC_TAB,         KC_TRANSPARENT, KC_UP,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_F7,          KC_F8,          KC_F9,          KC_TRANSPARENT, KC_TRANSPARENT, KC_KP_PLUS,
    KC_TRANSPARENT, KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_F4,          KC_F5,          KC_F6,          KC_TRANSPARENT, KC_TRANSPARENT, KC_DQUO,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_F1,          KC_F2,          KC_F3,          KC_KP_DOT,      KC_TRANSPARENT, KC_PIPE,
    KC_LEFT_CTRL,   RGB_VAD,        RGB_VAI,        KC_TRANSPARENT, KC_TRANSPARENT, KC_MEDIA_STOP,                                                                                                  KC_MEDIA_PLAY_PAUSE,KC_F10,         KC_TRANSPARENT, KC_TRANSPARENT, KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_MEDIA_PREV_TRACK,                KC_MEDIA_NEXT_TRACK,LSFT(KC_TAB),   KC_TRANSPARENT
  ),
  [3] = LAYOUT_moonlander(
    KC_GRAVE,       KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_UNDS,
    KC_TAB,         KC_F11,         KC_UP,          KC_F13,         KC_F14,         KC_F15,         KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_KP_7,        KC_KP_8,        KC_KP_9,        KC_KP_ASTERISK, KC_TRANSPARENT, KC_PLUS,
    KC_TRANSPARENT, KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_KP_4,        KC_KP_5,        KC_KP_6,        KC_KP_SLASH,    KC_COLN,        KC_DQUO,
    KC_TRANSPARENT, KC_F14,         KC_F15,         KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_KP_1,        KC_KP_2,        KC_KP_3,        KC_KP_PLUS,     KC_QUES,        KC_PIPE,
    KC_LEFT_CTRL,   RGB_VAD,        RGB_VAI,        KC_TRANSPARENT, KC_TRANSPARENT, LCTL(KC_SPACE),                                                                                                 LCTL(LSFT(KC_S)),KC_KP_0,        KC_KP_DOT,      KC_KP_MINUS,    KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,
    KC_DELETE,      KC_TRANSPARENT, LCTL(LSFT(KC_LEFT)),                LCTL(LSFT(KC_RIGHT)),LSFT(KC_TAB),   KC_TRANSPARENT
  ),
};

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}


const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [0] = { {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217}, {153,195,217} },

    [1] = { {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255}, {217,253,255} },

    [2] = { {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {154,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {35,255,255}, {154,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {35,255,255}, {154,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {154,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {154,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {146,224,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {154,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {154,255,255}, {0,0,255}, {0,0,255}, {154,255,255}, {0,0,255}, {154,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {154,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {154,255,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255} },

    [3] = { {0,13,221}, {31,255,255}, {31,255,255}, {0,0,255}, {0,0,255}, {85,203,158}, {0,13,221}, {0,13,221}, {31,255,255}, {0,0,134}, {85,203,158}, {0,245,245}, {0,245,245}, {31,255,255}, {0,0,255}, {85,203,158}, {0,13,221}, {0,245,245}, {31,255,255}, {0,245,245}, {85,203,158}, {0,13,221}, {31,255,255}, {31,255,255}, {0,13,221}, {85,203,158}, {0,13,221}, {31,255,255}, {31,255,255}, {0,245,245}, {0,13,221}, {31,255,255}, {0,245,245}, {0,245,245}, {31,255,255}, {31,255,255}, {31,255,255}, {0,13,221}, {31,255,255}, {31,255,255}, {0,13,221}, {85,203,158}, {0,13,221}, {31,255,255}, {31,255,255}, {0,13,221}, {85,203,158}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {85,203,158}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {85,203,158}, {154,255,255}, {154,255,255}, {154,255,255}, {154,255,255}, {85,203,158}, {154,255,255}, {154,255,255}, {154,255,255}, {0,245,245}, {31,255,255}, {31,255,255}, {31,255,255}, {31,255,255}, {31,255,255}, {31,255,255} },

};

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
  if (rawhid_state.rgb_control) {
      return false;
  }
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
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ST_MACRO_0:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_SCRL) SS_DELAY(100) SS_TAP(X_SCRL) SS_DELAY(100) SS_TAP(X_2));
    }
    break;
    case ST_MACRO_1:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_SCRL) SS_DELAY(100) SS_TAP(X_SCRL) SS_DELAY(100) SS_TAP(X_1));
    }
    break;

    case RGB_SLD:
        if (rawhid_state.rgb_control) {
            return false;
        }
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

static tap dance_state[69];

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


void on_dance_0(tap_dance_state_t *state, void *user_data);
void dance_0_finished(tap_dance_state_t *state, void *user_data);
void dance_0_reset(tap_dance_state_t *state, void *user_data);

void on_dance_0(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_ESCAPE);
        tap_code16(KC_ESCAPE);
        tap_code16(KC_ESCAPE);
    }
    if(state->count > 3) {
        tap_code16(KC_ESCAPE);
    }
}

void dance_0_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step) {
        case SINGLE_TAP: register_code16(KC_ESCAPE); break;
        case DOUBLE_TAP: register_code16(KC_GRAVE); break;
        case DOUBLE_HOLD: register_code16(LSFT(KC_GRAVE)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_ESCAPE); register_code16(KC_ESCAPE);
    }
}

void dance_0_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[0].step) {
        case SINGLE_TAP: unregister_code16(KC_ESCAPE); break;
        case DOUBLE_TAP: unregister_code16(KC_GRAVE); break;
        case DOUBLE_HOLD: unregister_code16(LSFT(KC_GRAVE)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_ESCAPE); break;
    }
    dance_state[0].step = 0;
}
void on_dance_1(tap_dance_state_t *state, void *user_data);
void dance_1_finished(tap_dance_state_t *state, void *user_data);
void dance_1_reset(tap_dance_state_t *state, void *user_data);

void on_dance_1(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_W);
        tap_code16(KC_W);
        tap_code16(KC_W);
    }
    if(state->count > 3) {
        tap_code16(KC_W);
    }
}

void dance_1_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step) {
        case SINGLE_TAP: register_code16(KC_W); break;
        case SINGLE_HOLD: register_code16(KC_W); break;
        case DOUBLE_TAP: register_code16(KC_W); register_code16(KC_W); break;
        case DOUBLE_HOLD: register_code16(KC_UP); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_W); register_code16(KC_W);
    }
}

void dance_1_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[1].step) {
        case SINGLE_TAP: unregister_code16(KC_W); break;
        case SINGLE_HOLD: unregister_code16(KC_W); break;
        case DOUBLE_TAP: unregister_code16(KC_W); break;
        case DOUBLE_HOLD: unregister_code16(KC_UP); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_W); break;
    }
    dance_state[1].step = 0;
}
void on_dance_2(tap_dance_state_t *state, void *user_data);
void dance_2_finished(tap_dance_state_t *state, void *user_data);
void dance_2_reset(tap_dance_state_t *state, void *user_data);

void on_dance_2(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_R);
        tap_code16(KC_R);
        tap_code16(KC_R);
    }
    if(state->count > 3) {fff
        tap_code16(KC_R);
    }
}

void dance_2_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[2].step = dance_step(state);
    switch (dance_state[2].step) {
        case SINGLE_TAP: register_code16(KC_R); break;
        case SINGLE_HOLD: register_code16(LCTL(KC_R)); break;
        case DOUBLE_TAP: register_code16(KC_R); register_code16(KC_R); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_R); register_code16(KC_R);
    }
}

void dance_2_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[2].step) {
        case SINGLE_TAP: unregister_code16(KC_R); break;
        case SINGLE_HOLD: unregister_code16(LCTL(KC_R)); break;
        case DOUBLE_TAP: unregister_code16(KC_R); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_R); break;
    }
    dance_state[2].step = 0;
}
void on_dance_3(tap_dance_state_t *state, void *user_data);
void dance_3_finished(tap_dance_state_t *state, void *user_data);
void dance_3_reset(tap_dance_state_t *state, void *user_data);

void on_dance_3(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_A);
        tap_code16(KC_A);
        tap_code16(KC_A);
    }
    if(state->count > 3) {
        tap_code16(KC_A);
    }
}

void dance_3_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[3].step = dance_step(state);
    switch (dance_state[3].step) {
        case SINGLE_TAP: register_code16(KC_A); break;
        case SINGLE_HOLD: register_code16(KC_A); break;
        case DOUBLE_TAP: register_code16(KC_A); register_code16(KC_A); break;
        case DOUBLE_HOLD: register_code16(KC_LEFT); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_A); register_code16(KC_A);
    }
}

void dance_3_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[3].step) {
        case SINGLE_TAP: unregister_code16(KC_A); break;
        case SINGLE_HOLD: unregister_code16(KC_A); break;
        case DOUBLE_TAP: unregister_code16(KC_A); break;
        case DOUBLE_HOLD: unregister_code16(KC_LEFT); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_A); break;
    }
    dance_state[3].step = 0;
}
void on_dance_4(tap_dance_state_t *state, void *user_data);
void dance_4_finished(tap_dance_state_t *state, void *user_data);
void dance_4_reset(tap_dance_state_t *state, void *user_data);

void on_dance_4(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_S);
        tap_code16(KC_S);
        tap_code16(KC_S);
    }
    if(state->count > 3) {
        tap_code16(KC_S);
    }
}

void dance_4_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[4].step = dance_step(state);
    switch (dance_state[4].step) {
        case SINGLE_TAP: register_code16(KC_S); break;
        case SINGLE_HOLD: register_code16(KC_S); break;
        case DOUBLE_TAP: register_code16(KC_S); register_code16(KC_S); break;
        case DOUBLE_HOLD: register_code16(KC_DOWN); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_S); register_code16(KC_S);
    }
}

void dance_4_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[4].step) {
        case SINGLE_TAP: unregister_code16(KC_S); break;
        case SINGLE_HOLD: unregister_code16(KC_S); break;
        case DOUBLE_TAP: unregister_code16(KC_S); break;
        case DOUBLE_HOLD: unregister_code16(KC_DOWN); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_S); break;
    }
    dance_state[4].step = 0;
}
void on_dance_5(tap_dance_state_t *state, void *user_data);
void dance_5_finished(tap_dance_state_t *state, void *user_data);
void dance_5_reset(tap_dance_state_t *state, void *user_data);

void on_dance_5(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_D);
        tap_code16(KC_D);
        tap_code16(KC_D);
    }
    if(state->count > 3) {
        tap_code16(KC_D);
    }
}

void dance_5_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[5].step = dance_step(state);
    switch (dance_state[5].step) {
        case SINGLE_TAP: register_code16(KC_D); break;
        case SINGLE_HOLD: register_code16(KC_D); break;
        case DOUBLE_TAP: register_code16(KC_D); register_code16(KC_D); break;
        case DOUBLE_HOLD: register_code16(KC_RIGHT); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_D); register_code16(KC_D);
    }
}

void dance_5_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[5].step) {
        case SINGLE_TAP: unregister_code16(KC_D); break;
        case SINGLE_HOLD: unregister_code16(KC_D); break;
        case DOUBLE_TAP: unregister_code16(KC_D); break;
        case DOUBLE_HOLD: unregister_code16(KC_RIGHT); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_D); break;
    }
    dance_state[5].step = 0;
}
void on_dance_6(tap_dance_state_t *state, void *user_data);
void dance_6_finished(tap_dance_state_t *state, void *user_data);
void dance_6_reset(tap_dance_state_t *state, void *user_data);

void on_dance_6(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_F);
        tap_code16(KC_F);
        tap_code16(KC_F);
    }
    if(state->count > 3) {
        tap_code16(KC_F);
    }
}

void dance_6_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[6].step = dance_step(state);
    switch (dance_state[6].step) {
        case SINGLE_TAP: register_code16(KC_F); break;
        case SINGLE_HOLD: register_code16(LCTL(KC_F)); break;
        case DOUBLE_TAP: register_code16(KC_F); register_code16(KC_F); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_F); register_code16(KC_F);
    }
}

void dance_6_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[6].step) {
        case SINGLE_TAP: unregister_code16(KC_F); break;
        case SINGLE_HOLD: unregister_code16(LCTL(KC_F)); break;
        case DOUBLE_TAP: unregister_code16(KC_F); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_F); break;
    }
    dance_state[6].step = 0;
}
void on_dance_7(tap_dance_state_t *state, void *user_data);
void dance_7_finished(tap_dance_state_t *state, void *user_data);
void dance_7_reset(tap_dance_state_t *state, void *user_data);

void on_dance_7(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_LBRC);
        tap_code16(KC_LBRC);
        tap_code16(KC_LBRC);
    }
    if(state->count > 3) {
        tap_code16(KC_LBRC);
    }
}

void dance_7_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[7].step = dance_step(state);
    switch (dance_state[7].step) {
        case SINGLE_TAP: register_code16(KC_LBRC); break;
        case SINGLE_HOLD: register_code16(LSFT(KC_9)); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_LBRC)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_LBRC); register_code16(KC_LBRC);
    }
}

void dance_7_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[7].step) {
        case SINGLE_TAP: unregister_code16(KC_LBRC); break;
        case SINGLE_HOLD: unregister_code16(LSFT(KC_9)); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_LBRC)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_LBRC); break;
    }
    dance_state[7].step = 0;
}
void on_dance_8(tap_dance_state_t *state, void *user_data);
void dance_8_finished(tap_dance_state_t *state, void *user_data);
void dance_8_reset(tap_dance_state_t *state, void *user_data);

void on_dance_8(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_Z);
        tap_code16(KC_Z);
        tap_code16(KC_Z);
    }
    if(state->count > 3) {
        tap_code16(KC_Z);
    }
}

void dance_8_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[8].step = dance_step(state);
    switch (dance_state[8].step) {
        case SINGLE_TAP: register_code16(KC_Z); break;
        case SINGLE_HOLD: register_code16(KC_Z); break;
        case DOUBLE_TAP: register_code16(LCTL(KC_Z)); break;
        case DOUBLE_HOLD: register_code16(LCTL(LSFT(KC_Z))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_Z); register_code16(KC_Z);
    }
}

void dance_8_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[8].step) {
        case SINGLE_TAP: unregister_code16(KC_Z); break;
        case SINGLE_HOLD: unregister_code16(KC_Z); break;
        case DOUBLE_TAP: unregister_code16(LCTL(KC_Z)); break;
        case DOUBLE_HOLD: unregister_code16(LCTL(LSFT(KC_Z))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_Z); break;
    }
    dance_state[8].step = 0;
}
void on_dance_9(tap_dance_state_t *state, void *user_data);
void dance_9_finished(tap_dance_state_t *state, void *user_data);
void dance_9_reset(tap_dance_state_t *state, void *user_data);

void on_dance_9(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_X);
        tap_code16(KC_X);
        tap_code16(KC_X);
    }
    if(state->count > 3) {
        tap_code16(KC_X);
    }
}

void dance_9_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[9].step = dance_step(state);
    switch (dance_state[9].step) {
        case SINGLE_TAP: register_code16(KC_X); break;
        case SINGLE_HOLD: register_code16(KC_X); break;
        case DOUBLE_TAP: register_code16(RCTL(KC_X)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_X); register_code16(KC_X);
    }
}

void dance_9_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[9].step) {
        case SINGLE_TAP: unregister_code16(KC_X); break;
        case SINGLE_HOLD: unregister_code16(KC_X); break;
        case DOUBLE_TAP: unregister_code16(RCTL(KC_X)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_X); break;
    }
    dance_state[9].step = 0;
}
void on_dance_10(tap_dance_state_t *state, void *user_data);
void dance_10_finished(tap_dance_state_t *state, void *user_data);
void dance_10_reset(tap_dance_state_t *state, void *user_data);

void on_dance_10(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_C);
        tap_code16(KC_C);
        tap_code16(KC_C);
    }
    if(state->count > 3) {
        tap_code16(KC_C);
    }
}

void dance_10_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[10].step = dance_step(state);
    switch (dance_state[10].step) {
        case SINGLE_TAP: register_code16(KC_C); break;
        case SINGLE_HOLD: register_code16(KC_C); break;
        case DOUBLE_TAP: register_code16(LCTL(KC_C)); break;
        case DOUBLE_HOLD: register_code16(LGUI(KC_C)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_C); register_code16(KC_C);
    }
}

void dance_10_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[10].step) {
        case SINGLE_TAP: unregister_code16(KC_C); break;
        case SINGLE_HOLD: unregister_code16(KC_C); break;
        case DOUBLE_TAP: unregister_code16(LCTL(KC_C)); break;
        case DOUBLE_HOLD: unregister_code16(LGUI(KC_C)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_C); break;
    }
    dance_state[10].step = 0;
}
void on_dance_11(tap_dance_state_t *state, void *user_data);
void dance_11_finished(tap_dance_state_t *state, void *user_data);
void dance_11_reset(tap_dance_state_t *state, void *user_data);

void on_dance_11(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_V);
        tap_code16(KC_V);
        tap_code16(KC_V);
    }
    if(state->count > 3) {
        tap_code16(KC_V);
    }
}

void dance_11_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[11].step = dance_step(state);
    switch (dance_state[11].step) {
        case SINGLE_TAP: register_code16(KC_V); break;
        case SINGLE_HOLD: register_code16(KC_V); break;
        case DOUBLE_TAP: register_code16(LCTL(KC_V)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_V); register_code16(KC_V);
    }
}

void dance_11_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[11].step) {
        case SINGLE_TAP: unregister_code16(KC_V); break;
        case SINGLE_HOLD: unregister_code16(KC_V); break;
        case DOUBLE_TAP: unregister_code16(LCTL(KC_V)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_V); break;
    }
    dance_state[11].step = 0;
}
void on_dance_12(tap_dance_state_t *state, void *user_data);
void dance_12_finished(tap_dance_state_t *state, void *user_data);
void dance_12_reset(tap_dance_state_t *state, void *user_data);

void on_dance_12(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(LCTL(KC_F));
        tap_code16(LCTL(KC_F));
        tap_code16(LCTL(KC_F));
    }
    if(state->count > 3) {
        tap_code16(LCTL(KC_F));
    }
}

void dance_12_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[12].step = dance_step(state);
    switch (dance_state[12].step) {
        case SINGLE_TAP: register_code16(LCTL(KC_F)); break;
        case DOUBLE_TAP: register_code16(LCTL(KC_H)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(LCTL(KC_F)); register_code16(LCTL(KC_F));
    }
}

void dance_12_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[12].step) {
        case SINGLE_TAP: unregister_code16(LCTL(KC_F)); break;
        case DOUBLE_TAP: unregister_code16(LCTL(KC_H)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(LCTL(KC_F)); break;
    }
    dance_state[12].step = 0;
}
void on_dance_13(tap_dance_state_t *state, void *user_data);
void dance_13_finished(tap_dance_state_t *state, void *user_data);
void dance_13_reset(tap_dance_state_t *state, void *user_data);

void on_dance_13(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_MINUS);
        tap_code16(KC_MINUS);
        tap_code16(KC_MINUS);
    }
    if(state->count > 3) {
        tap_code16(KC_MINUS);
    }
}

void dance_13_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[13].step = dance_step(state);
    switch (dance_state[13].step) {
        case SINGLE_TAP: register_code16(KC_MINUS); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_MINUS)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_MINUS); register_code16(KC_MINUS);
    }
}

void dance_13_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[13].step) {
        case SINGLE_TAP: unregister_code16(KC_MINUS); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_MINUS)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_MINUS); break;
    }
    dance_state[13].step = 0;
}
void on_dance_14(tap_dance_state_t *state, void *user_data);
void dance_14_finished(tap_dance_state_t *state, void *user_data);
void dance_14_reset(tap_dance_state_t *state, void *user_data);

void on_dance_14(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_EQUAL);
        tap_code16(KC_EQUAL);
        tap_code16(KC_EQUAL);
    }
    if(state->count > 3) {
        tap_code16(KC_EQUAL);
    }
}

void dance_14_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[14].step = dance_step(state);
    switch (dance_state[14].step) {
        case SINGLE_TAP: register_code16(KC_EQUAL); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_EQUAL)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_EQUAL); register_code16(KC_EQUAL);
    }
}

void dance_14_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[14].step) {
        case SINGLE_TAP: unregister_code16(KC_EQUAL); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_EQUAL)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_EQUAL); break;
    }
    dance_state[14].step = 0;
}
void on_dance_15(tap_dance_state_t *state, void *user_data);
void dance_15_finished(tap_dance_state_t *state, void *user_data);
void dance_15_reset(tap_dance_state_t *state, void *user_data);

void on_dance_15(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_RBRC);
        tap_code16(KC_RBRC);
        tap_code16(KC_RBRC);
    }
    if(state->count > 3) {
        tap_code16(KC_RBRC);
    }
}

void dance_15_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[15].step = dance_step(state);
    switch (dance_state[15].step) {
        case SINGLE_TAP: register_code16(KC_RBRC); break;
        case SINGLE_HOLD: register_code16(LSFT(KC_0)); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_RBRC)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_RBRC); register_code16(KC_RBRC);
    }
}

void dance_15_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[15].step) {
        case SINGLE_TAP: unregister_code16(KC_RBRC); break;
        case SINGLE_HOLD: unregister_code16(LSFT(KC_0)); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_RBRC)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_RBRC); break;
    }
    dance_state[15].step = 0;
}
void on_dance_16(tap_dance_state_t *state, void *user_data);
void dance_16_finished(tap_dance_state_t *state, void *user_data);
void dance_16_reset(tap_dance_state_t *state, void *user_data);

void on_dance_16(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_H);
        tap_code16(KC_H);
        tap_code16(KC_H);
    }
    if(state->count > 3) {
        tap_code16(KC_H);
    }
}

void dance_16_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[16].step = dance_step(state);
    switch (dance_state[16].step) {
        case SINGLE_TAP: register_code16(KC_H); break;
        case SINGLE_HOLD: register_code16(KC_H); break;
        case DOUBLE_TAP: register_code16(KC_H); register_code16(KC_H); break;
        case DOUBLE_HOLD: register_code16(KC_LEFT); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_H); register_code16(KC_H);
    }
}

void dance_16_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[16].step) {
        case SINGLE_TAP: unregister_code16(KC_H); break;
        case SINGLE_HOLD: unregister_code16(KC_H); break;
        case DOUBLE_TAP: unregister_code16(KC_H); break;
        case DOUBLE_HOLD: unregister_code16(KC_LEFT); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_H); break;
    }
    dance_state[16].step = 0;
}
void on_dance_17(tap_dance_state_t *state, void *user_data);
void dance_17_finished(tap_dance_state_t *state, void *user_data);
void dance_17_reset(tap_dance_state_t *state, void *user_data);

void on_dance_17(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_J);
        tap_code16(KC_J);
        tap_code16(KC_J);
    }
    if(state->count > 3) {
        tap_code16(KC_J);
    }
}

void dance_17_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[17].step = dance_step(state);
    switch (dance_state[17].step) {
        case SINGLE_TAP: register_code16(KC_J); break;
        case SINGLE_HOLD: register_code16(KC_J); break;
        case DOUBLE_TAP: register_code16(KC_J); register_code16(KC_J); break;
        case DOUBLE_HOLD: register_code16(KC_DOWN); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_J); register_code16(KC_J);
    }
}

void dance_17_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[17].step) {
        case SINGLE_TAP: unregister_code16(KC_J); break;
        case SINGLE_HOLD: unregister_code16(KC_J); break;
        case DOUBLE_TAP: unregister_code16(KC_J); break;
        case DOUBLE_HOLD: unregister_code16(KC_DOWN); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_J); break;
    }
    dance_state[17].step = 0;
}
void on_dance_18(tap_dance_state_t *state, void *user_data);
void dance_18_finished(tap_dance_state_t *state, void *user_data);
void dance_18_reset(tap_dance_state_t *state, void *user_data);

void on_dance_18(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_K);
        tap_code16(KC_K);
        tap_code16(KC_K);
    }
    if(state->count > 3) {
        tap_code16(KC_K);
    }
}

void dance_18_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[18].step = dance_step(state);
    switch (dance_state[18].step) {
        case SINGLE_TAP: register_code16(KC_K); break;
        case SINGLE_HOLD: register_code16(KC_K); break;
        case DOUBLE_TAP: register_code16(KC_K); register_code16(KC_K); break;
        case DOUBLE_HOLD: register_code16(KC_UP); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_K); register_code16(KC_K);
    }
}

void dance_18_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[18].step) {
        case SINGLE_TAP: unregister_code16(KC_K); break;
        case SINGLE_HOLD: unregister_code16(KC_K); break;
        case DOUBLE_TAP: unregister_code16(KC_K); break;
        case DOUBLE_HOLD: unregister_code16(KC_UP); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_K); break;
    }
    dance_state[18].step = 0;
}
void on_dance_19(tap_dance_state_t *state, void *user_data);
void dance_19_finished(tap_dance_state_t *state, void *user_data);
void dance_19_reset(tap_dance_state_t *state, void *user_data);

void on_dance_19(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_L);
        tap_code16(KC_L);
        tap_code16(KC_L);
    }
    if(state->count > 3) {
        tap_code16(KC_L);
    }
}

void dance_19_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[19].step = dance_step(state);
    switch (dance_state[19].step) {
        case SINGLE_TAP: register_code16(KC_L); break;
        case SINGLE_HOLD: register_code16(KC_L); break;
        case DOUBLE_TAP: register_code16(KC_L); register_code16(KC_L); break;
        case DOUBLE_HOLD: register_code16(KC_RIGHT); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_L); register_code16(KC_L);
    }
}

void dance_19_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[19].step) {
        case SINGLE_TAP: unregister_code16(KC_L); break;
        case SINGLE_HOLD: unregister_code16(KC_L); break;
        case DOUBLE_TAP: unregister_code16(KC_L); break;
        case DOUBLE_HOLD: unregister_code16(KC_RIGHT); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_L); break;
    }
    dance_state[19].step = 0;
}
void on_dance_20(tap_dance_state_t *state, void *user_data);
void dance_20_finished(tap_dance_state_t *state, void *user_data);
void dance_20_reset(tap_dance_state_t *state, void *user_data);

void on_dance_20(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_SCLN);
        tap_code16(KC_SCLN);
        tap_code16(KC_SCLN);
    }
    if(state->count > 3) {
        tap_code16(KC_SCLN);
    }
}

void dance_20_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[20].step = dance_step(state);
    switch (dance_state[20].step) {
        case SINGLE_TAP: register_code16(KC_SCLN); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_SCLN)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_SCLN); register_code16(KC_SCLN);
    }
}

void dance_20_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[20].step) {
        case SINGLE_TAP: unregister_code16(KC_SCLN); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_SCLN)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_SCLN); break;
    }
    dance_state[20].step = 0;
}
void on_dance_21(tap_dance_state_t *state, void *user_data);
void dance_21_finished(tap_dance_state_t *state, void *user_data);
void dance_21_reset(tap_dance_state_t *state, void *user_data);

void on_dance_21(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_QUOTE);
        tap_code16(KC_QUOTE);
        tap_code16(KC_QUOTE);
    }
    if(state->count > 3) {
        tap_code16(KC_QUOTE);
    }
}

void dance_21_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[21].step = dance_step(state);
    switch (dance_state[21].step) {
        case SINGLE_TAP: register_code16(KC_QUOTE); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_QUOTE)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_QUOTE); register_code16(KC_QUOTE);
    }
}

void dance_21_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[21].step) {
        case SINGLE_TAP: unregister_code16(KC_QUOTE); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_QUOTE)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_QUOTE); break;
    }
    dance_state[21].step = 0;
}
void on_dance_22(tap_dance_state_t *state, void *user_data);
void dance_22_finished(tap_dance_state_t *state, void *user_data);
void dance_22_reset(tap_dance_state_t *state, void *user_data);

void on_dance_22(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_COMMA);
        tap_code16(KC_COMMA);
        tap_code16(KC_COMMA);
    }
    if(state->count > 3) {
        tap_code16(KC_COMMA);
    }
}

void dance_22_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[22].step = dance_step(state);
    switch (dance_state[22].step) {
        case SINGLE_TAP: register_code16(KC_COMMA); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_COMMA)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_COMMA); register_code16(KC_COMMA);
    }
}

void dance_22_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[22].step) {
        case SINGLE_TAP: unregister_code16(KC_COMMA); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_COMMA)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_COMMA); break;
    }
    dance_state[22].step = 0;
}
void on_dance_23(tap_dance_state_t *state, void *user_data);
void dance_23_finished(tap_dance_state_t *state, void *user_data);
void dance_23_reset(tap_dance_state_t *state, void *user_data);

void on_dance_23(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_DOT);
        tap_code16(KC_DOT);
        tap_code16(KC_DOT);
    }
    if(state->count > 3) {
        tap_code16(KC_DOT);
    }
}

void dance_23_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[23].step = dance_step(state);
    switch (dance_state[23].step) {
        case SINGLE_TAP: register_code16(KC_DOT); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_DOT)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_DOT); register_code16(KC_DOT);
    }
}

void dance_23_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[23].step) {
        case SINGLE_TAP: unregister_code16(KC_DOT); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_DOT)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_DOT); break;
    }
    dance_state[23].step = 0;
}
void on_dance_24(tap_dance_state_t *state, void *user_data);
void dance_24_finished(tap_dance_state_t *state, void *user_data);
void dance_24_reset(tap_dance_state_t *state, void *user_data);

void on_dance_24(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_SLASH);
        tap_code16(KC_SLASH);
        tap_code16(KC_SLASH);
    }
    if(state->count > 3) {
        tap_code16(KC_SLASH);
    }
}

void dance_24_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[24].step = dance_step(state);
    switch (dance_state[24].step) {
        case SINGLE_TAP: register_code16(KC_SLASH); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_SLASH)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_SLASH); register_code16(KC_SLASH);
    }
}

void dance_24_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[24].step) {
        case SINGLE_TAP: unregister_code16(KC_SLASH); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_SLASH)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_SLASH); break;
    }
    dance_state[24].step = 0;
}
void on_dance_25(tap_dance_state_t *state, void *user_data);
void dance_25_finished(tap_dance_state_t *state, void *user_data);
void dance_25_reset(tap_dance_state_t *state, void *user_data);

void on_dance_25(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_BSLS);
        tap_code16(KC_BSLS);
        tap_code16(KC_BSLS);
    }
    if(state->count > 3) {
        tap_code16(KC_BSLS);
    }
}

void dance_25_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[25].step = dance_step(state);
    switch (dance_state[25].step) {
        case SINGLE_TAP: register_code16(KC_BSLS); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_BSLS)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_BSLS); register_code16(KC_BSLS);
    }
}

void dance_25_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[25].step) {
        case SINGLE_TAP: unregister_code16(KC_BSLS); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_BSLS)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_BSLS); break;
    }
    dance_state[25].step = 0;
}
void on_dance_26(tap_dance_state_t *state, void *user_data);
void dance_26_finished(tap_dance_state_t *state, void *user_data);
void dance_26_reset(tap_dance_state_t *state, void *user_data);

void on_dance_26(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_AUDIO_VOL_DOWN);
        tap_code16(KC_AUDIO_VOL_DOWN);
        tap_code16(KC_AUDIO_VOL_DOWN);
    }
    if(state->count > 3) {
        tap_code16(KC_AUDIO_VOL_DOWN);
    }
}

void dance_26_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[26].step = dance_step(state);
    switch (dance_state[26].step) {
        case SINGLE_TAP: register_code16(KC_AUDIO_VOL_DOWN); break;
        case DOUBLE_TAP: register_code16(KC_AUDIO_VOL_DOWN); break;
        case DOUBLE_HOLD: register_code16(KC_AUDIO_MUTE); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_AUDIO_VOL_DOWN); register_code16(KC_AUDIO_VOL_DOWN);
    }
}

void dance_26_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[26].step) {
        case SINGLE_TAP: unregister_code16(KC_AUDIO_VOL_DOWN); break;
        case DOUBLE_TAP: unregister_code16(KC_AUDIO_VOL_DOWN); break;
        case DOUBLE_HOLD: unregister_code16(KC_AUDIO_MUTE); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_AUDIO_VOL_DOWN); break;
    }
    dance_state[26].step = 0;
}
void on_dance_27(tap_dance_state_t *state, void *user_data);
void dance_27_finished(tap_dance_state_t *state, void *user_data);
void dance_27_reset(tap_dance_state_t *state, void *user_data);

void on_dance_27(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_RIGHT);
        tap_code16(KC_RIGHT);
        tap_code16(KC_RIGHT);
    }
    if(state->count > 3) {
        tap_code16(KC_RIGHT);
    }
}

void dance_27_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[27].step = dance_step(state);
    switch (dance_state[27].step) {
        case SINGLE_TAP: register_code16(KC_RIGHT); break;
        case SINGLE_HOLD: register_code16(KC_RIGHT); break;
        case DOUBLE_TAP: register_code16(KC_RIGHT); break;
        case DOUBLE_HOLD: register_code16(LCTL(LGUI(KC_RIGHT))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_RIGHT); register_code16(KC_RIGHT);
    }
}

void dance_27_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[27].step) {
        case SINGLE_TAP: unregister_code16(KC_RIGHT); break;
        case SINGLE_HOLD: unregister_code16(KC_RIGHT); break;
        case DOUBLE_TAP: unregister_code16(KC_RIGHT); break;
        case DOUBLE_HOLD: unregister_code16(LCTL(LGUI(KC_RIGHT))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_RIGHT); break;
    }
    dance_state[27].step = 0;
}
void on_dance_28(tap_dance_state_t *state, void *user_data);
void dance_28_finished(tap_dance_state_t *state, void *user_data);
void dance_28_reset(tap_dance_state_t *state, void *user_data);

void on_dance_28(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_TAB);
        tap_code16(KC_TAB);
        tap_code16(KC_TAB);
    }
    if(state->count > 3) {
        tap_code16(KC_TAB);
    }
}

void dance_28_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[28].step = dance_step(state);
    switch (dance_state[28].step) {
        case SINGLE_TAP: register_code16(KC_TAB); break;
        case DOUBLE_TAP: register_code16(KC_TAB); register_code16(KC_TAB); break;
        case DOUBLE_HOLD: register_code16(LSFT(KC_TAB)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_TAB); register_code16(KC_TAB);
    }
}

void dance_28_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[28].step) {
        case SINGLE_TAP: unregister_code16(KC_TAB); break;
        case DOUBLE_TAP: unregister_code16(KC_TAB); break;
        case DOUBLE_HOLD: unregister_code16(LSFT(KC_TAB)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_TAB); break;
    }
    dance_state[28].step = 0;
}
void on_dance_29(tap_dance_state_t *state, void *user_data);
void dance_29_finished(tap_dance_state_t *state, void *user_data);
void dance_29_reset(tap_dance_state_t *state, void *user_data);

void on_dance_29(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_ESCAPE);
        tap_code16(KC_ESCAPE);
        tap_code16(KC_ESCAPE);
    }
    if(state->count > 3) {
        tap_code16(KC_ESCAPE);
    }
}

void dance_29_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[29].step = dance_step(state);
    switch (dance_state[29].step) {
        case SINGLE_TAP: register_code16(KC_ESCAPE); break;
        case DOUBLE_TAP: register_code16(KC_GRAVE); break;
        case DOUBLE_HOLD: register_code16(LSFT(KC_GRAVE)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_ESCAPE); register_code16(KC_ESCAPE);
    }
}

void dance_29_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[29].step) {
        case SINGLE_TAP: unregister_code16(KC_ESCAPE); break;
        case DOUBLE_TAP: unregister_code16(KC_GRAVE); break;
        case DOUBLE_HOLD: unregister_code16(LSFT(KC_GRAVE)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_ESCAPE); break;
    }
    dance_state[29].step = 0;
}
void on_dance_30(tap_dance_state_t *state, void *user_data);
void dance_30_finished(tap_dance_state_t *state, void *user_data);
void dance_30_reset(tap_dance_state_t *state, void *user_data);

void on_dance_30(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_1);
        tap_code16(KC_1);
        tap_code16(KC_1);
    }
    if(state->count > 3) {
        tap_code16(KC_1);
    }
}

void dance_30_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[30].step = dance_step(state);
    switch (dance_state[30].step) {
        case SINGLE_TAP: register_code16(KC_1); break;
        case SINGLE_HOLD: register_code16(LSFT(KC_1)); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_1)); break;
        case DOUBLE_HOLD: register_code16(KC_1); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_1); register_code16(KC_1);
    }
}

void dance_30_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[30].step) {
        case SINGLE_TAP: unregister_code16(KC_1); break;
        case SINGLE_HOLD: unregister_code16(LSFT(KC_1)); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_1)); break;
        case DOUBLE_HOLD: unregister_code16(KC_1); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_1); break;
    }
    dance_state[30].step = 0;
}
void on_dance_31(tap_dance_state_t *state, void *user_data);
void dance_31_finished(tap_dance_state_t *state, void *user_data);
void dance_31_reset(tap_dance_state_t *state, void *user_data);

void on_dance_31(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_2);
        tap_code16(KC_2);
        tap_code16(KC_2);
    }
    if(state->count > 3) {
        tap_code16(KC_2);
    }
}

void dance_31_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[31].step = dance_step(state);
    switch (dance_state[31].step) {
        case SINGLE_TAP: register_code16(KC_2); break;
        case SINGLE_HOLD: register_code16(LSFT(KC_2)); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_2)); break;
        case DOUBLE_HOLD: register_code16(KC_2); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_2); register_code16(KC_2);
    }
}

void dance_31_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[31].step) {
        case SINGLE_TAP: unregister_code16(KC_2); break;
        case SINGLE_HOLD: unregister_code16(LSFT(KC_2)); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_2)); break;
        case DOUBLE_HOLD: unregister_code16(KC_2); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_2); break;
    }
    dance_state[31].step = 0;
}
void on_dance_32(tap_dance_state_t *state, void *user_data);
void dance_32_finished(tap_dance_state_t *state, void *user_data);
void dance_32_reset(tap_dance_state_t *state, void *user_data);

void on_dance_32(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_3);
        tap_code16(KC_3);
        tap_code16(KC_3);
    }
    if(state->count > 3) {
        tap_code16(KC_3);
    }
}

void dance_32_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[32].step = dance_step(state);
    switch (dance_state[32].step) {
        case SINGLE_TAP: register_code16(KC_3); break;
        case SINGLE_HOLD: register_code16(LSFT(KC_3)); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_3)); break;
        case DOUBLE_HOLD: register_code16(KC_3); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_3); register_code16(KC_3);
    }
}

void dance_32_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[32].step) {
        case SINGLE_TAP: unregister_code16(KC_3); break;
        case SINGLE_HOLD: unregister_code16(LSFT(KC_3)); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_3)); break;
        case DOUBLE_HOLD: unregister_code16(KC_3); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_3); break;
    }
    dance_state[32].step = 0;
}
void on_dance_33(tap_dance_state_t *state, void *user_data);
void dance_33_finished(tap_dance_state_t *state, void *user_data);
void dance_33_reset(tap_dance_state_t *state, void *user_data);

void on_dance_33(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_4);
        tap_code16(KC_4);
        tap_code16(KC_4);
    }
    if(state->count > 3) {
        tap_code16(KC_4);
    }
}

void dance_33_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[33].step = dance_step(state);
    switch (dance_state[33].step) {
        case SINGLE_TAP: register_code16(KC_4); break;
        case SINGLE_HOLD: register_code16(LSFT(KC_4)); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_4)); break;
        case DOUBLE_HOLD: register_code16(KC_4); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_4); register_code16(KC_4);
    }
}

void dance_33_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[33].step) {
        case SINGLE_TAP: unregister_code16(KC_4); break;
        case SINGLE_HOLD: unregister_code16(LSFT(KC_4)); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_4)); break;
        case DOUBLE_HOLD: unregister_code16(KC_4); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_4); break;
    }
    dance_state[33].step = 0;
}
void on_dance_34(tap_dance_state_t *state, void *user_data);
void dance_34_finished(tap_dance_state_t *state, void *user_data);
void dance_34_reset(tap_dance_state_t *state, void *user_data);

void on_dance_34(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_5);
        tap_code16(KC_5);
        tap_code16(KC_5);
    }
    if(state->count > 3) {
        tap_code16(KC_5);
    }
}

void dance_34_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[34].step = dance_step(state);
    switch (dance_state[34].step) {
        case SINGLE_TAP: register_code16(KC_5); break;
        case SINGLE_HOLD: register_code16(LSFT(KC_5)); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_5)); break;
        case DOUBLE_HOLD: register_code16(KC_5); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_5); register_code16(KC_5);
    }
}

void dance_34_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[34].step) {
        case SINGLE_TAP: unregister_code16(KC_5); break;
        case SINGLE_HOLD: unregister_code16(LSFT(KC_5)); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_5)); break;
        case DOUBLE_HOLD: unregister_code16(KC_5); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_5); break;
    }
    dance_state[34].step = 0;
}
void on_dance_35(tap_dance_state_t *state, void *user_data);
void dance_35_finished(tap_dance_state_t *state, void *user_data);
void dance_35_reset(tap_dance_state_t *state, void *user_data);

void on_dance_35(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_W);
        tap_code16(KC_W);
        tap_code16(KC_W);
    }
    if(state->count > 3) {
        tap_code16(KC_W);
    }
}

void dance_35_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[35].step = dance_step(state);
    switch (dance_state[35].step) {
        case SINGLE_TAP: register_code16(KC_W); break;
        case DOUBLE_TAP: register_code16(KC_W); register_code16(KC_W); break;
        case DOUBLE_HOLD: register_code16(KC_UP); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_W); register_code16(KC_W);
    }
}

void dance_35_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[35].step) {
        case SINGLE_TAP: unregister_code16(KC_W); break;
        case DOUBLE_TAP: unregister_code16(KC_W); break;
        case DOUBLE_HOLD: unregister_code16(KC_UP); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_W); break;
    }
    dance_state[35].step = 0;
}
void on_dance_36(tap_dance_state_t *state, void *user_data);
void dance_36_finished(tap_dance_state_t *state, void *user_data);
void dance_36_reset(tap_dance_state_t *state, void *user_data);

void on_dance_36(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_R);
        tap_code16(KC_R);
        tap_code16(KC_R);
    }
    if(state->count > 3) {
        tap_code16(KC_R);
    }
}

void dance_36_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[36].step = dance_step(state);
    switch (dance_state[36].step) {
        case SINGLE_TAP: register_code16(KC_R); break;
        case SINGLE_HOLD: register_code16(LGUI(KC_R)); break;
        case DOUBLE_TAP: register_code16(KC_R); register_code16(KC_R); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_R); register_code16(KC_R);
    }
}

void dance_36_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[36].step) {
        case SINGLE_TAP: unregister_code16(KC_R); break;
        case SINGLE_HOLD: unregister_code16(LGUI(KC_R)); break;
        case DOUBLE_TAP: unregister_code16(KC_R); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_R); break;
    }
    dance_state[36].step = 0;
}
void on_dance_37(tap_dance_state_t *state, void *user_data);
void dance_37_finished(tap_dance_state_t *state, void *user_data);
void dance_37_reset(tap_dance_state_t *state, void *user_data);

void on_dance_37(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_A);
        tap_code16(KC_A);
        tap_code16(KC_A);
    }
    if(state->count > 3) {
        tap_code16(KC_A);
    }
}

void dance_37_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[37].step = dance_step(state);
    switch (dance_state[37].step) {
        case SINGLE_TAP: register_code16(KC_A); break;
        case SINGLE_HOLD: register_code16(KC_A); break;
        case DOUBLE_TAP: register_code16(KC_A); register_code16(KC_A); break;
        case DOUBLE_HOLD: register_code16(KC_LEFT); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_A); register_code16(KC_A);
    }
}

void dance_37_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[37].step) {
        case SINGLE_TAP: unregister_code16(KC_A); break;
        case SINGLE_HOLD: unregister_code16(KC_A); break;
        case DOUBLE_TAP: unregister_code16(KC_A); break;
        case DOUBLE_HOLD: unregister_code16(KC_LEFT); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_A); break;
    }
    dance_state[37].step = 0;
}
void on_dance_38(tap_dance_state_t *state, void *user_data);
void dance_38_finished(tap_dance_state_t *state, void *user_data);
void dance_38_reset(tap_dance_state_t *state, void *user_data);

void on_dance_38(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_S);
        tap_code16(KC_S);
        tap_code16(KC_S);
    }
    if(state->count > 3) {
        tap_code16(KC_S);
    }
}

void dance_38_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[38].step = dance_step(state);
    switch (dance_state[38].step) {
        case SINGLE_TAP: register_code16(KC_S); break;
        case SINGLE_HOLD: register_code16(KC_S); break;
        case DOUBLE_TAP: register_code16(KC_S); register_code16(KC_S); break;
        case DOUBLE_HOLD: register_code16(KC_DOWN); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_S); register_code16(KC_S);
    }
}

void dance_38_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[38].step) {
        case SINGLE_TAP: unregister_code16(KC_S); break;
        case SINGLE_HOLD: unregister_code16(KC_S); break;
        case DOUBLE_TAP: unregister_code16(KC_S); break;
        case DOUBLE_HOLD: unregister_code16(KC_DOWN); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_S); break;
    }
    dance_state[38].step = 0;
}
void on_dance_39(tap_dance_state_t *state, void *user_data);
void dance_39_finished(tap_dance_state_t *state, void *user_data);
void dance_39_reset(tap_dance_state_t *state, void *user_data);

void on_dance_39(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_D);
        tap_code16(KC_D);
        tap_code16(KC_D);
    }
    if(state->count > 3) {
        tap_code16(KC_D);
    }
}

void dance_39_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[39].step = dance_step(state);
    switch (dance_state[39].step) {
        case SINGLE_TAP: register_code16(KC_D); break;
        case SINGLE_HOLD: register_code16(KC_D); break;
        case DOUBLE_TAP: register_code16(KC_D); register_code16(KC_D); break;
        case DOUBLE_HOLD: register_code16(KC_RIGHT); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_D); register_code16(KC_D);
    }
}

void dance_39_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[39].step) {
        case SINGLE_TAP: unregister_code16(KC_D); break;
        case SINGLE_HOLD: unregister_code16(KC_D); break;
        case DOUBLE_TAP: unregister_code16(KC_D); break;
        case DOUBLE_HOLD: unregister_code16(KC_RIGHT); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_D); break;
    }
    dance_state[39].step = 0;
}
void on_dance_40(tap_dance_state_t *state, void *user_data);
void dance_40_finished(tap_dance_state_t *state, void *user_data);
void dance_40_reset(tap_dance_state_t *state, void *user_data);

void on_dance_40(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_F);
        tap_code16(KC_F);
        tap_code16(KC_F);
    }
    if(state->count > 3) {
        tap_code16(KC_F);
    }
}

void dance_40_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[40].step = dance_step(state);
    switch (dance_state[40].step) {
        case SINGLE_TAP: register_code16(KC_F); break;
        case SINGLE_HOLD: register_code16(LGUI(KC_F)); break;
        case DOUBLE_TAP: register_code16(KC_F); register_code16(KC_F); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_F); register_code16(KC_F);
    }
}

void dance_40_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[40].step) {
        case SINGLE_TAP: unregister_code16(KC_F); break;
        case SINGLE_HOLD: unregister_code16(LGUI(KC_F)); break;
        case DOUBLE_TAP: unregister_code16(KC_F); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_F); break;
    }
    dance_state[40].step = 0;
}
void on_dance_41(tap_dance_state_t *state, void *user_data);
void dance_41_finished(tap_dance_state_t *state, void *user_data);
void dance_41_reset(tap_dance_state_t *state, void *user_data);

void on_dance_41(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_LBRC);
        tap_code16(KC_LBRC);
        tap_code16(KC_LBRC);
    }
    if(state->count > 3) {
        tap_code16(KC_LBRC);
    }
}

void dance_41_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[41].step = dance_step(state);
    switch (dance_state[41].step) {
        case SINGLE_TAP: register_code16(KC_LBRC); break;
        case SINGLE_HOLD: register_code16(LSFT(KC_9)); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_LBRC)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_LBRC); register_code16(KC_LBRC);
    }
}

void dance_41_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[41].step) {
        case SINGLE_TAP: unregister_code16(KC_LBRC); break;
        case SINGLE_HOLD: unregister_code16(LSFT(KC_9)); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_LBRC)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_LBRC); break;
    }
    dance_state[41].step = 0;
}
void on_dance_42(tap_dance_state_t *state, void *user_data);
void dance_42_finished(tap_dance_state_t *state, void *user_data);
void dance_42_reset(tap_dance_state_t *state, void *user_data);

void on_dance_42(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_Z);
        tap_code16(KC_Z);
        tap_code16(KC_Z);
    }
    if(state->count > 3) {
        tap_code16(KC_Z);
    }
}

void dance_42_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[42].step = dance_step(state);
    switch (dance_state[42].step) {
        case SINGLE_TAP: register_code16(KC_Z); break;
        case SINGLE_HOLD: register_code16(KC_Z); break;
        case DOUBLE_TAP: register_code16(LGUI(KC_Z)); break;
        case DOUBLE_HOLD: register_code16(LGUI(LSFT(KC_Z))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_Z); register_code16(KC_Z);
    }
}

void dance_42_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[42].step) {
        case SINGLE_TAP: unregister_code16(KC_Z); break;
        case SINGLE_HOLD: unregister_code16(KC_Z); break;
        case DOUBLE_TAP: unregister_code16(LGUI(KC_Z)); break;
        case DOUBLE_HOLD: unregister_code16(LGUI(LSFT(KC_Z))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_Z); break;
    }
    dance_state[42].step = 0;
}
void on_dance_43(tap_dance_state_t *state, void *user_data);
void dance_43_finished(tap_dance_state_t *state, void *user_data);
void dance_43_reset(tap_dance_state_t *state, void *user_data);

void on_dance_43(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_X);
        tap_code16(KC_X);
        tap_code16(KC_X);
    }
    if(state->count > 3) {
        tap_code16(KC_X);
    }
}

void dance_43_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[43].step = dance_step(state);
    switch (dance_state[43].step) {
        case SINGLE_TAP: register_code16(KC_X); break;
        case SINGLE_HOLD: register_code16(KC_X); break;
        case DOUBLE_TAP: register_code16(LGUI(KC_X)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_X); register_code16(KC_X);
    }
}

void dance_43_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[43].step) {
        case SINGLE_TAP: unregister_code16(KC_X); break;
        case SINGLE_HOLD: unregister_code16(KC_X); break;
        case DOUBLE_TAP: unregister_code16(LGUI(KC_X)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_X); break;
    }
    dance_state[43].step = 0;
}
void on_dance_44(tap_dance_state_t *state, void *user_data);
void dance_44_finished(tap_dance_state_t *state, void *user_data);
void dance_44_reset(tap_dance_state_t *state, void *user_data);

void on_dance_44(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_C);
        tap_code16(KC_C);
        tap_code16(KC_C);
    }
    if(state->count > 3) {
        tap_code16(KC_C);
    }
}

void dance_44_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[44].step = dance_step(state);
    switch (dance_state[44].step) {
        case SINGLE_TAP: register_code16(KC_C); break;
        case SINGLE_HOLD: register_code16(KC_C); break;
        case DOUBLE_TAP: register_code16(LGUI(KC_C)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_C); register_code16(KC_C);
    }
}

void dance_44_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[44].step) {
        case SINGLE_TAP: unregister_code16(KC_C); break;
        case SINGLE_HOLD: unregister_code16(KC_C); break;
        case DOUBLE_TAP: unregister_code16(LGUI(KC_C)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_C); break;
    }
    dance_state[44].step = 0;
}
void on_dance_45(tap_dance_state_t *state, void *user_data);
void dance_45_finished(tap_dance_state_t *state, void *user_data);
void dance_45_reset(tap_dance_state_t *state, void *user_data);

void on_dance_45(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_V);
        tap_code16(KC_V);
        tap_code16(KC_V);
    }
    if(state->count > 3) {
        tap_code16(KC_V);
    }
}

void dance_45_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[45].step = dance_step(state);
    switch (dance_state[45].step) {
        case SINGLE_TAP: register_code16(KC_V); break;
        case SINGLE_HOLD: register_code16(KC_V); break;
        case DOUBLE_TAP: register_code16(LGUI(KC_V)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_V); register_code16(KC_V);
    }
}

void dance_45_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[45].step) {
        case SINGLE_TAP: unregister_code16(KC_V); break;
        case SINGLE_HOLD: unregister_code16(KC_V); break;
        case DOUBLE_TAP: unregister_code16(LGUI(KC_V)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_V); break;
    }
    dance_state[45].step = 0;
}
void on_dance_46(tap_dance_state_t *state, void *user_data);
void dance_46_finished(tap_dance_state_t *state, void *user_data);
void dance_46_reset(tap_dance_state_t *state, void *user_data);

void on_dance_46(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_LEFT);
        tap_code16(KC_LEFT);
        tap_code16(KC_LEFT);
    }
    if(state->count > 3) {
        tap_code16(KC_LEFT);
    }
}

void dance_46_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[46].step = dance_step(state);
    switch (dance_state[46].step) {
        case SINGLE_TAP: register_code16(KC_LEFT); break;
        case SINGLE_HOLD: register_code16(KC_LEFT); break;
        case DOUBLE_TAP: register_code16(KC_LEFT); break;
        case DOUBLE_HOLD: register_code16(LCTL(KC_LEFT)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_LEFT); register_code16(KC_LEFT);
    }
}

void dance_46_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[46].step) {
        case SINGLE_TAP: unregister_code16(KC_LEFT); break;
        case SINGLE_HOLD: unregister_code16(KC_LEFT); break;
        case DOUBLE_TAP: unregister_code16(KC_LEFT); break;
        case DOUBLE_HOLD: unregister_code16(LCTL(KC_LEFT)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_LEFT); break;
    }
    dance_state[46].step = 0;
}
void on_dance_47(tap_dance_state_t *state, void *user_data);
void dance_47_finished(tap_dance_state_t *state, void *user_data);
void dance_47_reset(tap_dance_state_t *state, void *user_data);

void on_dance_47(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(LGUI(KC_F));
        tap_code16(LGUI(KC_F));
        tap_code16(LGUI(KC_F));
    }
    if(state->count > 3) {
        tap_code16(LGUI(KC_F));
    }
}

void dance_47_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[47].step = dance_step(state);
    switch (dance_state[47].step) {
        case SINGLE_TAP: register_code16(LGUI(KC_F)); break;
        case SINGLE_HOLD: register_code16(LGUI(KC_R)); break;
        case DOUBLE_TAP: register_code16(LGUI(LSFT(KC_F))); break;
        case DOUBLE_HOLD: register_code16(LGUI(LSFT(KC_R))); break;
        case DOUBLE_SINGLE_TAP: tap_code16(LGUI(KC_F)); register_code16(LGUI(KC_F));
    }
}

void dance_47_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[47].step) {
        case SINGLE_TAP: unregister_code16(LGUI(KC_F)); break;
        case SINGLE_HOLD: unregister_code16(LGUI(KC_R)); break;
        case DOUBLE_TAP: unregister_code16(LGUI(LSFT(KC_F))); break;
        case DOUBLE_HOLD: unregister_code16(LGUI(LSFT(KC_R))); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(LGUI(KC_F)); break;
    }
    dance_state[47].step = 0;
}
void on_dance_48(tap_dance_state_t *state, void *user_data);
void dance_48_finished(tap_dance_state_t *state, void *user_data);
void dance_48_reset(tap_dance_state_t *state, void *user_data);

void on_dance_48(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_6);
        tap_code16(KC_6);
        tap_code16(KC_6);
    }
    if(state->count > 3) {
        tap_code16(KC_6);
    }
}

void dance_48_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[48].step = dance_step(state);
    switch (dance_state[48].step) {
        case SINGLE_TAP: register_code16(KC_6); break;
        case SINGLE_HOLD: register_code16(LSFT(KC_6)); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_6)); break;
        case DOUBLE_HOLD: register_code16(KC_6); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_6); register_code16(KC_6);
    }
}

void dance_48_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[48].step) {
        case SINGLE_TAP: unregister_code16(KC_6); break;
        case SINGLE_HOLD: unregister_code16(LSFT(KC_6)); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_6)); break;
        case DOUBLE_HOLD: unregister_code16(KC_6); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_6); break;
    }
    dance_state[48].step = 0;
}
void on_dance_49(tap_dance_state_t *state, void *user_data);
void dance_49_finished(tap_dance_state_t *state, void *user_data);
void dance_49_reset(tap_dance_state_t *state, void *user_data);

void on_dance_49(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_7);
        tap_code16(KC_7);
        tap_code16(KC_7);
    }
    if(state->count > 3) {
        tap_code16(KC_7);
    }
}

void dance_49_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[49].step = dance_step(state);
    switch (dance_state[49].step) {
        case SINGLE_TAP: register_code16(KC_7); break;
        case SINGLE_HOLD: register_code16(LSFT(KC_7)); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_7)); break;
        case DOUBLE_HOLD: register_code16(KC_7); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_7); register_code16(KC_7);
    }
}

void dance_49_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[49].step) {
        case SINGLE_TAP: unregister_code16(KC_7); break;
        case SINGLE_HOLD: unregister_code16(LSFT(KC_7)); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_7)); break;
        case DOUBLE_HOLD: unregister_code16(KC_7); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_7); break;
    }
    dance_state[49].step = 0;
}
void on_dance_50(tap_dance_state_t *state, void *user_data);
void dance_50_finished(tap_dance_state_t *state, void *user_data);
void dance_50_reset(tap_dance_state_t *state, void *user_data);

void on_dance_50(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_8);
        tap_code16(KC_8);
        tap_code16(KC_8);
    }
    if(state->count > 3) {
        tap_code16(KC_8);
    }
}

void dance_50_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[50].step = dance_step(state);
    switch (dance_state[50].step) {
        case SINGLE_TAP: register_code16(KC_8); break;
        case SINGLE_HOLD: register_code16(LSFT(KC_8)); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_8)); break;
        case DOUBLE_HOLD: register_code16(KC_8); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_8); register_code16(KC_8);
    }
}

void dance_50_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[50].step) {
        case SINGLE_TAP: unregister_code16(KC_8); break;
        case SINGLE_HOLD: unregister_code16(LSFT(KC_8)); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_8)); break;
        case DOUBLE_HOLD: unregister_code16(KC_8); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_8); break;
    }
    dance_state[50].step = 0;
}
void on_dance_51(tap_dance_state_t *state, void *user_data);
void dance_51_finished(tap_dance_state_t *state, void *user_data);
void dance_51_reset(tap_dance_state_t *state, void *user_data);

void on_dance_51(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_9);
        tap_code16(KC_9);
        tap_code16(KC_9);
    }
    if(state->count > 3) {
        tap_code16(KC_9);
    }
}

void dance_51_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[51].step = dance_step(state);
    switch (dance_state[51].step) {
        case SINGLE_TAP: register_code16(KC_9); break;
        case SINGLE_HOLD: register_code16(LSFT(KC_9)); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_9)); break;
        case DOUBLE_HOLD: register_code16(KC_9); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_9); register_code16(KC_9);
    }
}

void dance_51_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[51].step) {
        case SINGLE_TAP: unregister_code16(KC_9); break;
        case SINGLE_HOLD: unregister_code16(LSFT(KC_9)); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_9)); break;
        case DOUBLE_HOLD: unregister_code16(KC_9); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_9); break;
    }
    dance_state[51].step = 0;
}
void on_dance_52(tap_dance_state_t *state, void *user_data);
void dance_52_finished(tap_dance_state_t *state, void *user_data);
void dance_52_reset(tap_dance_state_t *state, void *user_data);

void on_dance_52(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_0);
        tap_code16(KC_0);
        tap_code16(KC_0);
    }
    if(state->count > 3) {
        tap_code16(KC_0);
    }
}

void dance_52_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[52].step = dance_step(state);
    switch (dance_state[52].step) {
        case SINGLE_TAP: register_code16(KC_0); break;
        case SINGLE_HOLD: register_code16(LSFT(KC_0)); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_0)); break;
        case DOUBLE_HOLD: register_code16(KC_0); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_0); register_code16(KC_0);
    }
}

void dance_52_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[52].step) {
        case SINGLE_TAP: unregister_code16(KC_0); break;
        case SINGLE_HOLD: unregister_code16(LSFT(KC_0)); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_0)); break;
        case DOUBLE_HOLD: unregister_code16(KC_0); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_0); break;
    }
    dance_state[52].step = 0;
}
void on_dance_53(tap_dance_state_t *state, void *user_data);
void dance_53_finished(tap_dance_state_t *state, void *user_data);
void dance_53_reset(tap_dance_state_t *state, void *user_data);

void on_dance_53(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_MINUS);
        tap_code16(KC_MINUS);
        tap_code16(KC_MINUS);
    }
    if(state->count > 3) {
        tap_code16(KC_MINUS);
    }
}

void dance_53_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[53].step = dance_step(state);
    switch (dance_state[53].step) {
        case SINGLE_TAP: register_code16(KC_MINUS); break;
        case SINGLE_HOLD: register_code16(KC_MINUS); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_MINUS)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_MINUS); register_code16(KC_MINUS);
    }
}

void dance_53_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[53].step) {
        case SINGLE_TAP: unregister_code16(KC_MINUS); break;
        case SINGLE_HOLD: unregister_code16(KC_MINUS); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_MINUS)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_MINUS); break;
    }
    dance_state[53].step = 0;
}
void on_dance_54(tap_dance_state_t *state, void *user_data);
void dance_54_finished(tap_dance_state_t *state, void *user_data);
void dance_54_reset(tap_dance_state_t *state, void *user_data);

void on_dance_54(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_EQUAL);
        tap_code16(KC_EQUAL);
        tap_code16(KC_EQUAL);
    }
    if(state->count > 3) {
        tap_code16(KC_EQUAL);
    }
}

void dance_54_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[54].step = dance_step(state);
    switch (dance_state[54].step) {
        case SINGLE_TAP: register_code16(KC_EQUAL); break;
        case SINGLE_HOLD: register_code16(KC_EQUAL); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_EQUAL)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_EQUAL); register_code16(KC_EQUAL);
    }
}

void dance_54_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[54].step) {
        case SINGLE_TAP: unregister_code16(KC_EQUAL); break;
        case SINGLE_HOLD: unregister_code16(KC_EQUAL); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_EQUAL)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_EQUAL); break;
    }
    dance_state[54].step = 0;
}
void on_dance_55(tap_dance_state_t *state, void *user_data);
void dance_55_finished(tap_dance_state_t *state, void *user_data);
void dance_55_reset(tap_dance_state_t *state, void *user_data);

void on_dance_55(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_RBRC);
        tap_code16(KC_RBRC);
        tap_code16(KC_RBRC);
    }
    if(state->count > 3) {
        tap_code16(KC_RBRC);
    }
}

void dance_55_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[55].step = dance_step(state);
    switch (dance_state[55].step) {
        case SINGLE_TAP: register_code16(KC_RBRC); break;
        case SINGLE_HOLD: register_code16(LSFT(KC_0)); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_RBRC)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_RBRC); register_code16(KC_RBRC);
    }
}

void dance_55_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[55].step) {
        case SINGLE_TAP: unregister_code16(KC_RBRC); break;
        case SINGLE_HOLD: unregister_code16(LSFT(KC_0)); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_RBRC)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_RBRC); break;
    }
    dance_state[55].step = 0;
}
void on_dance_56(tap_dance_state_t *state, void *user_data);
void dance_56_finished(tap_dance_state_t *state, void *user_data);
void dance_56_reset(tap_dance_state_t *state, void *user_data);

void on_dance_56(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_H);
        tap_code16(KC_H);
        tap_code16(KC_H);
    }
    if(state->count > 3) {
        tap_code16(KC_H);
    }
}

void dance_56_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[56].step = dance_step(state);
    switch (dance_state[56].step) {
        case SINGLE_TAP: register_code16(KC_H); break;
        case SINGLE_HOLD: register_code16(KC_H); break;
        case DOUBLE_TAP: register_code16(KC_H); register_code16(KC_H); break;
        case DOUBLE_HOLD: register_code16(KC_LEFT); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_H); register_code16(KC_H);
    }
}

void dance_56_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[56].step) {
        case SINGLE_TAP: unregister_code16(KC_H); break;
        case SINGLE_HOLD: unregister_code16(KC_H); break;
        case DOUBLE_TAP: unregister_code16(KC_H); break;
        case DOUBLE_HOLD: unregister_code16(KC_LEFT); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_H); break;
    }
    dance_state[56].step = 0;
}
void on_dance_57(tap_dance_state_t *state, void *user_data);
void dance_57_finished(tap_dance_state_t *state, void *user_data);
void dance_57_reset(tap_dance_state_t *state, void *user_data);

void on_dance_57(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_J);
        tap_code16(KC_J);
        tap_code16(KC_J);
    }
    if(state->count > 3) {
        tap_code16(KC_J);
    }
}

void dance_57_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[57].step = dance_step(state);
    switch (dance_state[57].step) {
        case SINGLE_TAP: register_code16(KC_J); break;
        case SINGLE_HOLD: register_code16(KC_J); break;
        case DOUBLE_TAP: register_code16(KC_J); register_code16(KC_J); break;
        case DOUBLE_HOLD: register_code16(KC_DOWN); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_J); register_code16(KC_J);
    }
}

void dance_57_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[57].step) {
        case SINGLE_TAP: unregister_code16(KC_J); break;
        case SINGLE_HOLD: unregister_code16(KC_J); break;
        case DOUBLE_TAP: unregister_code16(KC_J); break;
        case DOUBLE_HOLD: unregister_code16(KC_DOWN); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_J); break;
    }
    dance_state[57].step = 0;
}
void on_dance_58(tap_dance_state_t *state, void *user_data);
void dance_58_finished(tap_dance_state_t *state, void *user_data);
void dance_58_reset(tap_dance_state_t *state, void *user_data);

void on_dance_58(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_K);
        tap_code16(KC_K);
        tap_code16(KC_K);
    }
    if(state->count > 3) {
        tap_code16(KC_K);
    }
}

void dance_58_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[58].step = dance_step(state);
    switch (dance_state[58].step) {
        case SINGLE_TAP: register_code16(KC_K); break;
        case SINGLE_HOLD: register_code16(KC_K); break;
        case DOUBLE_TAP: register_code16(KC_K); register_code16(KC_K); break;
        case DOUBLE_HOLD: register_code16(KC_UP); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_K); register_code16(KC_K);
    }
}

void dance_58_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[58].step) {
        case SINGLE_TAP: unregister_code16(KC_K); break;
        case SINGLE_HOLD: unregister_code16(KC_K); break;
        case DOUBLE_TAP: unregister_code16(KC_K); break;
        case DOUBLE_HOLD: unregister_code16(KC_UP); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_K); break;
    }
    dance_state[58].step = 0;
}
void on_dance_59(tap_dance_state_t *state, void *user_data);
void dance_59_finished(tap_dance_state_t *state, void *user_data);
void dance_59_reset(tap_dance_state_t *state, void *user_data);

void on_dance_59(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_L);
        tap_code16(KC_L);
        tap_code16(KC_L);
    }
    if(state->count > 3) {
        tap_code16(KC_L);
    }
}

void dance_59_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[59].step = dance_step(state);
    switch (dance_state[59].step) {
        case SINGLE_TAP: register_code16(KC_L); break;
        case SINGLE_HOLD: register_code16(KC_L); break;
        case DOUBLE_TAP: register_code16(KC_L); register_code16(KC_L); break;
        case DOUBLE_HOLD: register_code16(KC_RIGHT); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_L); register_code16(KC_L);
    }
}

void dance_59_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[59].step) {
        case SINGLE_TAP: unregister_code16(KC_L); break;
        case SINGLE_HOLD: unregister_code16(KC_L); break;
        case DOUBLE_TAP: unregister_code16(KC_L); break;
        case DOUBLE_HOLD: unregister_code16(KC_RIGHT); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_L); break;
    }
    dance_state[59].step = 0;
}
void on_dance_60(tap_dance_state_t *state, void *user_data);
void dance_60_finished(tap_dance_state_t *state, void *user_data);
void dance_60_reset(tap_dance_state_t *state, void *user_data);

void on_dance_60(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_SCLN);
        tap_code16(KC_SCLN);
        tap_code16(KC_SCLN);
    }
    if(state->count > 3) {
        tap_code16(KC_SCLN);
    }
}

void dance_60_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[60].step = dance_step(state);
    switch (dance_state[60].step) {
        case SINGLE_TAP: register_code16(KC_SCLN); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_SCLN)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_SCLN); register_code16(KC_SCLN);
    }
}

void dance_60_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[60].step) {
        case SINGLE_TAP: unregister_code16(KC_SCLN); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_SCLN)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_SCLN); break;
    }
    dance_state[60].step = 0;
}
void on_dance_61(tap_dance_state_t *state, void *user_data);
void dance_61_finished(tap_dance_state_t *state, void *user_data);
void dance_61_reset(tap_dance_state_t *state, void *user_data);

void on_dance_61(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_QUOTE);
        tap_code16(KC_QUOTE);
        tap_code16(KC_QUOTE);
    }
    if(state->count > 3) {
        tap_code16(KC_QUOTE);
    }
}

void dance_61_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[61].step = dance_step(state);
    switch (dance_state[61].step) {
        case SINGLE_TAP: register_code16(KC_QUOTE); break;
        case SINGLE_HOLD: register_code16(KC_QUOTE); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_QUOTE)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_QUOTE); register_code16(KC_QUOTE);
    }
}

void dance_61_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[61].step) {
        case SINGLE_TAP: unregister_code16(KC_QUOTE); break;
        case SINGLE_HOLD: unregister_code16(KC_QUOTE); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_QUOTE)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_QUOTE); break;
    }
    dance_state[61].step = 0;
}
void on_dance_62(tap_dance_state_t *state, void *user_data);
void dance_62_finished(tap_dance_state_t *state, void *user_data);
void dance_62_reset(tap_dance_state_t *state, void *user_data);

void on_dance_62(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_COMMA);
        tap_code16(KC_COMMA);
        tap_code16(KC_COMMA);
    }
    if(state->count > 3) {
        tap_code16(KC_COMMA);
    }
}

void dance_62_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[62].step = dance_step(state);
    switch (dance_state[62].step) {
        case SINGLE_TAP: register_code16(KC_COMMA); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_COMMA)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_COMMA); register_code16(KC_COMMA);
    }
}

void dance_62_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[62].step) {
        case SINGLE_TAP: unregister_code16(KC_COMMA); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_COMMA)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_COMMA); break;
    }
    dance_state[62].step = 0;
}
void on_dance_63(tap_dance_state_t *state, void *user_data);
void dance_63_finished(tap_dance_state_t *state, void *user_data);
void dance_63_reset(tap_dance_state_t *state, void *user_data);

void on_dance_63(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_DOT);
        tap_code16(KC_DOT);
        tap_code16(KC_DOT);
    }
    if(state->count > 3) {
        tap_code16(KC_DOT);
    }
}

void dance_63_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[63].step = dance_step(state);
    switch (dance_state[63].step) {
        case SINGLE_TAP: register_code16(KC_DOT); break;
        case SINGLE_HOLD: register_code16(KC_DOT); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_DOT)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_DOT); register_code16(KC_DOT);
    }
}

void dance_63_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[63].step) {
        case SINGLE_TAP: unregister_code16(KC_DOT); break;
        case SINGLE_HOLD: unregister_code16(KC_DOT); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_DOT)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_DOT); break;
    }
    dance_state[63].step = 0;
}
void on_dance_64(tap_dance_state_t *state, void *user_data);
void dance_64_finished(tap_dance_state_t *state, void *user_data);
void dance_64_reset(tap_dance_state_t *state, void *user_data);

void on_dance_64(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_SLASH);
        tap_code16(KC_SLASH);
        tap_code16(KC_SLASH);
    }
    if(state->count > 3) {
        tap_code16(KC_SLASH);
    }
}

void dance_64_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[64].step = dance_step(state);
    switch (dance_state[64].step) {
        case SINGLE_TAP: register_code16(KC_SLASH); break;
        case SINGLE_HOLD: register_code16(KC_SLASH); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_SLASH)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_SLASH); register_code16(KC_SLASH);
    }
}

void dance_64_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[64].step) {
        case SINGLE_TAP: unregister_code16(KC_SLASH); break;
        case SINGLE_HOLD: unregister_code16(KC_SLASH); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_SLASH)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_SLASH); break;
    }
    dance_state[64].step = 0;
}
void on_dance_65(tap_dance_state_t *state, void *user_data);
void dance_65_finished(tap_dance_state_t *state, void *user_data);
void dance_65_reset(tap_dance_state_t *state, void *user_data);

void on_dance_65(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_BSLS);
        tap_code16(KC_BSLS);
        tap_code16(KC_BSLS);
    }
    if(state->count > 3) {
        tap_code16(KC_BSLS);
    }
}

void dance_65_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[65].step = dance_step(state);
    switch (dance_state[65].step) {
        case SINGLE_TAP: register_code16(KC_BSLS); break;
        case SINGLE_HOLD: register_code16(KC_BSLS); break;
        case DOUBLE_TAP: register_code16(LSFT(KC_BSLS)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_BSLS); register_code16(KC_BSLS);
    }
}

void dance_65_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[65].step) {
        case SINGLE_TAP: unregister_code16(KC_BSLS); break;
        case SINGLE_HOLD: unregister_code16(KC_BSLS); break;
        case DOUBLE_TAP: unregister_code16(LSFT(KC_BSLS)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_BSLS); break;
    }
    dance_state[65].step = 0;
}
void on_dance_66(tap_dance_state_t *state, void *user_data);
void dance_66_finished(tap_dance_state_t *state, void *user_data);
void dance_66_reset(tap_dance_state_t *state, void *user_data);

void on_dance_66(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_AUDIO_VOL_DOWN);
        tap_code16(KC_AUDIO_VOL_DOWN);
        tap_code16(KC_AUDIO_VOL_DOWN);
    }
    if(state->count > 3) {
        tap_code16(KC_AUDIO_VOL_DOWN);
    }
}

void dance_66_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[66].step = dance_step(state);
    switch (dance_state[66].step) {
        case SINGLE_TAP: register_code16(KC_AUDIO_VOL_DOWN); break;
        case DOUBLE_TAP: register_code16(KC_AUDIO_VOL_DOWN); break;
        case DOUBLE_HOLD: register_code16(KC_AUDIO_MUTE); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_AUDIO_VOL_DOWN); register_code16(KC_AUDIO_VOL_DOWN);
    }
}

void dance_66_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[66].step) {
        case SINGLE_TAP: unregister_code16(KC_AUDIO_VOL_DOWN); break;
        case DOUBLE_TAP: unregister_code16(KC_AUDIO_VOL_DOWN); break;
        case DOUBLE_HOLD: unregister_code16(KC_AUDIO_MUTE); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_AUDIO_VOL_DOWN); break;
    }
    dance_state[66].step = 0;
}
void on_dance_67(tap_dance_state_t *state, void *user_data);
void dance_67_finished(tap_dance_state_t *state, void *user_data);
void dance_67_reset(tap_dance_state_t *state, void *user_data);

void on_dance_67(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_RIGHT);
        tap_code16(KC_RIGHT);
        tap_code16(KC_RIGHT);
    }
    if(state->count > 3) {
        tap_code16(KC_RIGHT);
    }
}

void dance_67_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[67].step = dance_step(state);
    switch (dance_state[67].step) {
        case SINGLE_TAP: register_code16(KC_RIGHT); break;
        case SINGLE_HOLD: register_code16(KC_RIGHT); break;
        case DOUBLE_TAP: register_code16(KC_RIGHT); register_code16(KC_RIGHT); break;
        case DOUBLE_HOLD: register_code16(LCTL(KC_RIGHT)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_RIGHT); register_code16(KC_RIGHT);
    }
}

void dance_67_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[67].step) {
        case SINGLE_TAP: unregister_code16(KC_RIGHT); break;
        case SINGLE_HOLD: unregister_code16(KC_RIGHT); break;
        case DOUBLE_TAP: unregister_code16(KC_RIGHT); break;
        case DOUBLE_HOLD: unregister_code16(LCTL(KC_RIGHT)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_RIGHT); break;
    }
    dance_state[67].step = 0;
}
void on_dance_68(tap_dance_state_t *state, void *user_data);
void dance_68_finished(tap_dance_state_t *state, void *user_data);
void dance_68_reset(tap_dance_state_t *state, void *user_data);

void on_dance_68(tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_TAB);
        tap_code16(KC_TAB);
        tap_code16(KC_TAB);
    }
    if(state->count > 3) {
        tap_code16(KC_TAB);
    }
}

void dance_68_finished(tap_dance_state_t *state, void *user_data) {
    dance_state[68].step = dance_step(state);
    switch (dance_state[68].step) {
        case SINGLE_TAP: register_code16(KC_TAB); break;
        case DOUBLE_TAP: register_code16(KC_TAB); register_code16(KC_TAB); break;
        case DOUBLE_HOLD: register_code16(LSFT(KC_TAB)); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_TAB); register_code16(KC_TAB);
    }
}

void dance_68_reset(tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[68].step) {
        case SINGLE_TAP: unregister_code16(KC_TAB); break;
        case DOUBLE_TAP: unregister_code16(KC_TAB); break;
        case DOUBLE_HOLD: unregister_code16(LSFT(KC_TAB)); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_TAB); break;
    }
    dance_state[68].step = 0;
}

tap_dance_action_t tap_dance_actions[] = {
        [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_0, dance_0_finished, dance_0_reset),
        [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_1, dance_1_finished, dance_1_reset),
        [DANCE_2] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_2, dance_2_finished, dance_2_reset),
        [DANCE_3] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_3, dance_3_finished, dance_3_reset),
        [DANCE_4] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_4, dance_4_finished, dance_4_reset),
        [DANCE_5] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_5, dance_5_finished, dance_5_reset),
        [DANCE_6] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_6, dance_6_finished, dance_6_reset),
        [DANCE_7] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_7, dance_7_finished, dance_7_reset),
        [DANCE_8] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_8, dance_8_finished, dance_8_reset),
        [DANCE_9] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_9, dance_9_finished, dance_9_reset),
        [DANCE_10] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_10, dance_10_finished, dance_10_reset),
        [DANCE_11] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_11, dance_11_finished, dance_11_reset),
        [DANCE_12] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_12, dance_12_finished, dance_12_reset),
        [DANCE_13] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_13, dance_13_finished, dance_13_reset),
        [DANCE_14] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_14, dance_14_finished, dance_14_reset),
        [DANCE_15] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_15, dance_15_finished, dance_15_reset),
        [DANCE_16] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_16, dance_16_finished, dance_16_reset),
        [DANCE_17] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_17, dance_17_finished, dance_17_reset),
        [DANCE_18] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_18, dance_18_finished, dance_18_reset),
        [DANCE_19] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_19, dance_19_finished, dance_19_reset),
        [DANCE_20] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_20, dance_20_finished, dance_20_reset),
        [DANCE_21] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_21, dance_21_finished, dance_21_reset),
        [DANCE_22] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_22, dance_22_finished, dance_22_reset),
        [DANCE_23] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_23, dance_23_finished, dance_23_reset),
        [DANCE_24] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_24, dance_24_finished, dance_24_reset),
        [DANCE_25] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_25, dance_25_finished, dance_25_reset),
        [DANCE_26] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_26, dance_26_finished, dance_26_reset),
        [DANCE_27] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_27, dance_27_finished, dance_27_reset),
        [DANCE_28] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_28, dance_28_finished, dance_28_reset),
        [DANCE_29] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_29, dance_29_finished, dance_29_reset),
        [DANCE_30] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_30, dance_30_finished, dance_30_reset),
        [DANCE_31] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_31, dance_31_finished, dance_31_reset),
        [DANCE_32] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_32, dance_32_finished, dance_32_reset),
        [DANCE_33] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_33, dance_33_finished, dance_33_reset),
        [DANCE_34] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_34, dance_34_finished, dance_34_reset),
        [DANCE_35] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_35, dance_35_finished, dance_35_reset),
        [DANCE_36] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_36, dance_36_finished, dance_36_reset),
        [DANCE_37] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_37, dance_37_finished, dance_37_reset),
        [DANCE_38] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_38, dance_38_finished, dance_38_reset),
        [DANCE_39] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_39, dance_39_finished, dance_39_reset),
        [DANCE_40] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_40, dance_40_finished, dance_40_reset),
        [DANCE_41] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_41, dance_41_finished, dance_41_reset),
        [DANCE_42] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_42, dance_42_finished, dance_42_reset),
        [DANCE_43] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_43, dance_43_finished, dance_43_reset),
        [DANCE_44] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_44, dance_44_finished, dance_44_reset),
        [DANCE_45] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_45, dance_45_finished, dance_45_reset),
        [DANCE_46] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_46, dance_46_finished, dance_46_reset),
        [DANCE_47] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_47, dance_47_finished, dance_47_reset),
        [DANCE_48] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_48, dance_48_finished, dance_48_reset),
        [DANCE_49] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_49, dance_49_finished, dance_49_reset),
        [DANCE_50] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_50, dance_50_finished, dance_50_reset),
        [DANCE_51] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_51, dance_51_finished, dance_51_reset),
        [DANCE_52] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_52, dance_52_finished, dance_52_reset),
        [DANCE_53] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_53, dance_53_finished, dance_53_reset),
        [DANCE_54] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_54, dance_54_finished, dance_54_reset),
        [DANCE_55] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_55, dance_55_finished, dance_55_reset),
        [DANCE_56] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_56, dance_56_finished, dance_56_reset),
        [DANCE_57] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_57, dance_57_finished, dance_57_reset),
        [DANCE_58] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_58, dance_58_finished, dance_58_reset),
        [DANCE_59] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_59, dance_59_finished, dance_59_reset),
        [DANCE_60] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_60, dance_60_finished, dance_60_reset),
        [DANCE_61] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_61, dance_61_finished, dance_61_reset),
        [DANCE_62] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_62, dance_62_finished, dance_62_reset),
        [DANCE_63] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_63, dance_63_finished, dance_63_reset),
        [DANCE_64] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_64, dance_64_finished, dance_64_reset),
        [DANCE_65] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_65, dance_65_finished, dance_65_reset),
        [DANCE_66] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_66, dance_66_finished, dance_66_reset),
        [DANCE_67] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_67, dance_67_finished, dance_67_reset),
        [DANCE_68] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_68, dance_68_finished, dance_68_reset),
};
