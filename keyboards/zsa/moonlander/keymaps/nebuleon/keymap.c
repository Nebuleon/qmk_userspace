#include "common.h"

enum custom_keycodes {
    RGB_SLD = SAFE_RANGE,
};

#define TT_QWAc TT(L_QWERTYAccents)
#define TT_DvAc TT(L_DvorakAccents)
#define TT_Move TT(L_MoveSelect)
#define TT_Syms TT(L_Symbols)
#define TT_Nums TT(L_Numbers)
#define TT_FnMs TT(L_FnMouse)
#define TT_Web  TT(L_Web)
#define TT_RGBC TT(L_RGBControl)
#define TG_Mus  TG(L_Music)
#if defined MIDI_BASIC || defined MIDI_ADVANCED
#    define TG_MIDI TG(L_MIDI)
#endif
#define DF_Dvor DF(L_DvorakBLX)
#define DF_DRaw DF(L_DvorakRaw)
/* Other */
#define _leave_ _______              /* denotes a key that must be transparent because it exits a layer */

/* Modified: TO() layer keys are now DF() keys; TD() keys now have DANCE_ removed */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_DvorakBLX] = LAYOUT_moonlander(
    KC_ESC,  TD_1_F1, TD_2_F2, TD_3_F3, TD_4_F4, TD_5_F5, KC_PSCR,          TD_LOCK, TD_6_F6, TD_7_F7, TD_8_F8, TD_9_F9, TD_0F10, DF_DRaw,
    TT_FnMs, TD_SCBS, TD_CMEX, TD_DTQU, TD_P_AT, TD_Y_AM, KC_UP,            KC_LEFT, TD_F_PI, TD_G_DL, TD_C_LP, TD_R_RP, TD_X_TI, _______,
    TT_Web,  TD_A_SQ, TD_O_LB, TD_E_RB, TD_U_DQ, TD_I_UN, KC_DOWN,          KC_RGHT, TD_D_EQ, TD_H_PL, TD_T_MI, TD_N_AS, TD_S_SL, KC_BSPC,
    KC_LSFT, TD_CLLD, TD_Q_LC, TD_J_RC, TD_K_HA, TD_B_NB,                            TD_L_DG, TD_M_PC, TD_W_RA, TD_V_LA, TD_Z_RD, KC_DEL,
    KC_LCTL, KC_LGUI, KC_LALT, TT_Move, TT_Nums,          _______,          TD_LGUI,          TT_Syms, TT_DvAc, SC_RAAP, _______, TT_RGBC,
                                        KC_SPC,  KC_ENT,  SC_TAWT,          TD_LALT, TD_LCTL, TD_LSFT
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
    _______, _______, _______, _leave_, _______,          _______,          _______,          _______, _______, DM_PLY1, DM_PLY2, _______,
                                        _______, _______, _______,          _______, _______, _______
  ),
  [L_WindowsTerminals] = LAYOUT_moonlander(
    _______, SC_CF1,  SC_CF2,  SC_CF3,  SC_CF4,  SC_CF5,  _______,          _______, SC_CF6,  SC_CF7,  SC_CF8,  SC_CF9,  SC_CF10, _______,
    _______, KC_F3,   KC_F9,   KC_F10,  KC_F4,   SC_G_PL, _______,          _______, XXXXXXX, SC_GSF1, SC_GSF2, SC_GSF3, SC_GSF4, _______,
    _______, SC_CGSL, SC_S_L,  SC_S_R,  SC_CGSR, SC_G_0,  _______,          _______, XXXXXXX, SC_GF1,  SC_GF2,  SC_GF3,  SC_GF4,  _______,
    _______, XXXXXXX, SC_S_T,  KC_TAB,  XXXXXXX, SC_G_MI,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, _______, _______, _______, _______,          _______,          _______,          _______, _______, _______, _______, _______,
                                        _______, _______, _leave_,          _______, _______, _______
  ),
  [L_DvorakAccents] = LAYOUT_moonlander(
    _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TD_Y_S,  _______,          _______, XXXXXXX, XXXXXXX, TD_C_S,  XXXXXXX, XXXXXXX, _______,
    _______, TD_A_S,  TD_O_S,  TD_E_S,  TD_U_S,  TD_I_S,  _______,          _______, FR_DIAE, FR_ACUT, FR_DCIR, FR_DGRV, FR_CEDL, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, XXXXXXX, XXXXXXX, _______, _______,          _______,          _______,          _______, _leave_, XXXXXXX, _______, _______,
                                        _______, _______, _______,          _______, _______, _______
  ),
  [L_Symbols] = LAYOUT_moonlander(
    _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
    _______, FR_BSLS, FR_EXLM, FR_QUES, FR_AT,   FR_AMPR, _______,          _______, FR_PIPE, FR_DLR,  FR_RPRN, FR_LPRN, FR_TILD, _______,
    _______, FR_QUOT, FR_LBRC, FR_RBRC, FR_DQUO, FR_UNDS, _______,          _______, FR_EQL,  FR_PLUS, FR_MINS, FR_ASTR, FR_SLSH, _______,
    _______, FR_LDAQ, FR_LCBR, FR_RCBR, FR_HASH, SC_NBSP,                            FR_DEG,  FR_PERC, FR_RABK, FR_LABK, FR_RDAQ, _______,
    _______, _______, _______, _______, _______,          _______,          _______,          _leave_, _______, XXXXXXX, XXXXXXX, _______,
                                        _______, _______, _______,          _______, _______, _______
  ),
  [L_Numbers] = LAYOUT_moonlander(
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,          _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, FR_SCLN, FR_7,    FR_8,    FR_9,    FR_COMM, _______,          _______, XXXXXXX, FR_DLR,  FR_RPRN, FR_LPRN, XXXXXXX, _______,
    _______, FR_0,    FR_4,    FR_5,    FR_6,    FR_DOT,  _______,          _______, FR_EQL,  FR_PLUS, FR_MINS, FR_ASTR, FR_SLSH, _______,
    _______, FR_COLN, FR_1,    FR_2,    FR_3,    SC_NBSP,                            FR_DEG,  FR_PERC, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, _______, _______, _______, _leave_,          _______,          _______,          _______, _______, _______, _______, _______,
                                        _______, _______, _______,          _______, _______, _______
  ),
  [L_FnMouse] = LAYOUT_moonlander(
    _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
    _leave_, KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, _______,          _______, XXXXXXX, MS_BTN1, MS_UP,   MS_BTN2, MS_WHLU, _______,
    _______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX, _______,          _______, XXXXXXX, MS_LEFT, MS_DOWN, MS_RGHT, MS_WHLD, _______,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, _______, _______, _______, _______,          _______,          _______,          _______, _______, _______, _______, _______,
                                        _______, _______, _______,          _______, _______, _______
  ),
  [L_Web] = LAYOUT_moonlander(
    _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
    _______,C(S(FR_T)),TD_RFSH,C(FR_T), C(FR_W), SC_C_PL, _______,          _______, SC_CA_Z, MS_BTN1, MS_UP,   MS_BTN2, MS_WHLU, _______,
    _leave_, KC_UP,   KC_WBAK, KC_WFWD, KC_PGUP, SC_C_0,  _______,          _______, XXXXXXX, MS_LEFT, MS_DOWN, MS_RGHT, MS_WHLD, _______,
    _______, KC_DOWN, SC_CS_T, SC_C_T,  KC_PGDN, SC_C_MI,                            XXXXXXX, C(FR_V), C(FR_C), C(FR_X), C(FR_A), _______,
    _______, _______, _______, _______, _______,          _______,          _______,          _______, _______, _______, _______, _______,
                                        _______, _______, _______,          _______, _______, _______
  ),
  [L_RGBControl] = LAYOUT_moonlander(
    QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, IL_TOGG, NK_TOGG,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    EE_CLR,  XXXXXXX, RM_SATU, RM_VALU, RM_HUEU, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, RM_SATD, RM_VALD, RM_HUED, XXXXXXX, XXXXXXX,          XXXXXXX, KC_MPRV, KC_MRWD, KC_MPLY, KC_MFFD, KC_MNXT, XXXXXXX,
    RM_NEXT, XXXXXXX, DM_REC1, DM_REC2, DM_RSTP, XXXXXXX,                            XXXXXXX, KC_VOLU, KC_MUTE, KC_VOLD, XXXXXXX, XXXXXXX,
#if defined AUDIO_CLICKY && (defined MIDI_BASIC || defined MIDI_ADVANCED)
    TG_Mus,  TG_MIDI, CK_TOGG, XXXXXXX, XXXXXXX,          RM_TOGG,          LC_TOGG,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _leave_,
#elif defined MIDI_BASIC || defined MIDI_ADVANCED
    TG_Mus,  TG_MIDI, XXXXXXX, XXXXXXX, XXXXXXX,          RM_TOGG,          LC_TOGG,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _leave_,
#elif defined AUDIO_CLICKY
    TG_Mus,  XXXXXXX, CK_TOGG, XXXXXXX, XXXXXXX,          RM_TOGG,          LC_TOGG,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _leave_,
#else
    TG_Mus,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          RM_TOGG,          LC_TOGG,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _leave_,
#endif
                                        RM_SPDU, RGB_SLD, RM_SPDD,          DT_UP,   DT_PRNT, DT_DOWN
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
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_B,                               KC_L,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
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
    if (layer_state_cmp(default_state, L_DvorakBLX)
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
