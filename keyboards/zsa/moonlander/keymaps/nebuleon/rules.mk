# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
DYNAMIC_MACRO_ENABLE = yes
TAP_DANCE_ENABLE = yes
SPACE_CADET_ENABLE = no
MIDI_ENABLE = yes
DYNAMIC_TAPPING_TERM_ENABLE = yes
SRC += rgb.c
INTROSPECTION_KEYMAP_C = tap_dances.c
LTO_ENABLE = yes
ifeq ($(AUDIO_DRIVER), dac_additive)
	SRC += audio_custom.c
endif
