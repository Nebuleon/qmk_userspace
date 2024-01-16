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
    GENERATE(_SCLC, FR_SCLN, FR_LCBR) \
    GENERATE(_CMLA, FR_COMM, FR_LABK) \
    GENERATE(_DTLP, FR_DOT, FR_LPRN) \
    GENERATE(_P_LB, FR_P, FR_LBRC) \
    GENERATE(_Y_UN, FR_Y, FR_UNDS) \
    GENERATE(_F_EQ, FR_F, FR_EQL) \
    GENERATE(_G_RB, FR_G, FR_RBRC) \
    GENERATE(_C_RP, FR_C, FR_RPRN) \
    GENERATE(_R_RA, FR_R, FR_RABK) \
    GENERATE(_X_RC, FR_X, FR_RCBR) \
    /* On L_DvorakLX, home (middle) row */ \
    GENERATE(_A_DL, FR_A, FR_DLR) \
    GENERATE(_O_DQ, FR_O, FR_DQUO) \
    GENERATE(_E_MI, FR_E, FR_MINS) \
    GENERATE(_U_PC, FR_U, FR_PERC) \
    GENERATE(_I_AM, FR_I, FR_AMPR) \
    GENERATE(_D_PI, FR_D, FR_PIPE) \
    GENERATE(_H_AT, FR_H, FR_AT) \
    GENERATE(_T_PL, FR_T, FR_PLUS) \
    GENERATE(_N_SQ, FR_N, FR_QUOT) \
    GENERATE(_S_TI, FR_S, FR_TILD) \
    /* On L_DvorakLX, bottom row */ \
    GENERATE(_CLLD, FR_COLN, FR_LDAQ) \
    GENERATE(_Q_EX, FR_Q, FR_EXLM) \
    GENERATE(_J_SL, FR_J, FR_SLSH) \
    GENERATE(_K_BS, FR_K, FR_BSLS) \
    GENERATE(_L_NB, FR_L, SC_NBSP) \
    GENERATE(_B_DG, FR_B, FR_DEG) \
    GENERATE(_M_HA, FR_M, FR_HASH) \
    GENERATE(_W_AS, FR_W, FR_ASTR) \
    GENERATE(_V_QU, FR_V, FR_QUES) \
    GENERATE(_Z_RD, FR_Z, FR_RDAQ) \
    /* On L_Phrase */ \
    GENERATE(_SEG,  LCTL(KC_ENTER), LCTL(LSFT(KC_ENTER))) \
    GENERATE(_TMTB, LCTL(FR_K), LCTL(LSFT(FR_K))) \
    /* On L_Web */ \
    GENERATE(_RFSH, KC_F5, LCTL(KC_F5)) \

#define DN_ENUM_TAP_DOUBLE_TAP_CUSTOM(dance_name) DN##dance_name,
#define DN_ENUM_TAP_HOLD(dance_name, kc_tap, kc_hold) DN##dance_name,

enum tap_dances_dn {
    GENERATE_TAP_DANCES_TAP_HOLD(DN_ENUM_TAP_HOLD)
    GENERATE_TAP_DANCES_TAP_DOUBLE_TAP_CUSTOM(DN_ENUM_TAP_DOUBLE_TAP_CUSTOM)
};

#define TD_ENUM_TAP_DOUBLE_TAP_CUSTOM(dance_name) TD##dance_name = TD(DN##dance_name),
#define TD_ENUM_TAP_HOLD(dance_name, kc_tap, kc_hold) TD##dance_name = TD(DN##dance_name),

enum tap_dances_td {
    GENERATE_TAP_DANCES_TAP_HOLD(TD_ENUM_TAP_HOLD)
    GENERATE_TAP_DANCES_TAP_DOUBLE_TAP_CUSTOM(TD_ENUM_TAP_DOUBLE_TAP_CUSTOM)
};