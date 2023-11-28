#pragma once

// clang-format off
#define LEDMAP_moonlander( \
    k00, k01, k02, k03, k04, k05, k06,   k60, k61, k62, k63, k64, k65, k66, \
    k10, k11, k12, k13, k14, k15, k16,   k70, k71, k72, k73, k74, k75, k76, \
    k20, k21, k22, k23, k24, k25, k26,   k80, k81, k82, k83, k84, k85, k86, \
    k30, k31, k32, k33, k34, k35,             k91, k92, k93, k94, k95, k96, \
    k40, k41, k42, k43, k44,      k53,   kb3,      ka2, ka3, ka4, ka5, ka6, \
                        k50, k51, k52,   kb4, kb5, kb6 \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06 }, \
    { k10, k11, k12, k13, k14, k15, k16 }, \
    { k20, k21, k22, k23, k24, k25, k26 }, \
    { k30, k31, k32, k33, k34, k35, PAL_NONE }, \
    { k40, k41, k42, k43, k44, PAL_NONE, PAL_NONE }, \
    { k50, k51, k52, k53, PAL_NONE, PAL_NONE, PAL_NONE }, \
\
    { k60, k61, k62, k63, k64, k65, k66 }, \
    { k70, k71, k72, k73, k74, k75, k76 }, \
    { k80, k81, k82, k83, k84, k85, k86 }, \
    { PAL_NONE, k91, k92, k93, k94, k95, k96 }, \
    { PAL_NONE, PAL_NONE, ka2, ka3, ka4, ka5, ka6 }, \
    { PAL_NONE, PAL_NONE, PAL_NONE, kb3, kb4, kb5, kb6 } \
}
// clang-format on

#undef ________
#define ________ PAL_NONE
#undef XXXXXXXX
#define XXXXXXXX PAL_NONE
#define _lleave_ PAL_NONE  /* denotes a key that must be unlit because it denotes that a layer is active and the color is set on the layer-entering key */



enum palette {
    PAL_NONE,
    PAL_QLTR,
    PAL_DLTR,
    PAL_DIG,
    PAL_DIGF,
    PAL_FN,
    PAL_SYM,
    PAL_ACC,
    PAL_BSPC,
    PAL_DEL,
    PAL_ESC,
    PAL_ENT,
    PAL_TAB,
    PAL_SPC,
    PAL_MOD,
    PAL_PSCR,
    PAL_LOCK,
    PAL_CAPS,
    PAL_NAV1,
    PAL_NAV2,
    PAL_MOV1,
    PAL_MOVW,
    PAL_MOVL,
    PAL_MOVE,
    PAL_SEL1,
    PAL_SELW,
    PAL_SELL,
    PAL_SELE,
    PAL_BSP1,
    PAL_BSPW,
    PAL_DEL1,
    PAL_DELW,
    PAL_SELA,
    PAL_CUT,
    PAL_COPY,
    PAL_PSTE,
    PAL_TERM,
    PAL_SHDE,
    PAL_MIN,
    PAL_MAX,
    PAL_CLSE,
    PAL_TILE,
    PAL_SCRN,
    PAL_WNDW,
    PAL_WSSW,
    PAL_WSMO,
    PAL_SPLT,
    PAL_JOIN,
    PAL_SEG,
    PAL_COMM,
    PAL_TMTB,
    PAL_TABS,
    PAL_FLTR,
    PAL_SINS,
    PAL_SUP,
    PAL_SUB,
    PAL_MBTN,
    PAL_MMOV,
    PAL_MWHL,
    PAL_ZIN,
    PAL_ZOUT,
    PAL_ZRST,
    PAL_RFSH,
    PAL_WEBN,
    PAL_BOOT,
    PAL_CLR,
    PAL_RGBM,
    PAL_DREC,
    PAL_DPLY,
    PAL_DSTP,
    PAL_SAI,
    PAL_SAD,
    PAL_VAI,
    PAL_VAD,
    PAL_HUI,
    PAL_HUD,
    PAL_RGBT,
    PAL_SLD,
    PAL_SLOW,
    PAL_FAST,
    PAL_LCTG,
    PAL_ILTG,
    PAL_NKRO,
    PAL_DTTP,
    PAL_MPRV,
    PAL_MRWD,
    PAL_MPLY,
    PAL_MFFD,
    PAL_MNXT,
    PAL_VOLU,
    PAL_VOLD,
    PAL_MUTE,
    PAL_MUST,
    PAL_MUSM,
    PAL_MUS,
    PAL_APP,

    PAL_QWER,
    PAL_Dvor,
    PAL_Accs,
    PAL_Move,
    PAL_Syms,
    PAL_Phrs,
    PAL_Nums,
    PAL_FnMs,
    PAL_Web,
    PAL_RGBC,
    PAL_Mus,
    PAL_RawI,
    PAL_RawO,
    PAL_UNKN,
};
