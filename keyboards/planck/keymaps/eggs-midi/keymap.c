
//#pragma message "You may need to add LAYOUT_planck_grid to your keymap layers - see default for an example"
#include "planck.h"
//#include "action_layer.h"
//#ifdef AUDIO_ENABLE
//  #include "audio.h"
//#endif
#include "eeconfig.h"

//#include QMK_KEYBOARD_H //<-- is this needed?

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _MIDI 0


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* MIDI
 * ,-----------------------------------------------------------------------------.
 * | C4  | C#4 | D4  | D#4 | E4  | E#4 | F4  | F#4 | G4  | G#4 | A4  | A#4 | B4  |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * | C3  | C#3 | D3  | D#3 | E3  | E#3 | F3  | F#3 | G3  | G#3 | A3  | A#3 | B3  |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * | C2  | C#2 | D2  | D#2 | E2  | E#2 | F2  | F#2 | G2  | G#2 | A2  | A#2 | B2  |
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * | C1  | C#1 | D1  | D#1 | E1  | E#1 | F1  | F#1 | G1  | G#1 | A1  | A#1 | B1  |
 * `-----------------------------------------------------------------------------'
 */


[_MIDI] = {
  {MI_C_4, MI_Cs_4, MI_D_4, MI_Ds_4, MI_E_4, MI_F_4, MI_Fs_4, MI_G_4, MI_Gs_4, MI_A_4, MI_As_4, MI_B_4},
  {MI_C_3, MI_Cs_3, MI_D_3, MI_Ds_3, MI_E_3, MI_F_3, MI_Fs_3, MI_G_3, MI_Gs_3, MI_A_3, MI_As_3, MI_B_3},
  {MI_C_2, MI_Cs_2, MI_D_2, MI_Ds_2, MI_E_2, MI_F_2, MI_Fs_2, MI_G_2, MI_Gs_2, MI_A_2, MI_As_2, MI_B_2},
  {MI_C_1, MI_Cs_1, MI_D_1, MI_Ds_1, MI_E_1, MI_F_1, MI_Fs_1, MI_G_1, MI_Gs_1, MI_A_1, MI_As_1, MI_B_1}
}


};

#ifdef AUDIO_ENABLE
float tone_startup[][2]    = SONG(STARTUP_SOUND);
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);

float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
#endif


void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}



void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
}

#ifdef AUDIO_ENABLE
void startup_user(){
    _delay_ms(20); // gets rid of tick
    PLAY_SONG(tone_startup);
}

void shutdown_user(){
    PLAY_SONG(tone_goodbye);
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void){
    music_scale_user();
}

void music_scale_user(void){
    PLAY_SONG(music_scale);
}
#endif
