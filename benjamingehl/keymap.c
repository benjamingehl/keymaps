/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

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
#include "env.h"

#define BASE 0
#define FN 1

#define MAC_REDO LGUI(S(KC_Z))
#define MAC_UNDO LGUI(KC_Z)
#define MAC_PSCR LGUI(S(KC_4))
#define MAC_SEL_WRD A(S(KC_LEFT))
#define MAC_MUL_PST LGUI(S(KC_V))

enum custom_keycodes {
    PRT_EM = SAFE_RANGE,
    PSCR,
    DEL_WRD,
    MUL_PST,
    ENC_UNDO,
    ENC_REDO
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
    // ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc          PgUp
    // Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgDn
    // Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             Home
    // LSPO              Z        X        C        V        B        N        M        ,        .        ?                 RSPC     Up       End
    // Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right

    [BASE] = LAYOUT(
        KC_ESC,  KC_BRID, KC_BRIU, KC_F3,   KC_F4,   LGUI(S(KC_M)), KC_F6,   KC_MPRV, KC_MNXT, KC_MPLY, KC_MUTE, KC_VOLD, KC_VOLU, PSCR,             KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGDN,
        MUL_PST, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_HOME,
        SC_LSPO,          KC_Z,    KC_X,    KC_C,    KC_V,          KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          SC_RSPC, KC_UP,   KC_END,
        KC_LCTL, KC_LALT, KC_LGUI,                                  KC_SPC,                             KC_RALT, MO(FN),  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [FN] = LAYOUT(
        QK_BOOT, KC_F1,   KC_F2,   _______, _______, _______, _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,          _______,
        NK_TOGG, RM_TOGG, RM_VALU, RM_VALD, RM_HUEU, _______, _______, _______, _______, _______, _______, _______, _______, DEL_WRD,          _______,
        _______, _______, _______, PRT_EM,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        CW_TOGG, AC_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        KC_LSFT,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_RSFT, RM_NEXT, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, RM_SPDD, RM_PREV, RM_SPDU
    ),
};
// clang-format on

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [FN]   = { ENCODER_CCW_CW(ENC_UNDO, ENC_REDO) },
};
#endif // ENCODER_MAP_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case PRT_EM: {
            SEND_STRING(MY_EMAIL);
            break;
        }
        case PSCR: {
            tap_code16(MAC_PSCR);
            break;
        }
        case DEL_WRD: {
            tap_code16(MAC_SEL_WRD);
            tap_code(KC_BSPC);
            return false;
        }
        case MUL_PST: {
            tap_code16(MAC_MUL_PST);
            break;
        }
        case ENC_UNDO: {
            tap_code16(MAC_UNDO);
            break;
        }
        case ENC_REDO: {
            tap_code16(MAC_REDO);
            break;
        }
    }

    return true;
}

#ifdef RGB_MATRIX_ENABLE
void keyboard_post_init_user(void) {
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(23, 255, 255);
}

void set_fn_led_overlay(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);

    HSV current_hsv = rgb_matrix_get_hsv();
    HSV fn_hsv = {(current_hsv.h + 10) % 256, MIN(current_hsv.s + 50, 255), MIN(current_hsv.v + 50, 255)};
    RGB fn_rgb = hsv_to_rgb(fn_hsv);

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];

            if (index >= led_min && index <= led_max && index != NO_LED &&
            keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                rgb_matrix_set_color(index, fn_rgb.r, fn_rgb.g, fn_rgb.b);
            }
        }
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (get_highest_layer(layer_state) > BASE) {
        set_fn_led_overlay(led_min, led_max);
    }

    return false;
}

#endif // RGB_MATRIX_ENABLE
