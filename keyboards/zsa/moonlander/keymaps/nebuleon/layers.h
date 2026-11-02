#pragma once

enum layers {
    L_DvorakBLX,        /* constraints: must be below L_Control */
    L_Control,          /* constraints: must be above the highest layout layer */
    L_MoveSelect,       /* constraints: must be above the highest layout layer and L_Control */
    L_WindowsTerminals, /* constraints: must be above the highest layout layer, L_MoveSelect and L_Control; must be within layers 0..15 */
    L_DvorakAccents,    /* constraints: must be above L_DvorakBLX and L_Control */
    L_Symbols,          /* constraints: must be above the highest layout layer, L_MoveSelect and L_Control */
    L_Numbers,          /* constraints: must be above the highest layout layer, L_MoveSelect and L_Control */
    L_FnMouse,          /* constraints: must be above the highest layout layer, L_Numbers, L_MoveSelect and L_Control */
    L_Web,              /* constraints: must be above the highest layout layer, L_MoveSelect and L_Control */
    L_RGBControl,       /* constraints: must be above the highest layout layer */
    L_Music,            /* constraints: must be above L_RGBControl */
#if defined MIDI_BASIC || defined MIDI_ADVANCED
    L_MIDI,             /* constraints: must be above L_RGBControl */
#endif
    L_DvorakRaw,
};
