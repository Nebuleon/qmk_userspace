#pragma once
#include QMK_KEYBOARD_H
#include "keymap_canadian_french.h"

/* The tap dances are defined here. */

#define GENERATE_TAP_DANCES_TAP_DOUBLE_TAP_CUSTOM(GENERATE) \
    /* On L_DvorakLX, layer clear or Lock button */ \
    GENERATE(_LOCK) \

#define GENERATE_TAP_DANCES_TAP_HOLD(GENERATE) \
    /* On L_DvorakLX, number row */ \
    GENERATE(_1_F1, KC_1, KC_F1) \
    GENERATE(_2_F2, KC_2, KC_F2) \
    GENERATE(_3_F3, KC_3, KC_F3) \
    GENERATE(_4_F4, KC_4, KC_F4) \
    GENERATE(_5_F5, KC_5, KC_F5) \
    GENERATE(_6_F6, KC_6, KC_F6) \
    GENERATE(_7_F7, KC_7, KC_F7) \
    GENERATE(_8_F8, KC_8, KC_F8) \
    GENERATE(_9_F9, KC_9, KC_F9) \
    GENERATE(_0F10, KC_0, KC_F10) \
    /* On L_DvorakLX, top row */ \
    GENERATE(_SCBS, FR_SCLN, FR_BSLS) \
    GENERATE(_CMEX, FR_COMM, FR_EXLM) \
    GENERATE(_DTQU, FR_DOT, FR_QUES) \
    GENERATE(_P_AT, FR_P, FR_AT) \
    GENERATE(_Y_AM, FR_Y, FR_AMPR) \
    GENERATE(_F_PI, FR_F, FR_PIPE) \
    GENERATE(_G_DL, FR_G, FR_DLR) \
    GENERATE(_C_LP, FR_C, FR_RPRN) \
    GENERATE(_R_RP, FR_R, FR_LPRN) \
    GENERATE(_X_TI, FR_X, FR_TILD) \
    /* On L_DvorakLX, home (middle) row */ \
    GENERATE(_A_SQ, FR_A, FR_QUOT) \
    GENERATE(_O_LB, FR_O, FR_LBRC) \
    GENERATE(_E_RB, FR_E, FR_RBRC) \
    GENERATE(_U_DQ, FR_U, FR_DQUO) \
    GENERATE(_I_UN, FR_I, FR_UNDS) \
    GENERATE(_D_EQ, FR_D, FR_EQL) \
    GENERATE(_H_PL, FR_H, FR_PLUS) \
    GENERATE(_T_MI, FR_T, FR_MINS) \
    GENERATE(_N_AS, FR_N, FR_ASTR) \
    GENERATE(_S_SL, FR_S, FR_SLSH) \
    /* On L_DvorakLX, bottom row */ \
    GENERATE(_CLLD, FR_COLN, FR_LDAQ) \
    GENERATE(_Q_LC, FR_Q, FR_LCBR) \
    GENERATE(_J_RC, FR_J, FR_RCBR) \
    GENERATE(_K_HA, FR_K, FR_HASH) \
    GENERATE(_B_NB, FR_B, SC_NBSP) \
    GENERATE(_L_DG, FR_L, FR_DEG) \
    GENERATE(_M_PC, FR_M, FR_PERC) \
    GENERATE(_W_RA, FR_W, FR_RABK) \
    GENERATE(_V_LA, FR_V, FR_LABK) \
    GENERATE(_Z_RD, FR_Z, FR_RDAQ) \
    /* On L_DvorakAccents, top row */ \
    GENERATE(_Y_S,  FR_Y, LSFT(FR_Y)) \
    GENERATE(_C_S,  FR_C, LSFT(FR_C)) \
    /* On L_DvorakAccents, home (middle) row */ \
    GENERATE(_A_S,  FR_A, LSFT(FR_A)) \
    GENERATE(_O_S,  FR_O, LSFT(FR_O)) \
    GENERATE(_E_S,  FR_E, LSFT(FR_E)) \
    GENERATE(_U_S,  FR_U, LSFT(FR_U)) \
    GENERATE(_I_S,  FR_I, LSFT(FR_I)) \
    /* On L_Web */ \
    GENERATE(_RFSH, KC_F5, LCTL(KC_F5)) \

#define GENERATE_TAP_DANCES_TOGGLE_HOLD_MOD(GENERATE) \
    /* On L_DvorakLX, right thumb cluster */ \
    GENERATE(_LCTL, MOD_LCTL) \
    GENERATE(_LSFT, MOD_LSFT) \
    GENERATE(_LALT, MOD_LALT) \
    GENERATE(_LGUI, MOD_LGUI) \

#define DN_ENUM_TAP_DOUBLE_TAP_CUSTOM(dance_name) DN##dance_name,
#define DN_ENUM_TAP_HOLD(dance_name, kc_tap, kc_hold) DN##dance_name,
#define DN_ENUM_TOGGLE_HOLD_MOD(dance_name, mods) DN##dance_name,

enum tap_dances_dn {
    GENERATE_TAP_DANCES_TAP_HOLD(DN_ENUM_TAP_HOLD)
    GENERATE_TAP_DANCES_TOGGLE_HOLD_MOD(DN_ENUM_TOGGLE_HOLD_MOD)
    GENERATE_TAP_DANCES_TAP_DOUBLE_TAP_CUSTOM(DN_ENUM_TAP_DOUBLE_TAP_CUSTOM)
};

#define TD_ENUM_TAP_DOUBLE_TAP_CUSTOM(dance_name) TD##dance_name = TD(DN##dance_name),
#define TD_ENUM_TAP_HOLD(dance_name, kc_tap, kc_hold) TD##dance_name = TD(DN##dance_name),
#define TD_ENUM_TOGGLE_HOLD_MOD(dance_name, mods) TD##dance_name = TD(DN##dance_name),

enum tap_dances_td {
    GENERATE_TAP_DANCES_TAP_HOLD(TD_ENUM_TAP_HOLD)
    GENERATE_TAP_DANCES_TOGGLE_HOLD_MOD(TD_ENUM_TOGGLE_HOLD_MOD)
    GENERATE_TAP_DANCES_TAP_DOUBLE_TAP_CUSTOM(TD_ENUM_TAP_DOUBLE_TAP_CUSTOM)
};