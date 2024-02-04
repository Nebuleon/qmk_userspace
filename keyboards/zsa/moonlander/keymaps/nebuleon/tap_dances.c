#include "common.h"

typedef struct {
    uint16_t kc_held;
} tap;

#define DATA_TAP_HOLD(dance_name, kc_tap, kc_hold) { DN##dance_name, (kc_tap), (kc_hold) },

#define ACTION_TAP_HOLD(dance_name, kc_tap, kc_hold) \
     [DN##dance_name] = { .fn = { tapdance_lowlatency_press, tapdance_lowlatency_finished, tapdance_lowlatency_reset, tapdance_lowlatency_release }, .user_data = (void *) &tap_hold_data[DN##dance_name], },

#define LENGTH_TAP_HOLD(dance_name, kc_tap, kc_hold) + 1

typedef struct {
    uint16_t dance_index; /* Index of this dance's tap state in 'dance_state' */
    uint16_t kc_tap; /* Keycode to be sent on a single tap */
    uint16_t kc_hold; /* Keycode to be sent on a held key */
} tap_dance_tap_hold_t;

static tap dance_state[GENERATE_TAP_DANCES_TAP_HOLD(LENGTH_TAP_HOLD)];

void tapdance_lowlatency_press(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *dance_data = (tap_dance_tap_hold_t *) user_data;
    uint16_t dance_index = pgm_read_word(&dance_data->dance_index);
    uint16_t kc_tap = pgm_read_word(&dance_data->kc_tap);

    if (state->count > 1
#ifndef PERMISSIVE_HOLD
        && !state->interrupted
#endif
    ) {
        dance_state[dance_index].kc_held = kc_tap;
        register_code16(kc_tap);
    }
}

void tapdance_lowlatency_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *dance_data = (tap_dance_tap_hold_t *) user_data;
    uint16_t kc_tap = pgm_read_word(&dance_data->kc_tap);
    uint16_t kc_hold = pgm_read_word(&dance_data->kc_hold);
    uint16_t dance_index = pgm_read_word(&dance_data->dance_index);

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            dance_state[dance_index].kc_held = kc_hold;
            register_code16(kc_hold);
        } else if (!dance_state[dance_index].kc_held) {
            dance_state[dance_index].kc_held = kc_tap;
            register_code16(kc_tap);
        }
    }
}

void tapdance_lowlatency_release(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *dance_data = (tap_dance_tap_hold_t *) user_data;
    uint16_t kc_tap = pgm_read_word(&dance_data->kc_tap);

    if (!state->finished && (state->count == 1
#ifndef PERMISSIVE_HOLD
        || (state->count > 1 && state->interrupted)
#endif
        )) {
        add_weak_mods(state->weak_mods);
#ifndef NO_ACTION_ONESHOT
        add_mods(state->oneshot_mods);
#endif
        send_keyboard_report();
        tap_code16(kc_tap);
    }
}

void tapdance_lowlatency_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *dance_data = (tap_dance_tap_hold_t *) user_data;
    uint16_t dance_index = pgm_read_word(&dance_data->dance_index);
    uint16_t kc_held = dance_state[dance_index].kc_held;

    if (kc_held) {
        dance_state[dance_index].kc_held = 0;
        unregister_code16(kc_held);
    }
}

void clear_lock_press(tap_dance_state_t *state, void *user_data) {
    /* Disable every non-default layer, provided that a default layer is
     * selected. */
    if (default_layer_state != 0) {
        layer_state_set(0);
    } else {
        layer_state_set((layer_state_t)1 << L_DvorakLX);
    }

    if (state->count > 1) {
        register_code16(LGUI(FR_L));

        if (!keyboard_config.disable_layer_led) {
            keyboard_config.disable_layer_led = 1;
            rgb_matrix_set_color_all(0, 0, 0);
            eeconfig_update_kb(keyboard_config.raw);
        }
    }
} 

void clear_lock_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count > 1) {
        unregister_code16(LGUI(FR_L));
    }
}

/* - - - TAP-TOGGLE MODS IMPLEMENTATION - - - */

typedef struct {
    uint8_t mods; /* Modifiers to be toggled by this dance */
} tap_dance_toggle_hold_mod_t;

uint8_t toggle_hold_held_mods;
uint8_t toggle_hold_locked_mods;

void toggle_hold_mod_press(tap_dance_state_t *state, void *user_data) {
    tap_dance_toggle_hold_mod_t *dance_data = (tap_dance_toggle_hold_mod_t *) user_data;
    uint8_t mods = mt_to_mod_bits(pgm_read_byte(&dance_data->mods));

    bool are_locked = (toggle_hold_locked_mods & mods) == mods;

    toggle_hold_held_mods |= mods;
    if (!are_locked) {
        register_mods(mods);
    }
}

void toggle_hold_mod_release(tap_dance_state_t *state, void *user_data) {
    tap_dance_toggle_hold_mod_t *dance_data = (tap_dance_toggle_hold_mod_t *) user_data;
    uint8_t mods = mt_to_mod_bits(pgm_read_byte(&dance_data->mods));

    bool are_locked = (toggle_hold_locked_mods & mods) == mods;

    toggle_hold_held_mods &= ~mods;

    /* As of when a tap dance starts, the weak mods are preserved but unapplied.
     * Apply them here, otherwise we will send a report with modifiers released.
     */
    add_weak_mods(state->weak_mods);
#ifndef NO_ACTION_ONESHOT
    add_mods(state->oneshot_mods);
#endif

    if (state->interrupted || state->finished) {
        /* If the toggle-mod key was either pressed along with another key or
         * held for longer than the tapping term, do not toggle locking, but
         * instead release the modifiers at the host if they are not locked. */
        if (!are_locked) {
            unregister_mods(mods);
        }
    } else {
        /* If the toggle-mod key was tapped, toggle locking. */
        if (are_locked) {
            toggle_hold_locked_mods &= ~mods;
            unregister_mods(mods);
        } else {
            toggle_hold_locked_mods |= mods;
        }
    }
}

#define DATA_TOGGLE_HOLD_MOD(dance_name, mods) { (mods) },

#define ACTION_TOGGLE_HOLD_MOD(dance_name, mods) \
     [DN##dance_name] = { .fn = { toggle_hold_mod_press, NULL, NULL, toggle_hold_mod_release }, .user_data = (void *) &toggle_hold_mod_data[DN##dance_name - (GENERATE_TAP_DANCES_TAP_HOLD(LENGTH_TAP_HOLD))], },

#define LENGTH_TOGGLE_HOLD_MOD(dance_name, mods) + 1

const tap_dance_toggle_hold_mod_t PROGMEM toggle_hold_mod_data[] = {
    GENERATE_TAP_DANCES_TOGGLE_HOLD_MOD(DATA_TOGGLE_HOLD_MOD)
};

/* - - - END TAP-TOGGLE MODS IMPLEMENTATION - - - */

static_assert(GENERATE_TAP_DANCES_TAP_HOLD(LENGTH_TAP_HOLD) + GENERATE_TAP_DANCES_TOGGLE_HOLD_MOD(LENGTH_TOGGLE_HOLD_MOD) + 1 /* the Lock dance */ <= UINT8_MAX + 1, "Number of tap dances must fit within a byte");

const tap_dance_tap_hold_t PROGMEM tap_hold_data[] = {
    GENERATE_TAP_DANCES_TAP_HOLD(DATA_TAP_HOLD)
};

tap_dance_action_t tap_dance_actions[] = {
    GENERATE_TAP_DANCES_TAP_HOLD(ACTION_TAP_HOLD)
    GENERATE_TAP_DANCES_TOGGLE_HOLD_MOD(ACTION_TOGGLE_HOLD_MOD)
    [DN_LOCK] = { .fn = { clear_lock_press, NULL, clear_lock_reset } },
};
