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

#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR

#define BASE 0
#define FN 1

#define WIN_REDO LCTL(KC_Y)
#define MAC_REDO LGUI(S(KC_Z))
#define WIN_UNDO LCTL(KC_Z)
#define MAC_UNDO LGUI(KC_Z)
#define WIN_PSCR LGUI(S(KC_S))
#define MAC_PSCR LGUI(S(KC_4))
#define WIN_SEL_WRD C(S(KC_LEFT))
#define MAC_SEL_WRD A(S(KC_LEFT))
#define WIN_MUL_PST LGUI(KC_V)
#define MAC_MUL_PST LGUI(S(KC_V))

#define LED_CAPS 3
#define LED_O 52
#define V_RED 0
#define min(a, b) (((a) < (b)) ? (a) : (b))

enum custom_keycodes {
    OS_CHG = SAFE_RANGE,
    PRT_EM,
    PSCR,
    DEL_WRD,
    MUL_PST
};

bool is_win_mode = false;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
    // ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc          PgUp
    // Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgDn
    // Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             Home
    // LSPO              Z        X        C        V        B        N        M        ,        .        ?                 RSPC     Up       End
    // Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right

    [BASE] = LAYOUT(
        KC_ESC,  KC_BRID, KC_BRIU, KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MPRV, KC_MNXT, KC_MPLY, KC_MUTE, KC_VOLD, KC_VOLU, PSCR,             KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGDN,
        MUL_PST, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_HOME,
        KC_LSPO,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSPC, KC_UP,   KC_END,
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RALT, MO(FN),  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [FN] = LAYOUT(
        QK_BOOT, KC_F1,   KC_F2,   _______, _______, _______, _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,          _______,
        NK_TOGG, RGB_TOG, RGB_VAI, RGB_VAD, RGB_HUI, _______, _______, _______, _______, _______, _______, _______, _______, DEL_WRD,          _______,
        _______, _______, _______, PRT_EM,  _______, _______, _______, _______, _______, OS_CHG,  _______, _______, _______, _______,          _______,
        CW_TOGG, AC_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        KC_LSFT,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_RSFT, RGB_MOD, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    ),
};
// clang-format on

#ifdef ENCODER_ENABLE

void encoder_clockwise(void) {    
    switch(get_highest_layer(layer_state)) {
        case BASE: {
            tap_code(KC_VOLU);
            return;
        }
        case FN: {
            int keycode = is_win_mode ? WIN_REDO : MAC_REDO;
            tap_code16(keycode);
            return;
        }
    }
}

void encoder_counterclockwise(void) {
    switch(get_highest_layer(layer_state)) {
        case BASE: {
            tap_code(KC_VOLD);
            return;
        }
        case FN: {
            int keycode = is_win_mode ? WIN_UNDO : MAC_UNDO;
            tap_code16(keycode);
            return;
        }
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        encoder_clockwise();
    } else {
        encoder_counterclockwise();
    }

    return false;
}
#endif // ENCODER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case OS_CHG: {
            is_win_mode = !is_win_mode;
            break;
        }
        case PRT_EM: {
            SEND_STRING(MY_EMAIL);
            break;
        }
        case PSCR: {
            int keycode = is_win_mode ? WIN_PSCR : MAC_PSCR;
            tap_code16(keycode);
            break;
        }
        case DEL_WRD: {
            int keycode = is_win_mode ? WIN_SEL_WRD : MAC_SEL_WRD;
            tap_code16(keycode);
            tap_code(KC_BSPC);
            return false;
        }
        case MUL_PST: {
            int keycode = is_win_mode ? WIN_MUL_PST : MAC_MUL_PST;
            tap_code16(keycode);
            break;
        }
    }

    return true;
}

#ifdef RGB_MATRIX_ENABLE
void keyboard_post_init_user(void) {
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_set_color_all(255, 137, 0);
}

void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}

void set_caps_led_indicator(void) {
    HSV current_hsv = rgb_matrix_get_hsv();
    HSV caps_hsv = {V_RED, current_hsv.s, min(current_hsv.v + 50, 255)};
    RGB caps_rgb = hsv_to_rgb(caps_hsv);
    rgb_matrix_set_color(LED_CAPS, caps_rgb.r, caps_rgb.g, caps_rgb.b);
}

void set_fn_led_overlay(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);

    HSV current_hsv = rgb_matrix_get_hsv();
    HSV fn_hsv = {(current_hsv.h + 10) % 255, min(current_hsv.s + 50, 255), min(current_hsv.v + 50, 255)};
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

    if (is_win_mode) {
        rgb_matrix_set_color(LED_O, 200, 0, 0);
    } else {
        rgb_matrix_set_color(LED_O, 0, 0, 200);
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        set_caps_led_indicator();
    }

    if (get_highest_layer(layer_state) > BASE) {
        set_fn_led_overlay(led_min, led_max);
    }

    return false;
}

#endif // RGB_MATRIX_ENABLE