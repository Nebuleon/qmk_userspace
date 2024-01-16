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

static_assert(GENERATE_TAP_DANCES_TAP_HOLD(LENGTH_TAP_HOLD) <= UINT8_MAX + 1, "Number of tap dances must fit within a byte");

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

const tap_dance_tap_hold_t PROGMEM tap_hold_data[] = {
    GENERATE_TAP_DANCES_TAP_HOLD(DATA_TAP_HOLD)
};

tap_dance_action_t tap_dance_actions[] = {
    GENERATE_TAP_DANCES_TAP_HOLD(ACTION_TAP_HOLD)
    [DN_LOCK] = { .fn = { clear_lock_press, NULL, clear_lock_reset } },
};
