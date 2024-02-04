#include "common.h"

enum custom_keycodes {
    RGB_SLD = SAFE_RANGE,
};

#define TT_QWAc TT(L_QWERTYAccents)
#define TT_DvAc TT(L_DvorakAccents)
#define TT_Move TT(L_MoveSelect)
#define TT_Syms TT(L_Symbols)
#define TT_Phrs TT(L_Phrase)
#define TT_Nums TT(L_Numbers)
#define TT_FnMs TT(L_FnMouse)
#define TT_Web  TT(L_Web)
#define TT_RGBC TT(L_RGBControl)
#define TG_Mus  TG(L_Music)
#if defined MIDI_BASIC || defined MIDI_ADVANCED
#    define TG_MIDI TG(L_MIDI)
#endif
#define DF_Dvor DF(L_DvorakLX)
#define DF_DRaw DF(L_DvorakRaw)
/* Other */
#define _leave_ _______              /* denotes a key that must be transparent because it exits a layer */

/* Modified: TO() layer keys are now DF() keys; TD() keys now have DANCE_ removed */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_DvorakLX] = LAYOUT_moonlander(
    KC_ESC,  TD_1_F1, TD_2_F2, TD_3_F3, TD_4_F4, TD_5_F5, KC_PSCR,          TD_LOCK, TD_6_F6, TD_7_F7, TD_8_F8, TD_9_F9, TD_0F10, DF_DRaw,
    _______, TD_SCLC, TD_CMLA, TD_DTLP, TD_P_LB, TD_Y_UN, KC_UP,            KC_LEFT, TD_F_EQ, TD_G_RB, TD_C_RP, TD_R_RA, TD_X_RC, TT_Web,
    KC_BSPC, TD_A_DL, TD_O_DQ, TD_E_MI, TD_U_PC, TD_I_AM, KC_DOWN,          KC_RGHT, TD_D_PI, TD_H_AT, TD_T_PL, TD_N_SQ, TD_S_TI, TT_Phrs,
    KC_DEL,  TD_CLLD, TD_Q_EX, TD_J_SL, TD_K_BS, TD_L_NB,                            TD_B_DG, TD_M_HA, TD_W_AS, TD_V_QU, TD_Z_RD, _______,
    _______, KC_LGUI, SC_LAAP, TT_Move, TT_Nums,          TT_FnMs,          TD_LGUI,          TT_Syms, TT_DvAc, KC_RALT, _______, TT_RGBC,
                                        SC_LSSP, SC_LCEN, SC_TAWT,          TD_LALT, TD_LCTL, TD_LSFT
  ),
  [L_Control] = LAYOUT_moonlander(
    _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
    _______, FR_Q,    FR_W,    FR_E,    FR_R,    FR_T,    _______,          _______, FR_Y,    FR_U,    FR_I,    FR_O,    FR_P,    _______,
    _______, FR_A,    FR_S,    FR_D,    FR_F,    FR_G,    _______,          _______, FR_H,    FR_J,    FR_K,    FR_L,    FR_SCLN, _______,
    _______, FR_Z,    FR_X,    FR_C,    FR_V,    FR_B,                               FR_N,    FR_M,    FR_COMM, FR_DOT,  FR_COLN, _______,
    _______, _______, _______, _______, _______,          _______,          _______,          _______, _______, _______, _______, _______,
                                        _______, _______, _______,          _______, _______, _______
  ),
  [L_MoveSelect] = LAYOUT_moonlander(
    _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
    _______, SC_CS_L, SC_S_L,  SC_S_R,  SC_CS_R, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, SC_CS_H, SC_S_H,  SC_S_E,  SC_CS_E, _______,
    _______, SC_C_L,  KC_LEFT, KC_RGHT, SC_C_R,  KC_UP,   XXXXXXX,          XXXXXXX, KC_PGUP, SC_C_H,  KC_HOME, KC_END,  SC_C_E,  _______,
    _______, SC_C_BS, KC_BSPC, KC_DEL,  SC_C_DL, KC_DOWN,                            KC_PGDN, C(FR_V), C(FR_C), C(FR_X), C(FR_A), _______,
    _______, _______, _______, _______, _leave_,          _______,          _______,          _______, _______, DM_PLY1, DM_PLY2, _______,
                                        _______, _______, _leave_,          _______, _______, _______
  ),
  [L_WindowsTerminals] = LAYOUT_moonlander(
    _______, SC_CF1,  SC_CF2,  SC_CF3,  SC_CF4,  SC_CF5,  _______,          _______, SC_CF6,  SC_CF7,  SC_CF8,  SC_CF9,  SC_CF10, _______,
    _______, KC_F3,   KC_F9,   KC_F10,  KC_F4,   XXXXXXX, _______,          _______, XXXXXXX, SC_GSF1, SC_GSF2, SC_GSF3, SC_GSF4, _______,
    _______, SC_CGSL, SC_S_L,  SC_S_R,  SC_CGSR, XXXXXXX, _______,          _______, XXXXXXX, SC_GF1,  SC_GF2,  SC_GF3,  SC_GF4,  _______,
    _______, XXXXXXX, SC_S_TB, KC_TAB,  XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, _______, _______, _______, _______,          _leave_,          _______,          _______, _______, _______, _______, _______,
                                        _______, _______, _______,          _______, _______, _______
  ),
  [L_DvorakAccents] = LAYOUT_moonlander(
    _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, FR_Y,    _______,          _______, XXXXXXX, XXXXXXX, FR_C,    XXXXXXX, XXXXXXX, _______,
    _______, FR_A,    FR_O,    FR_E,    FR_U,    FR_I,    _______,          _______, FR_DIAE, FR_ACUT, FR_DCIR, FR_DGRV, FR_CEDL, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, XXXXXXX, XXXXXXX, _______, _______,          _______,          XXXXXXX,          _______, _leave_, XXXXXXX, _______, _______,
                                        _______, _______, _______,          XXXXXXX, XXXXXXX, XXXXXXX
  ),
  [L_Symbols] = LAYOUT_moonlander(
    _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
    _______, FR_LCBR, FR_LABK, FR_LPRN, FR_LBRC, FR_UNDS, _______,          _______, FR_EQL,  FR_RBRC, FR_RPRN, FR_RABK, FR_RCBR, _______,
    _______, FR_DLR,  FR_DQUO, FR_MINS, FR_PERC, FR_AMPR, _______,          _______, FR_PIPE, FR_AT,   FR_PLUS, FR_QUOT, FR_TILD, _______,
    _______, FR_LDAQ, FR_EXLM, FR_SLSH, FR_BSLS, SC_NBSP,                            FR_DEG,  FR_HASH, FR_ASTR, FR_QUES, FR_RDAQ, _______,
    _______, _______, _______, _______, _______,          _______,          _______,          _leave_, _______, XXXXXXX, XXXXXXX, _______,
                                        _______, _______, _______,          _______, _______, _______
  ),
  [L_Phrase] = LAYOUT_moonlander(
    _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
    SC_CS_M, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _leave_,
    SC_C_M,  _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
    _______, _______, _______, C(FR_E), C(FR_J),          TD_SEG,          C(S(FR_F)),        _______, _______, _______, _______, _______,
                                        TD_TMTB,C(S(FR_M)),SC_CA_L,         SC_CA_R, KC_TAB, C(KC_INS)
  ),
  [L_Numbers] = LAYOUT_moonlander(
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,          _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, FR_SCLN, FR_7,    FR_8,    FR_9,    FR_COMM, _______,          _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, FR_COLN, FR_4,    FR_5,    FR_6,    FR_DOT,  _______,          _______, FR_EQL,  FR_PLUS, FR_MINS, FR_ASTR, FR_SLSH, _______,
    _______, FR_0,    FR_1,    FR_2,    FR_3,    XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, _______, _______, _______, _leave_,          _______,          TD_LGUI,          _______, _______, _______, _______, _______,
                                        _______, _______, _______,          TD_LALT, TD_LCTL, TD_LSFT
  ),
  [L_FnMouse] = LAYOUT_moonlander(
    _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
    _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, _______,          _______, XXXXXXX, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, _______,
    _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX, _______,          _______, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, _______, _______, _______, _______,          _leave_,          TD_LGUI,          _______, _______, _______, _______, _______,
                                        _______, _______, _______,          TD_LALT, TD_LCTL, TD_LSFT
  ),
  [L_Web] = LAYOUT_moonlander(
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,          _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, XXXXXXX, XXXXXXX,C(KC_EQL),XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _leave_,
    _______, XXXXXXX, XXXXXXX, C(KC_0), XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, XXXXXXX, XXXXXXX,C(KC_MINS),XXXXXXX,XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, TD_RFSH,          KC_WBAK,          KC_WFWD,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                                        KC_UP,   KC_PGUP, C(S(KC_TAB)),   C(KC_TAB), KC_PGDN, KC_DOWN
  ),
  [L_RGBControl] = LAYOUT_moonlander(
    QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, IL_TOGG, NK_TOGG,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    EE_CLR,  XXXXXXX, RGB_SAI, RGB_VAI, RGB_HUI, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, RGB_SAD, RGB_VAD, RGB_HUD, XXXXXXX, XXXXXXX,          XXXXXXX, KC_MPRV, KC_MRWD, KC_MPLY, KC_MFFD, KC_MNXT, XXXXXXX,
    RGB_MOD, XXXXXXX, DM_REC1, DM_REC2, DM_RSTP, XXXXXXX,                            XXXXXXX, KC_VOLU, KC_MUTE, KC_VOLD, XXXXXXX, XXXXXXX,
#if defined AUDIO_CLICKY && (defined MIDI_BASIC || defined MIDI_ADVANCED)
    TG_Mus,  TG_MIDI, CK_TOGG, XXXXXXX, XXXXXXX,          RGB_TOG,          LC_TOGG,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _leave_,
#elif defined MIDI_BASIC || defined MIDI_ADVANCED
    TG_Mus,  TG_MIDI, XXXXXXX, XXXXXXX, XXXXXXX,          RGB_TOG,          LC_TOGG,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _leave_,
#elif defined AUDIO_CLICKY
    TG_Mus,  XXXXXXX, CK_TOGG, XXXXXXX, XXXXXXX,          RGB_TOG,          LC_TOGG,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _leave_,
#else
    TG_Mus,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          RGB_TOG,          LC_TOGG,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _leave_,
#endif
                                        RGB_SPI, RGB_SLD, RGB_SPD,          DT_UP,   DT_PRNT, DT_DOWN
  ),
  [L_Music] = LAYOUT_moonlander(
    MU_TOGG, MU_NEXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _leave_, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                                        XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX
  ),
#if defined MIDI_BASIC || defined MIDI_ADVANCED
  [L_MIDI] = LAYOUT_moonlander(
    MI_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,          _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    MI_C,    MI_Cs,   MI_D,    MI_Ds,   MI_E,    MI_F,    XXXXXXX,          MI_Fs,   MI_G,    MI_Gs,   MI_A,    MI_As,   MI_B,    MI_C1,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, _leave_, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
#    ifdef MIDI_ADVANCED
                                        MI_OCTU, MI_VELU, MI_CHNU,          MI_CHND, MI_VELD, MI_OCTD
#    else
                                        XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX
#    endif
  ),
#endif
  [L_DvorakRaw] = LAYOUT_moonlander(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS,          KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    DF_Dvor,
    KC_TAB,  KC_SLSH, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_LBRC,          KC_RBRC, KC_F,    KC_G,    KC_C,    KC_R,    KC_X,    KC_ESC,
    KC_CAPS, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_QUOT,          KC_BSLS, KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_ENT,
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_L,                               KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_BSPC,          KC_PGUP,          KC_UP,            KC_DEL,  KC_RALT, KC_RGUI, KC_APP,  KC_RCTL,
                                        KC_HOME, KC_PGDN, KC_END,           KC_LEFT, KC_DOWN, KC_RGHT
  ),
};

bool window_terminal_was_active = false;

/* Keeps the Left Alt key held as long as the L_WindowsTerminals layer which
 * contains keyboard shortcuts that all use Left Alt, is active. This allows
 * the use of layer entry methods other than LM().
 * That is done this way because of the Alt+Tab and Alt+Shift+Tab shortcuts,
 * which keep the GUI to switch windows active while Alt is pressed. */
layer_state_t window_terminal_layer(layer_state_t state) {
    bool window_terminal_is_active = layer_state_cmp(state, L_WindowsTerminals) != 0;
    if (window_terminal_is_active != window_terminal_was_active) {
        window_terminal_was_active = window_terminal_is_active;
        if (window_terminal_is_active) {
            add_mods(MOD_LALT);
        } else {
            del_mods(MOD_LALT);
        }
        send_keyboard_report();
    }
    return state;
}

layer_state_t qwerty_ctrl_layer(layer_state_t state, layer_state_t default_state) {
    /* Act as if the default layer is layer 0 (bit 0 set) if none is set. */
    default_state = default_state ? default_state : 1;
    /* If we're on any keyboard layout layer other than QWERTY, and the topmost
     * layer is below the L_Control layer, which provides the QWERTY layer when
     * Control is held, or the L_Control layer itself, and Control is held, the
     * L_Control layer needs to be activated. */
    if (layer_state_cmp(default_state, L_DvorakLX)
     && (get_mods() & MOD_MASK_CTRL)
     && get_highest_layer(state | default_state) <= L_Control) {
        state |= (layer_state_t)1 << L_Control;
    } else {
        state &= ~((layer_state_t)1 << L_Control);
    }
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_SLD:
            if (record->event.pressed) {
                rgblight_mode(1);
            }
            return false;
    }
    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    layer_state_set(qwerty_ctrl_layer(layer_state, default_layer_state));
}

layer_state_t layer_state_set_user(layer_state_t state) {
    layer_state_t result = window_terminal_layer(state);
    return qwerty_ctrl_layer(result, default_layer_state);
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD_LOCK:
            return g_tapping_term + 200;
        default:
            return g_tapping_term;
    }
}
