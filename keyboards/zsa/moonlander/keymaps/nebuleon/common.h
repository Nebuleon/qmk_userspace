#pragma once
#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_canadian_french.h"
#include <assert.h>
#include "layers.h"
#include "tap_dances.h"

/* Key shortcuts */
#define SC_LAAP MT(MOD_LALT, KC_APP)
#define SC_LSSP MT(MOD_LSFT, KC_SPC)
#define SC_LCEN MT(MOD_LCTL, KC_ENT)
#define SC_TAWT LT(L_WindowsTerminals, KC_TAB)
#define SC_NBSP LCTL(LSFT(KC_SPC))
#define SC_CS_L LCTL(LSFT(KC_LEFT))
#define SC_CS_R LCTL(LSFT(KC_RGHT))
#define SC_S_L  LSFT(KC_LEFT)
#define SC_S_R  LSFT(KC_RGHT)
#define SC_C_L  LCTL(KC_LEFT)
#define SC_C_R  LCTL(KC_RGHT)
#define SC_S_TB LSFT(KC_TAB)
#define SC_C_BS LCTL(KC_BSPC)
#define SC_C_DL LCTL(KC_DEL)
#define SC_CS_H LCTL(LSFT(KC_HOME))
#define SC_CS_E LCTL(LSFT(KC_END))
#define SC_S_H  LSFT(KC_HOME)
#define SC_S_E  LSFT(KC_END)
#define SC_C_H  LCTL(KC_HOME)
#define SC_C_E  LCTL(KC_END)
#define SC_CA_L LALT(LCTL(KC_LEFT))
#define SC_CA_R LALT(LCTL(KC_RGHT))
#define SC_CS_M LCTL(LSFT(FR_MINS))
#define SC_C_M  LCTL(FR_MINS)
#define SC_CF1  LCTL(KC_F1)
#define SC_CF2  LCTL(KC_F2)
#define SC_CF3  LCTL(KC_F3)
#define SC_CF4  LCTL(KC_F4)
#define SC_CF5  LCTL(KC_F5)
#define SC_CF6  LCTL(KC_F6)
#define SC_CF7  LCTL(KC_F7)
#define SC_CF8  LCTL(KC_F8)
#define SC_CF9  LCTL(KC_F9)
#define SC_CF10 LCTL(KC_F10)
#define SC_GF1  LGUI(KC_F1)
#define SC_GF2  LGUI(KC_F2)
#define SC_GF3  LGUI(KC_F3)
#define SC_GF4  LGUI(KC_F4)
#define SC_GSF1 LGUI(LSFT(KC_F1))
#define SC_GSF2 LGUI(LSFT(KC_F2))
#define SC_GSF3 LGUI(LSFT(KC_F3))
#define SC_GSF4 LGUI(LSFT(KC_F4))
#define SC_CGSL LCTL(LGUI(LSFT(KC_LEFT)))
#define SC_CGSR LCTL(LGUI(LSFT(KC_RGHT)))
#define IL_TOGG LED_LEVEL            /* stands for Indicator Led TOGGle */
#define LC_TOGG TOGGLE_LAYER_COLOR   /* stands for Layer Color TOGGle */

/* \brief Converts a modifier bitfield for use with MT, i.e. where the side
 *        of all modifiers, left or right, is represented with one bit, to
 *        a modifier bitfield where each modifier on each side gets its own
 *        bit, for use with get_mods() and related functions.
 * \param mods the 5-bit modifiers to convert
 * \return the modifiers in 'mods', converted into an 8-bit bitfield
 */
uint8_t mt_to_mod_bits(uint8_t mods);

extern const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS];

extern uint8_t toggle_hold_held_mods;
extern uint8_t toggle_hold_locked_mods;
