// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ENT,
        C(KC_A), C(KC_DEL), C(KC_S),
        C(KC_END),  S(KC_TAB), C(KC_HOME)
    ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    tap_code16(clockwise ? C(S(KC_V)) : C(S(A(KC_V))));
    return false;
}
