#include "audio.h"

static dacsample_t square_wave[2] = {
    AUDIO_DAC_OFF_VALUE,
    AUDIO_DAC_OFF_VALUE + (AUDIO_DAC_SAMPLE_MAX - AUDIO_DAC_OFF_VALUE) / 4
};

float wavetable_indices[AUDIO_MAX_SIMULTANEOUS_TONES];

/**
 * Generation of the waveform being passed to the callback.
 */
uint16_t dac_value_generate(void) {
    size_t n_tones = audio_get_number_of_active_tones();
    if (n_tones == 0) {
        return AUDIO_DAC_OFF_VALUE;
    }

    uint32_t value = 0;

    for (size_t i = 0; i < n_tones; i++) {
        float new_wavetable_index = wavetable_indices[i];
        new_wavetable_index += audio_get_frequency(i) * ((float)(sizeof(square_wave) / sizeof(square_wave[0])) / AUDIO_DAC_SAMPLE_RATE * 2.0f / 3.0f);
        /* Note: the 2/3 are necessary to get the correct frequencies on the
         *       DAC output (as measured with an oscilloscope), since the gpt
         *       timer runs with 3*AUDIO_DAC_SAMPLE_RATE; and the DAC callback
         *       is called twice per conversion.*/

        while (new_wavetable_index >= sizeof(square_wave) / sizeof(square_wave[0]))
            new_wavetable_index -= sizeof(square_wave) / sizeof(square_wave[0]);

        value += square_wave[(size_t)new_wavetable_index];
        wavetable_indices[i] = new_wavetable_index;
    }

    return value / n_tones;
}