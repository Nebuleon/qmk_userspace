#include "common.h"
#include "rgb.h"

extern rgb_config_t rgb_matrix_config;

#define REDUCE_BRIGHTNESS(b) ((b) / 2 - (b) / 8)
#define BLINK_BRIGHTNESS(b) (timer_read_fast() & 0x100 ? (b) : 0)

const HSV PROGMEM led_palette[] = {
    [PAL_NONE] = { .h =   0, .s =   0, .v =   0 }, /* PAL_NONE must be the only unlit palette entry */
    [PAL_QLTR] = { .h =   0, .s =   0, .v = 255 }, /* QWERTY letters */
    [PAL_DLTR] = { .h = 172, .s =  95, .v = 255 }, /* Dvorak letters */
    [PAL_DIG]  = { .h =   0, .s =   0, .v = 128 }, /* digits */
    [PAL_DIGF] = { .h =  86, .s = 192, .v = 128 }, /* tap dances with digits and F<number> keys */
    [PAL_FN]   = { .h =  86, .s = 255, .v = 128 }, /* F<number> keys */
    [PAL_SYM]  = { .h = 193, .s = 255, .v = 255 }, /* symbols */
    [PAL_ACC]  = { .h =  21, .s = 255, .v = 255 }, /* accents and accented letters */
    [PAL_BSPC] = { .h =  10, .s = 255, .v = 255 }, /* Backspace */
    [PAL_DEL]  = { .h =  32, .s = 255, .v = 255 }, /* Delete */
    [PAL_ESC]  = { .h =   0, .s = 255, .v = 128 }, /* Escape */
    [PAL_ENT]  = { .h =  43, .s = 255, .v = 255 }, /* Enter */
    [PAL_TAB]  = { .h =  43, .s = 255, .v = 136 }, /* Tab */
    [PAL_SPC]  = { .h = 150, .s = 255, .v = 255 }, /* Space */
    [PAL_MOD]  = { .h =  86, .s = 255, .v = 255 }, /* modifier keys */
    [PAL_PSCR] = { .h =  59, .s = 255, .v = 255 }, /* Print Screen */
    [PAL_LOCK] = { .h = 236, .s = 255, .v = 255 }, /* GUI+L for locking the session */
    [PAL_CAPS] = { .h = 150, .s = 255, .v = 255 }, /* Caps Word and Caps Lock */
    [PAL_NAV1] = { .h = 129, .s = 255, .v = 128 }, /* single-step navigation keys: Up, Down, Left, Right */
    [PAL_NAV2] = { .h = 129, .s = 255, .v = 255 }, /* multi-step navigation keys: Page Up, Page Down, Home, End */
    [PAL_MOV1] = { .h = 129, .s = 255, .v = 128 }, /* single-step navigation keys on L_MoveSelect: Left, Right */
    [PAL_MOVW] = { .h = 129, .s = 255, .v = 192 }, /* word-step navigation keys on L_MoveSelect: Ctrl+Left, Ctrl+Right */
    [PAL_MOVL] = { .h = 129, .s = 255, .v = 255 }, /* line-step navigation keys on L_MoveSelect: Home, End */
    [PAL_MOVE] = { .h = 129, .s = 191, .v = 255 }, /* extremity navigation keys on L_MoveSelect: Ctrl+Home, Ctrl+End */
    [PAL_SEL1] = { .h = 172, .s = 255, .v = 128 }, /* single-step selection keys on L_MoveSelect: Shift+Left, Shift+Right */
    [PAL_SELW] = { .h = 172, .s = 255, .v = 192 }, /* word-step selection keys on L_MoveSelect: C+S+Left, C+S+Right */
    [PAL_SELL] = { .h = 172, .s = 255, .v = 255 }, /* line-step selection keys on L_MoveSelect: Shift+Home, Shift+End */
    [PAL_SELE] = { .h = 172, .s = 191, .v = 255 }, /* extremity selection keys on L_MoveSelect: C+S+Home, C+S+End */
    [PAL_BSP1] = { .h =  10, .s = 255, .v = 128 }, /* single-step Backspace on L_MoveSelect */
    [PAL_BSPW] = { .h =  10, .s = 255, .v = 255 }, /* word-step Backspace on L_MoveSelect: Ctrl+Backspace */
    [PAL_DEL1] = { .h =  32, .s = 255, .v = 128 }, /* single-step Delete on L_MoveSelect */
    [PAL_DELW] = { .h =  32, .s = 255, .v = 255 }, /* word-step Delete on L_MoveSelect: Ctrl+Delete */
    [PAL_SELA] = { .h = 172, .s = 127, .v = 255 }, /* Select All shortcut on L_MoveSelect: Ctrl+A */
    [PAL_CUT]  = { .h =   0, .s = 255, .v = 255 }, /* Cut shortcut on L_MoveSelect: Ctrl+X */
    [PAL_COPY] = { .h =  86, .s = 255, .v = 255 }, /* Copy shortcut on L_MoveSelect: Ctrl+C */
    [PAL_PSTE] = { .h = 172, .s = 255, .v = 255 }, /* Paste shortcut on L_MoveSelect: Ctrl+V */
    [PAL_TERM] = { .h =  86, .s = 255, .v = 255 }, /* Terminal switching shortcuts on L_WindowsTerminals: Ctrl+Shift+(Alt+)F<number> */
    [PAL_SHDE] = { .h =  43, .s = 255, .v = 128 }, /* Toggle window shading shortcut on L_WindowsTerminals: (Alt+)F3 */
    [PAL_MIN]  = { .h =  43, .s = 255, .v = 255 }, /* Minimize window shortcut on L_WindowsTerminals: (Alt+)F9 */
    [PAL_MAX]  = { .h =  86, .s = 255, .v = 255 }, /* Toggle window maximization shortcut on L_WindowsTerminals: (Alt+)F10 */
    [PAL_CLSE] = { .h =   0, .s = 255, .v = 255 }, /* Close window shortcut on L_WindowsTerminals: (Alt+)F4 */
    [PAL_TILE] = { .h = 129, .s = 255, .v = 255 }, /* Window tiling shortcuts on L_WindowsTerminals: (Alt+)Shift+Left, (Alt+)Shift+Right */
    [PAL_SCRN] = { .h = 129, .s = 191, .v = 255 }, /* Move window one screen left/right shortcuts on L_WindowsTerminals: Ctrl+GUI+(Alt+)Shift+Left, Ctrl+GUI+(Alt+)Shift+Right */
    [PAL_WNDW] = { .h = 129, .s = 255, .v = 128 }, /* Window navigation shortcuts on L_WindowsTerminals: (Alt+)Shift+Tab, (Alt+)Tab */
    [PAL_WSSW] = { .h = 129, .s = 255, .v = 128 }, /* Workspace switching shortcuts on L_WindowsTerminals: GUI+(Alt+)Shift+F<number> */
    [PAL_WSMO] = { .h = 172, .s = 255, .v = 128 }, /* Window move to workspace shortcuts on L_WindowsTerminals: GUI+(Alt+)F<number> */
    [PAL_SPLT] = { .h =   0, .s = 255, .v = 255 }, /* Split shortcut on L_Phrase: Ctrl+E */
    [PAL_JOIN] = { .h =  86, .s = 255, .v = 255 }, /* Join shortcut on L_Phrase: Ctrl+J */
    [PAL_SEG]  = { .h =  86, .s = 255, .v = 255 }, /* Accept and Reject segment shortcuts on L_Phrase: Ctrl+Enter, C+S+Enter */
    [PAL_COMM] = { .h = 150, .s = 255, .v = 255 }, /* Add comment shortcut on L_Phrase: C+S+M */
    [PAL_TMTB] = { .h = 150, .s = 255, .v = 255 }, /* (Exact) search in TM/TB shortcuts on L_Phrase: Ctrl+K, C+S+K */
    [PAL_TABS] = { .h = 215, .s = 255, .v = 255 }, /* keys for moving between tabs in L_Web and L_Phrase */
    [PAL_FLTR] = { .h = 150, .s = 255, .v = 255 }, /* Filter shortcut on L_Phrase: C+S+F */
    [PAL_SINS] = { .h =   0, .s = 255, .v = 255 }, /* Copy source to target shortcut on L_Phrase: Ctrl+Insert */
    [PAL_SUP]  = { .h =   0, .s =   0, .v = 255 }, /* Superscript shortcut on L_Phrase */
    [PAL_SUB]  = { .h =   0, .s =   0, .v = 128 }, /* Subscript shortcut on L_Phrase */
    [PAL_MBTN] = { .h = 112, .s = 255, .v = 255 }, /* mouse buttons */
    [PAL_MMOV] = { .h = 112, .s = 255, .v = 128 }, /* mouse movement */
    [PAL_MWHL] = { .h =   0, .s =   0, .v = 192 }, /* mouse wheel */
    [PAL_ZIN]  = { .h =  43, .s = 255, .v = 255 }, /* zoom in: Ctrl+[+] */
    [PAL_ZOUT] = { .h =  43, .s = 255, .v = 128 }, /* zoom out: Ctrl+- */
    [PAL_ZRST] = { .h =  86, .s = 255, .v = 255 }, /* zoom reset: Ctrl+0 */
    [PAL_RFSH] = { .h =  86, .s = 255, .v = 255 }, /* Refresh: F5, Ctrl+F5 */
    [PAL_WEBN] = { .h =  86, .s = 255, .v = 255 }, /* Web navigation: WWW Back, WWW Forward */
    [PAL_BOOT] = { .h =   0, .s = 255, .v = 255 }, /* QK_BOOT, reboots to the bootloader */
    [PAL_CLR]  = { .h =   0, .s = 255, .v = 255 }, /* EE_CLR, erases the EEPROM */
    [PAL_RGBM] = { .h =   0, .s =   0, .v = 255 }, /* RGB_MOD, changes the active RGB animation */
    [PAL_DREC] = { .h =   0, .s = 255, .v = 255 }, /* DM_RECn, starts recording a dynamic macro */
    [PAL_DPLY] = { .h =  43, .s = 255, .v = 255 }, /* DM_PLYn, plays a dynamic macro */
    [PAL_DSTP] = { .h =   0, .s = 255, .v = 255 }, /* DM_STOP, stops recording the current dynamic macro */
    [PAL_SAI]  = { .h = 129, .s = 255, .v = 255 }, /* RGB_SAI, saturation increase */
    [PAL_SAD]  = { .h =   0, .s =   0, .v = 255 }, /* RGB_SAD, saturation decrease */
    [PAL_VAI]  = { .h =   0, .s =   0, .v = 255 }, /* RGB_VAI, value increase */
    [PAL_VAD]  = { .h =   0, .s =   0, .v = 128 }, /* RGB_VAD, value decrease */
    [PAL_HUI]  = { .h = 172, .s = 255, .v = 255 }, /* RGB_HUI, hue increase */
    [PAL_HUD]  = { .h =  86, .s = 255, .v = 255 }, /* RGB_HUD, hue decrease */
    [PAL_RGBT] = { .h =   0, .s = 255, .v = 255 }, /* RGB_TOG, RGB toggle */
    [PAL_SLD]  = { .h =   0, .s = 255, .v = 255 }, /* RGB_SLD, pause RGB animation */
    [PAL_SLOW] = { .h =   0, .s =   0, .v = 112 }, /* for things that slow down, like RGB_SPD, RGB speed decrease */
    [PAL_FAST] = { .h =   0, .s =   0, .v = 255 }, /* for things that speed up, like RGB_SPI, RGB speed increase */
    [PAL_LCTG] = { .h = 172, .s = 255, .v = 255 }, /* LC_TOGG, layer color toggle */
    [PAL_ILTG] = { .h = 172, .s = 255, .v = 255 }, /* IL_TOGG, indicator LED toggle */
    [PAL_NKRO] = { .h =  86, .s = 255, .v = 255 }, /* NK_TOGG, n-key rollover (NKRO) toggle */
    [PAL_DTTP] = { .h = 193, .s = 255, .v = 255 }, /* DT_PRNT, dynamic tapping term print */
    [PAL_MPRV] = { .h = 128, .s = 255, .v = 255 }, /* media previous track */
    [PAL_MRWD] = { .h = 172, .s = 255, .v = 128 }, /* media rewind */
    [PAL_MPLY] = { .h =  86, .s = 255, .v = 255 }, /* media play/pause */
    [PAL_MFFD] = { .h = 172, .s = 255, .v = 255 }, /* media fast-forward */
    [PAL_MNXT] = { .h = 129, .s = 255, .v = 255 }, /* media next track */
    [PAL_VOLU] = { .h =  43, .s = 255, .v = 255 }, /* media volume up */
    [PAL_VOLD] = { .h =  43, .s = 255, .v = 128 }, /* media volume down */
    [PAL_MUTE] = { .h =   0, .s = 255, .v = 255 }, /* media mute */
    [PAL_MUST] = { .h =  86, .s = 255, .v = 255 }, /* MU_TOGG, music mode toggle */
    [PAL_MUSM] = { .h = 172, .s = 255, .v = 255 }, /* MU_NEXT, next music mode */
    [PAL_MUS]  = { .h = 215, .s = 255, .v = 255 }, /* keys set to KC_NO on L_Music */
    [PAL_APP]  = { .h =  75, .s = 255, .v = 255 }, /* Application (context menu key) */

    [PAL_Accs] = { .h =  21, .s = 255, .v = 255 }, /* layer entry to L_*Accents */
    [PAL_Move] = { .h = 129, .s = 255, .v = 255 }, /* layer entry to L_MoveSelect */
    [PAL_Syms] = { .h = 193, .s = 255, .v = 255 }, /* layer entry to L_Symbols */
    [PAL_Phrs] = { .h = 118, .s = 255, .v = 240 }, /* layer entry to L_Phrase */
    [PAL_Nums] = { .h =   0, .s =   0, .v = 255 }, /* layer entry to L_Numbers */
    [PAL_FnMs] = { .h =  86, .s = 255, .v = 255 }, /* layer entry to L_FnMouse */
    [PAL_Web]  = { .h = 129, .s = 255, .v = 255 }, /* layer entry to L_Web */
    [PAL_RGBC] = { .h = 129, .s = 255, .v = 255 }, /* layer entry to L_RGBControl */
    [PAL_Mus]  = { .h =  43, .s = 255, .v = 255 }, /* layer entry to L_Music */
    [PAL_RawI] = { .h =   0, .s =   0, .v =  64 }, /* layer entry to L_*Raw */
    [PAL_RawO] = { .h =   0, .s =   0, .v = 255 }, /* layer exit from L_*Raw */
    [PAL_UNKN] = { .h =   0, .s = 255, .v = 255 }, /* unknown colors */
};


const uint8_t PROGMEM ledmaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_DvorakLX] = LEDMAP_moonlander(
    PAL_ESC,  PAL_DIGF, PAL_DIGF, PAL_DIGF, PAL_DIGF, PAL_DIGF, PAL_PSCR,          PAL_LOCK, PAL_DIGF, PAL_DIGF, PAL_DIGF, PAL_DIGF, PAL_DIGF, PAL_RawI,
    ________, PAL_SYM,  PAL_SYM,  PAL_SYM,  PAL_DLTR, PAL_DLTR, PAL_NAV1,          PAL_NAV1, PAL_DLTR, PAL_DLTR, PAL_DLTR, PAL_DLTR, PAL_DLTR, PAL_Web,
    PAL_BSPC, PAL_DLTR, PAL_DLTR, PAL_DLTR, PAL_DLTR, PAL_DLTR, PAL_NAV1,          PAL_NAV1, PAL_DLTR, PAL_DLTR, PAL_DLTR, PAL_DLTR, PAL_DLTR, PAL_Phrs,
    PAL_DEL,  PAL_SYM,  PAL_DLTR, PAL_DLTR, PAL_DLTR, PAL_DLTR,                              PAL_DLTR, PAL_DLTR, PAL_DLTR, PAL_DLTR, PAL_DLTR, ________,
    ________, PAL_MOD,  PAL_MOD,  PAL_Move, PAL_Nums,           PAL_FnMs,          PAL_MOD,            PAL_Syms, PAL_Accs, PAL_MOD,  ________, PAL_RGBC,
                                            PAL_SPC,  PAL_ENT,  PAL_TAB,           PAL_MOD,  PAL_MOD,  PAL_MOD
  ),
  [L_Control] = LEDMAP_moonlander(
    ________, ________, ________, ________, ________, ________, ________,          ________, ________, ________, ________, ________, ________, ________,
    ________, PAL_QLTR, PAL_QLTR, PAL_QLTR, PAL_QLTR, PAL_QLTR, ________,          ________, PAL_QLTR, PAL_QLTR, PAL_QLTR, PAL_QLTR, PAL_QLTR, ________,
    ________, PAL_QLTR, PAL_QLTR, PAL_QLTR, PAL_QLTR, PAL_QLTR, ________,          ________, PAL_QLTR, PAL_QLTR, PAL_QLTR, PAL_QLTR, PAL_SYM,  ________,
    ________, PAL_QLTR, PAL_QLTR, PAL_QLTR, PAL_QLTR, PAL_QLTR,                              PAL_QLTR, PAL_QLTR, PAL_SYM,  PAL_SYM,  PAL_SYM,  ________,
    ________, ________, ________, ________, ________,           ________,          ________,           ________, ________, ________, ________, ________,
                                            ________, ________, ________,          ________, ________, ________
  ),
  [L_MoveSelect] = LEDMAP_moonlander(
    ________, ________, ________, ________, ________, ________, ________,          ________, ________, ________, ________, ________, ________, ________,
    ________, PAL_SELW, PAL_SEL1, PAL_SEL1, PAL_SELW, XXXXXXXX, XXXXXXXX,          XXXXXXXX, XXXXXXXX, PAL_SELE, PAL_SELL, PAL_SELL, PAL_SELE, ________,
    ________, PAL_MOVW, PAL_MOV1, PAL_MOV1, PAL_MOVW, PAL_NAV1, XXXXXXXX,          XXXXXXXX, PAL_NAV2, PAL_MOVE, PAL_MOVL, PAL_MOVL, PAL_MOVE, ________,
    ________, PAL_BSPW, PAL_BSP1, PAL_DEL1, PAL_DELW, PAL_NAV1,                              PAL_NAV2, PAL_PSTE, PAL_COPY, PAL_CUT,  PAL_SELA, ________,
    ________, ________, ________, _lleave_, ________,           ________,          ________,           ________, ________, PAL_DPLY, PAL_DPLY, ________,
                                            ________, ________, ________,          ________, ________, ________
  ),
  [L_WindowsTerminals] = LEDMAP_moonlander(
    ________, PAL_TERM, PAL_TERM, PAL_TERM, PAL_TERM, PAL_TERM, ________,          ________, PAL_TERM, PAL_TERM, PAL_TERM, PAL_TERM, PAL_TERM, ________,
    ________, PAL_SHDE, PAL_MIN,  PAL_MAX,  PAL_CLSE, XXXXXXXX, ________,          ________, XXXXXXXX, PAL_WSMO, PAL_WSMO, PAL_WSMO, PAL_WSMO, ________,
    ________, PAL_SCRN, PAL_TILE, PAL_TILE, PAL_SCRN, XXXXXXXX, ________,          ________, XXXXXXXX, PAL_WSSW, PAL_WSSW, PAL_WSSW, PAL_WSSW, ________,
    ________, XXXXXXXX, PAL_WNDW, PAL_WNDW, XXXXXXXX, XXXXXXXX,                              XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, ________,
    ________, ________, ________, ________, ________,           _lleave_,          ________,           ________, ________, ________, ________, ________,
                                            ________, ________, ________,          ________, ________, ________
  ),
  [L_DvorakAccents] = LEDMAP_moonlander(
    ________, ________, ________, ________, ________, ________, ________,          ________, ________, ________, ________, ________, ________, ________,
    ________, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, PAL_ACC,  ________,          ________, XXXXXXXX, XXXXXXXX, PAL_ACC,  XXXXXXXX, XXXXXXXX, ________,
    ________, PAL_ACC,  PAL_ACC,  PAL_ACC,  PAL_ACC,  PAL_ACC,  ________,          ________, PAL_ACC,  PAL_ACC,  PAL_ACC,  PAL_ACC,  PAL_ACC,  ________,
    ________, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,                              XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, ________,
    ________, XXXXXXXX, XXXXXXXX, ________, ________,           ________,          XXXXXXXX,           ________, _lleave_, XXXXXXXX, ________, ________,
                                            ________, ________, ________,          XXXXXXXX, XXXXXXXX, XXXXXXXX
  ),
  [L_Symbols] = LEDMAP_moonlander(
    ________, ________, ________, ________, ________, ________, ________,          ________, ________, ________, ________, ________, ________, ________,
    ________, PAL_SYM,  PAL_SYM,  PAL_SYM,  PAL_SYM,  PAL_SYM,  ________,          ________, PAL_SYM,  PAL_SYM,  PAL_SYM,  PAL_SYM,  PAL_SYM,  ________,
    ________, PAL_SYM,  PAL_SYM,  PAL_SYM,  PAL_SYM,  PAL_SYM,  ________,          ________, PAL_SYM,  PAL_SYM,  PAL_SYM,  PAL_SYM,  PAL_SYM,  ________,
    ________, PAL_SYM,  PAL_SYM,  PAL_SYM,  PAL_SYM,  PAL_SPC,                               PAL_SYM,  PAL_SYM,  PAL_SYM,  PAL_SYM,  PAL_SYM,  ________,
    ________, ________, ________, ________, ________,           ________,          ________,           _lleave_, ________, XXXXXXXX, XXXXXXXX, ________,
                                            ________, ________, ________,          ________, ________, ________
  ),
  [L_Phrase] = LEDMAP_moonlander(
    ________, ________, ________, ________, ________, ________, ________,          ________, ________, ________, ________, ________, ________, ________,
    ________, ________, ________, ________, ________, ________, ________,          ________, ________, ________, ________, ________, ________, ________,
    PAL_SUP,  ________, ________, ________, ________, ________, ________,          ________, ________, ________, ________, ________, ________, _lleave_,
    PAL_SUB,  ________, ________, ________, ________, ________,                              ________, ________, ________, ________, ________, ________,
    ________, ________, ________, PAL_SPLT, PAL_JOIN,           PAL_SEG,           PAL_FLTR,           ________, ________, ________, ________, ________,
                                            PAL_TMTB, PAL_COMM, PAL_TABS,          PAL_TABS, PAL_TAB,  PAL_SINS
  ),
  [L_Numbers] = LEDMAP_moonlander(
    ________, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, ________,          ________, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, ________,
    ________, PAL_SYM,  PAL_DIG,  PAL_DIG,  PAL_DIG,  PAL_SYM,  ________,          ________, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, ________,
    ________, PAL_SYM,  PAL_DIG,  PAL_DIG,  PAL_DIG,  PAL_SYM,  ________,          ________, PAL_SYM,  PAL_SYM,  PAL_SYM,  PAL_SYM,  PAL_SYM,  ________,
    ________, PAL_DIG,  PAL_DIG,  PAL_DIG,  PAL_DIG,  XXXXXXXX,                              XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, ________,
    ________, ________, ________, ________, _lleave_,           ________,          PAL_MOD,            ________, ________, ________, ________, ________,
                                            ________, ________, ________,          PAL_MOD,  PAL_MOD,  PAL_MOD
  ),
  [L_FnMouse] = LEDMAP_moonlander(
    ________, ________, ________, ________, ________, ________, ________,          ________, ________, ________, ________, ________, ________, ________,
    ________, PAL_FN,   PAL_FN,   PAL_FN,   PAL_FN,   XXXXXXXX, ________,          ________, XXXXXXXX, PAL_MBTN, PAL_MMOV, PAL_MBTN, PAL_MWHL, ________,
    ________, PAL_FN,   PAL_FN,   PAL_FN,   PAL_FN,   XXXXXXXX, ________,          ________, XXXXXXXX, PAL_MMOV, PAL_MMOV, PAL_MMOV, PAL_MWHL, ________,
    ________, PAL_FN,   PAL_FN,   PAL_FN,   PAL_FN,   XXXXXXXX,                              XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, ________,
    ________, ________, ________, ________, ________,           _lleave_,          PAL_MOD,            ________, ________, ________, ________, ________,
                                            ________, ________, ________,          PAL_MOD,  PAL_MOD,  PAL_MOD
  ),
  [L_Web] = LEDMAP_moonlander(
    ________, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, ________,          ________, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, ________,
    ________, XXXXXXXX, XXXXXXXX, PAL_ZIN,  XXXXXXXX, XXXXXXXX, XXXXXXXX,          XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, _lleave_,
    ________, XXXXXXXX, XXXXXXXX, PAL_ZRST, XXXXXXXX, XXXXXXXX, XXXXXXXX,          XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, ________,
    ________, XXXXXXXX, XXXXXXXX, PAL_ZOUT, XXXXXXXX, XXXXXXXX,                              XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, ________,
    ________, XXXXXXXX, XXXXXXXX, XXXXXXXX, PAL_RFSH,           PAL_WEBN,          PAL_WEBN,           XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, ________,
                                            PAL_NAV1, PAL_NAV2, PAL_TABS,          PAL_TABS, PAL_NAV2, PAL_NAV1
  ),
  [L_RGBControl] = LEDMAP_moonlander(
    PAL_BOOT, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, PAL_ILTG, PAL_NKRO,          XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
    PAL_CLR,  XXXXXXXX, PAL_SAI,  PAL_VAI,  PAL_HUI,  XXXXXXXX, XXXXXXXX,          XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
    XXXXXXXX, XXXXXXXX, PAL_SAD,  PAL_VAD,  PAL_HUD,  XXXXXXXX, XXXXXXXX,          XXXXXXXX, PAL_MPRV, PAL_MRWD, PAL_MPLY, PAL_MFFD, PAL_MNXT, XXXXXXXX,
    PAL_RGBM, XXXXXXXX, PAL_DREC, PAL_DREC, PAL_DSTP, XXXXXXXX,                              XXXXXXXX, PAL_VOLU, PAL_MUTE, PAL_VOLD, XXXXXXXX, XXXXXXXX,
#if defined AUDIO_CLICKY && (defined MIDI_BASIC || defined MIDI_ADVANCED)
    PAL_Mus,  PAL_Mus,  PAL_Mus,  XXXXXXXX, XXXXXXXX,           PAL_RGBT,          PAL_LCTG,           XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, _lleave_,
#elif defined MIDI_BASIC || defined MIDI_ADVANCED
    PAL_Mus,  PAL_Mus,  XXXXXXXX, XXXXXXXX, XXXXXXXX,           PAL_RGBT,          PAL_LCTG,           XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, _lleave_,
#elif defined AUDIO_CLICKY
    PAL_Mus,  PAL_Mus,  XXXXXXXX, XXXXXXXX, XXXXXXXX,           PAL_RGBT,          PAL_LCTG,           XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, _lleave_,
#else
    PAL_Mus,  XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,           PAL_RGBT,          PAL_LCTG,           XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, _lleave_,
#endif
                                            PAL_FAST, PAL_SLD,  PAL_SLOW,          PAL_SLOW, PAL_DTTP, PAL_FAST
  ),
  [L_Music] = LEDMAP_moonlander(
    PAL_MUST, PAL_MUSM, PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,           PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,
    PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,           PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,
    PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,           PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,
    PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,                               PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,
    _lleave_, PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,            PAL_MUS,           PAL_MUS,            PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,  ________,
                                            PAL_MUS,  PAL_MUS,  PAL_MUS,           PAL_MUS,  PAL_MUS,  PAL_MUS
  ),
#if defined MIDI_BASIC || defined MIDI_ADVANCED
  [L_MIDI] = LEDMAP_moonlander(
    PAL_MUST, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, ________,          ________, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
    XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,          XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
    PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,  XXXXXXXX,          XXXXXXXX, PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,  PAL_MUS,
    XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,                              XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX,
    XXXXXXXX, _lleave_, XXXXXXXX, XXXXXXXX, XXXXXXXX,           XXXXXXXX,          XXXXXXXX,           XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, ________,
#    ifdef MIDI_ADVANCED
                                            PAL_NAV1, PAL_VOLU, PAL_NAV2,          PAL_NAV2, PAL_VOLD, PAL_NAV1
#    else
                                            XXXXXXXX, XXXXXXXX, XXXXXXXX,          XXXXXXXX, XXXXXXXX, XXXXXXXX
#    endif
  ),
#endif
  [L_DvorakRaw] = LEDMAP_moonlander(
    PAL_SYM,  PAL_DIG,  PAL_DIG,  PAL_DIG,  PAL_DIG,  PAL_DIG,  PAL_SYM,           PAL_SYM,  PAL_DIG,  PAL_DIG,  PAL_DIG,  PAL_DIG,  PAL_DIG,  PAL_RawO,
    PAL_TAB,  PAL_SYM,  PAL_SYM,  PAL_SYM,  PAL_DLTR, PAL_DLTR, PAL_ACC,           PAL_ACC,  PAL_DLTR, PAL_DLTR, PAL_DLTR, PAL_DLTR, PAL_DLTR, PAL_ESC,
    PAL_CAPS, PAL_DLTR, PAL_DLTR, PAL_DLTR, PAL_DLTR, PAL_DLTR, PAL_ACC,           PAL_SYM,  PAL_DLTR, PAL_DLTR, PAL_DLTR, PAL_DLTR, PAL_DLTR, PAL_ENT,
    PAL_MOD,  PAL_SYM,  PAL_DLTR, PAL_DLTR, PAL_DLTR, PAL_DLTR,                              PAL_DLTR, PAL_DLTR, PAL_DLTR, PAL_DLTR, PAL_DLTR, PAL_MOD,
    PAL_MOD,  PAL_MOD,  PAL_MOD,  PAL_SPC,  PAL_BSPC,           PAL_NAV2,          PAL_NAV1,           PAL_DEL,  PAL_MOD,  PAL_MOD,  PAL_APP,  PAL_MOD,
                                            PAL_NAV2, PAL_NAV2, PAL_NAV2,          PAL_NAV1, PAL_NAV1, PAL_NAV1
  ),
};

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

/* Added */
/* \brief Converts a modifier bitfield for use with MT, i.e. where the side
 *        of all modifiers, left or right, is represented with one bit, to
 *        a modifier bitfield where each modifier on each side gets its own
 *        bit, for use with get_mods() and related functions.
 * \param mods the 5-bit modifiers to convert
 * \return the modifiers in 'mods', converted into an 8-bit bitfield
 */
uint8_t mt_to_mod_bits(uint8_t mods) {
    uint8_t result = 0;
    if (mods & MOD_LSFT) {
        result |= (mods & MOD_RSFT) == MOD_RSFT ? MOD_BIT(KC_RSFT) : MOD_BIT(KC_LSFT);
    }
    if (mods & MOD_LCTL) {
        result |= (mods & MOD_RCTL) == MOD_RCTL ? MOD_BIT(KC_RCTL) : MOD_BIT(KC_LCTL);
    }
    if (mods & MOD_LALT) {
        result |= (mods & MOD_RALT) == MOD_RALT ? MOD_BIT(KC_RALT) : MOD_BIT(KC_LALT);
    }
    if (mods & MOD_LGUI) {
        result |= (mods & MOD_RGUI) == MOD_RGUI ? MOD_BIT(KC_RGUI) : MOD_BIT(KC_LGUI);
    }
    return result;
}

void set_layer_color(void) {
    layer_state_t state = layer_state | (default_layer_state ? default_layer_state : 1);
    uint8_t highest_layer = get_highest_layer(state);
    float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
    for (size_t map_row = 0; map_row < MATRIX_ROWS; map_row++) {
        for (size_t map_col = 0; map_col < MATRIX_COLS; map_col++) {
            /* Grab the index of the LED for this matrix position, if any. */
            uint8_t i = g_led_config.matrix_co[map_row][map_col];
            if (i == NO_LED) continue;
            /* Resolve the topmost active layer in which this key is lit
             * (Value > 0) or not KC_TRANSPARENT. */
            uint8_t active_layer = highest_layer;
            for (int j = highest_layer; j >= 0; j--) {
                if (layer_state_cmp(state, j)
                    && (pgm_read_word(&keymaps[j][map_row][map_col]) != KC_TRANSPARENT
                     || pgm_read_byte(&ledmaps[j][map_row][map_col]) != PAL_NONE)) {
                    active_layer = j;
                    break;
                }
            }
            uint8_t palette_entry = pgm_read_byte(&ledmaps[active_layer][map_row][map_col]);
            if (palette_entry == PAL_NONE) {
                rgb_matrix_set_color( i, 0, 0, 0 );
            } else {
                HSV hsv = {
                    .h = pgm_read_byte(&led_palette[palette_entry].h),
                    .s = pgm_read_byte(&led_palette[palette_entry].s),
                    .v = pgm_read_byte(&led_palette[palette_entry].v),
                };
                /* What kind of key is on the topmost active layer at this
                 * location? */
                uint16_t keycode = keymaps[active_layer][map_row][map_col];
                switch (keycode) {
                    case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
                        /* For Tap-Toggle layer keys, reduce the brightness of
                         * the glow if the layer isn't currently active. */
                        if (!layer_state_cmp(state, QK_LAYER_TAP_TOGGLE_GET_LAYER(keycode))) {
                            hsv.v = REDUCE_BRIGHTNESS(hsv.v);
                        }
                        break;
                    case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
                        /* For Layer Mod keys, reduce the brightness of
                         * the glow if the layer isn't currently active. */
                        if (!layer_state_cmp(state, QK_LAYER_MOD_GET_LAYER(keycode))) {
                            hsv.v = REDUCE_BRIGHTNESS(hsv.v);
                        }
                        break;
                    case QK_MOMENTARY ... QK_MOMENTARY_MAX:
                        /* For momentary layer keys, reduce the brightness of
                         * the glow if the layer isn't currently active. */
                        if (!layer_state_cmp(state, QK_MOMENTARY_GET_LAYER(keycode))) {
                            hsv.v = REDUCE_BRIGHTNESS(hsv.v);
                        }
                        break;
                    case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX: {
                        uint8_t key_oneshot_mods = mt_to_mod_bits(QK_ONE_SHOT_MOD_GET_MODS(keycode));
                        /* For one-shot modifier keys:
                         * a) Keep the brightness of the glow if all of the
                         *    modifiers it one-shots are currently locked. */
                        if ((get_oneshot_locked_mods() & key_oneshot_mods) == key_oneshot_mods) {
                        }
                        /* b) Keep the brightness of the glow and make it blink
                         *    if the modifiers are currently one-shot. */
                        else if ((get_oneshot_mods() & key_oneshot_mods) == key_oneshot_mods) {
                            hsv.v = BLINK_BRIGHTNESS(hsv.v);
                        }
                        /* c) Reduce the brightness of the glow if any of the
                         *    modifiers isn't currently active. */
                        else {
                            hsv.v = REDUCE_BRIGHTNESS(hsv.v);
                        }
                        break;
                    }
#if defined CAPS_WORD_ENABLE
                    case QK_CAPS_WORD_TOGGLE:
                        /* For Caps Word, reduce the brightness of the glow if
                         * Caps Word is off. */
                        if (!is_caps_word_on()) {
                            hsv.v = REDUCE_BRIGHTNESS(hsv.v);
                        }
                        break;
#endif
                    case MAGIC_TOGGLE_NKRO:
                        /* For NKRO, reduce the brightness of the glow if the
                         * key rollover is set to 6. */
                        if (!keymap_config.nkro) {
                            hsv.v = REDUCE_BRIGHTNESS(hsv.v);
                        }
                        break;
                    case KC_NUM_LOCK:
                        /* For Num Lock, reduce the brightness of the glow if
                         * Num Lock is off. */
                        if (!host_keyboard_led_state().num_lock) {
                            hsv.v = REDUCE_BRIGHTNESS(hsv.v);
                        }
                        break;
                    case KC_CAPS_LOCK:
                        /* For Caps Lock, reduce the brightness of the glow if
                         * Caps Lock is off. */
                        if (!host_keyboard_led_state().caps_lock) {
                            hsv.v = REDUCE_BRIGHTNESS(hsv.v);
                        }
                        break;
                    case KC_SCROLL_LOCK:
                        /* For Scroll Lock, reduce the brightness of the glow if
                         * Scroll Lock is off. */
                        if (!host_keyboard_led_state().scroll_lock) {
                            hsv.v = REDUCE_BRIGHTNESS(hsv.v);
                        }
                        break;
#if defined AUDIO_ENABLE
                    case MU_TOGG:
                        /* For Music Toggle, reduce the brightness of the glow
                         * if music is off. */
                        if (!is_music_on()) {
                            hsv.v = REDUCE_BRIGHTNESS(hsv.v);
                        }
                        break;
#endif /* AUDIO_ENABLE */
#if defined MIDI_BASIC || defined MIDI_ADVANCED
                    case MI_TOGG:
                        /* For MIDI Toggle, reduce the brightness of the glow
                         * if MIDI is off. */
                        if (!is_midi_on()) {
                            hsv.v = REDUCE_BRIGHTNESS(hsv.v);
                        }
                        break;
#endif /* defined MIDI_BASIC || defined MIDI_ADVANCED */
#if defined AUDIO_CLICKY
                    case CK_TOGG:
                        /* For Audio Clicky, reduce the brightness of the glow
                         * if Audio Clicky is off. */
                        if (!is_clicky_on()) {
                            hsv.v = REDUCE_BRIGHTNESS(hsv.v);
                        }
                        break;
#endif
                    /* Tap Dance keys implementing Toggle-Hold Mods. */
                    case TD_LSFT:
                    case TD_LCTL:
                    case TD_LALT:
                    case TD_LGUI: {
                        uint8_t key_toggle_hold_mods;
                        switch (keycode) {
                            case TD_LSFT:
                                key_toggle_hold_mods = MOD_BIT(KC_LSFT);
                                break;
                            case TD_LCTL:
                                key_toggle_hold_mods = MOD_BIT(KC_LCTL);
                                break;
                            case TD_LALT:
                                key_toggle_hold_mods = MOD_BIT(KC_LALT);
                                break;
                            case TD_LGUI:
                                key_toggle_hold_mods = MOD_BIT(KC_LGUI);
                                break;
                        }
                        /* a) Keep the brightness of the glow if all of the
                         *    modifiers it toggle-holds are currently locked
                         *    and make it blink. */
                        if ((toggle_hold_locked_mods & key_toggle_hold_mods) == key_toggle_hold_mods) {
                            hsv.v = BLINK_BRIGHTNESS(hsv.v);
                        }
                        /* b) Keep the brightness of the glow if all of the
                         *    modifiers it toggle-holds are currently held. */
                        else if ((toggle_hold_held_mods & key_toggle_hold_mods) == key_toggle_hold_mods) {
                        }
                        /* c) Reduce the brightness of the glow if any of the
                         *    modifiers it toggle-holds isn't currently active. */
                        else {
                            hsv.v = REDUCE_BRIGHTNESS(hsv.v);
                        }
                        break;
                    }
                    default:
                        break;
                }
                RGB rgb = hsv_to_rgb( hsv );
                rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
            }
        }
    }
}

bool rgb_matrix_indicators_user(void) {
    if (keyboard_config.disable_layer_led) { return false; }
    set_layer_color();
    return false;
}
