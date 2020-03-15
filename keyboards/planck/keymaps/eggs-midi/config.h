#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

/*
 * MIDI options
 */

/* Prevent use of disabled MIDI features in the keymap */
//#define MIDI_ENABLE_STRICT 1

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/
#define MIDI_BASIC

#undef TAPPING_TERM
#define TAPPING_TERM 190

/* prevent stuck modifiers */
#define USB_MAX_POWER_CONSUMPTION 50 //ipad compatibility
#define PREVENT_STUCK_MODIFIERS

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
#define MUSIC_MASK (keycode != KC_NO)
#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 3

#endif
