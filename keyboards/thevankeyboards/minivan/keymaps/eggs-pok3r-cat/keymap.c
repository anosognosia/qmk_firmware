#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _TOUCHCURSOR 3
#define _MOUSECURSOR 4
#define _ADJUST 16

// Keycodes
enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_ALT_TAB,
  KC_CMD_TAB,
  KC_CTL_TAB,
  KC_CMD_SLSH,
  KC_AG_FIND,
  KC_AG_AGAIN,
  KC_AG_UNDO,
  KC_AG_CUT,
  KC_AG_COPY,
  KC_AG_PASTE,
  KC_AG_DESK_L,
  KC_AG_DESK_R,
  KC_AG_TAB_C,
  KC_AG_TAB_N,
  KC_AG_TAB_R,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Custom macros
#define CTL_ESC     CTL_T(KC_ESC)               // Tap for Esc, hold for Ctrl
#define SFT_ENT     SFT_T(KC_ENT)               // Tap for Enter, hold for Shift
#define HPR_TAB     ALL_T(KC_TAB)               // Tap for Tab, hold for Hyper
#define GUI_SEM     GUI_T(KC_SCLN)              // Tap for Semicolon, hold for GUI
#define ALT_QUO     ALT_T(KC_QUOT)              // Tap for Quote, hold for Alt
// Requires KC_TRNS/_______ for the trigger key in the destination layer
#define LT_TC       LT(_TOUCHCURSOR, KC_SPC)    // L-ayer T-ap T-ouch C-ursor  -  SPACE
#define LT_TCE      LT(_TOUCHCURSOR, KC_ENT)    // L-ayer T-ap T-ouch C-ursor  -  ENTER
#define LT_MC(kc)   LT(_MOUSECURSOR, kc)        // L-ayer T-ap M-ouse C-ursor
#define ALT_TAB     M(KC_ALT_TAB)               // Macro for Alt-Tab
#define CMD_TAB     M(KC_CMD_TAB)               // Macro for Cmd-Tab
#define CTL_TAB     M(KC_CTL_TAB)               // Macro for Ctl-Tab
#define CMD_SLSH    M(KC_CMD_SLSH)              // Macro for Cmd-Slash (personal shortcut to toggle iTerm2 visibility)
#define AG_FIND     M(KC_AG_FIND)               // Macros for Cmd-[x] vs Ctrl-[x] based on current AG_NORM or AG_SWAP settings
#define AG_AGAIN    M(KC_AG_AGAIN)
#define AG_UNDO     M(KC_AG_UNDO)
#define AG_CUT      M(KC_AG_CUT)
#define AG_COPY     M(KC_AG_COPY)
#define AG_PASTE    M(KC_AG_PASTE)
#define AG_D_L      M(KC_AG_DESK_L)             // For Virtual Desktop Switching: Left, and
#define AG_D_R      M(KC_AG_DESK_R)             //                                Right
#define AG_T_C      M(KC_AG_TAB_C)              // For Chrome, etc. Tab Close,
#define AG_T_N      M(KC_AG_TAB_N)              //                  Tab New, and
#define AG_T_R      M(KC_AG_TAB_R)              //                  Tab Reopen Closed

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 /*
 *
 * Qwerty EDGAR Pok3r Catalyst
 *   add hyper on tab again
 * ,---------+------+------+------+------+------+------+------+------+------+------+-----------.
 * |   Tab   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   Bksp    |  Hyper
 * |---------`------`------`------`------`------`------`------`------`------`------`-----------|
 * |   MC/Esc |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |  ;   |   "      |
 * |----------`------`------`------`------`------`------`------`------`------`------`----------|
 * |   Shift   |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Sft/Ent |
 * |-----------`------`------`------`------`-----'-------`------`------`------`------`---------|
 * |   Ctrl  |   Alt   |   GUI   |   Lower/Space  |   Raise/Enter  |   TC    | GUI | ALT | CTRL|
 *  `--------+---------+---------+------^^^-------+-----^^^--------+---------+-----+-----+-----'
 * HPR_TAB KC_TAB
 */

    [_QWERTY] = LAYOUT_arrow(
        /*,--------+-------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------.*/
        HPR_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        /*|--------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`-----------------|*/
        LT_MC(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCOLON, KC_QUOT,
        /*|---------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`----------------|*/
        KC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC,
        /*|----------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`---------------|*/
        KC_LCTRL, KC_LALT,  KC_LGUI, LT(_LOWER, KC_SPACE), LT(_RAISE, KC_ENTER), MO(_TOUCHCURSOR), KC_RGUI, KC_RALT, KC_RCTRL),
    /*`-----------+---------------+---------+-------^^^------+-------^^^-------+---------+-----------------+--------------'*/


    /* Lower
 * ,---------+------+------+------+------+------+------+------+------+------+------+-------------.
 * |   ~     |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |   Bksp      |
 * |---------`------`------`------`------`------`------`------`------`------`------`-------------|
 * |   [      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |   "|"      |
 * |----------`------`------`------`------`------`------`------`------`------`------`------------|
 * |   ]       |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |   -  |   =  |   [  |   ]  |    \      |
 * |-----------`------`------`------`------`-----'-------`------`------`------`------`-----------|
 * |         |         |         |                |                |         |         |         |
 *  `--------+---------+---------+------^^^-------+-----^^^--------+---------+---------+---------'
 */
    [_LOWER] = LAYOUT_arrow(
        /*,--------+-------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------.*/
        KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
        /*|--------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`-----------------|*/
        KC_LBRC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
        /*|---------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`----------------|*/
        KC_RBRC, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_MINS, KC_EQL, KC_LBRC, KC_UP, KC_BSLS,
        /*|----------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`---------------|*/
        _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT),
    /*`-----------+---------------+---------+-------^^^------+-------^^^-------+---------+-----------------+--------------'*/

    /* Raise
 * ,------+------+------+------+------+------+------+------+------+------+------+--------.
 * |   0  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  Bksp  |
 * |------`------`------`------`------`------`------`------`------`------`------`--------|
 * |   $   |   4  |   5  |   6  |   .  |   +  |   .  |   4  |   5  |   6  |   *  |  "|"  |
 * |-------`------`------`------`------`------`------`------`------`------`------`-------|
 * |   =    |   7  |   8  |   9  |   0  |   -  |   .  |   1  |   2  |   3  |  A   |  \   |
 * |--------`------`------`------`------`------'------`------`------`------`------`------|
 * |      |         |       |                |               |  TC   |  <   |  V  |   >  |
 *  `-----+---------+-------+------^^^-------+-----^^^-------+-------+------+-----+------'
 */
    [_RAISE] = LAYOUT_arrow(
        /*,--------+-------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------.*/
        KC_0, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
        /*|--------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`-----------------|*/
        KC_DLR, KC_4, KC_5, KC_6, KC_DOT, KC_PLUS, KC_DOT, KC_4, KC_5, KC_6, KC_ASTR, KC_PIPE,
        /*|---------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`----------------|*/
        KC_EQL, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_DOT, KC_1, KC_2, KC_3, KC_UP, KC_BSLS,
        /*|----------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`---------------|*/
        _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT),
    /*`-----------+---------------+---------+-------^^^------+-------^^^-------+---------+-----------------+--------------'*/




    /* TouchCursor layer (http://martin-stone.github.io/touchcursor/) plus personal customizations
 * ,---------+------+------+------+------+------+------+------+------+------+------+------------.
 * |         |      |      |      |      |      |Insert| Home |  Up  | End  | Bksp |            |
 * |---------`------`------`------`------`------`------`------`------`------`------`------------|
 * |          |     |      |      |      |      | PgUp | Left | Down |Right |Desk_L|  Desk_R    |
 * |----------`------`------`------`------`------`------`------`------`------`------`-----------|
 * |           |     |      |      |      |      | PgDn | Del  |Tab_N |Tab_R |   A  |           |
 * |-----------`------`------`------`------`-----'-------`------`------`------`------`----------|
 * | RGB TOG | RGB MOD | RGB RST |                |                |       |  <   |   V  |   >  |
 *  `--------+---------+---------+------^^^-------+-----^^^--------+-------+------+------+------'
 */
    [_TOUCHCURSOR] = LAYOUT_arrow(
        /*,--------+-------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------.*/
        _______, _______, _______, _______, _______, _______, KC_INS, KC_HOME, KC_UP, KC_END, KC_BSPC, _______,
        /*|--------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`-----------------|*/
        _______, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX, KC_PGUP, KC_LEFT, KC_DOWN, KC_RGHT, AG_D_L, AG_D_R,
        /*|---------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`----------------|*/
        RGBRST, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, KC_PGDN, KC_DEL, AG_T_N, AG_T_R, KC_UP, _______,
        /*|----------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`---------------|*/
        RGB_TOG, RGB_MOD, RGB_RMOD, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT),
    /*`-----------+---------------+---------+-------^^^------+-------^^^-------+---------+-----------------+--------------'*/


    /* Mousecursor Layer + Pok3r Media
 * ,---------+------+------+------+------+------+------+------+------+------+------+------------.
 * |         | RRWD | PLAY | FFWD |ACCL0 |ACCL1 |ACCL2 | BTN1 |  Up  | BTN2 | WH L |    WH R    | KC_LOCK
 * |---------`------`------`------`------`------`------`------`------`------`------`------------|
 * |          |      | VOL+ | VOL- | MUTE |      |WHL_Up| Left | Down |Right | BTN4 |   BTN5    |
 * |----------`------`------`------`------`------`------`------`------`------`------`-----------|
 * |           |      |      |      | BTN3 |      |WHL_Dn| BTN1 |      |      |   A  |          |
 * |-----------`------`------`------`------`-----'-------`------`------`------`------`----------|
 * | MAC SCN |         |         |                |               |     | <   |   V   |    >    |
 *  `--------+---------+---------+------^^^-------+-----^^^-------+-----+-----+-------+---------'
 */

    [_MOUSECURSOR] = LAYOUT_arrow(
        /*,--------+-------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------.*/
        _______, KC_MRWD, KC_MPLY, KC_MFFD, KC_ACL0, KC_ACL1, KC_ACL2, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_L, KC_WH_R, //KC_MNXT KC_MPRV
        /*|--------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`-----------------|*/
        _______, _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN4, KC_BTN5,
        /*|---------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`----------------|*/
        _______, _______, _______, _______, _______, _______, KC_WH_D, KC_BTN1, KC_WH_L, KC_WH_R, KC_UP, KC_BTN3,
        /*|----------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`---------------|*/
        LGUI(S(KC_4)), _______, _______,       _______,       _______,        _______,   KC_LEFT, KC_DOWN, KC_RIGHT),
    /*`-----------+---------------+---------+-------^^^------+-------^^^-------+---------+-----------------+--------------'*/


    /* Adjust (Lower + Raise)
 * ,---------+------+------+------+------+------+------+------+------+------+------+-------------.
 * |         |      |      |      |      |      |      |      |      |      |      |    Del      |
 * |---------`------`------`------`------`------`------`------`------`------`------`-------------|
 * |          |      |      |      |      |AGnorm|AGswap|Qwerty|      |      |      |            |
 * |----------`------`------`------`------`------`------`------`------`------`------`------------|
 * |           |      |      |      |      |     |       |      |      |      |      |           |
 * |-----------`------`------`------`------`-----'-------`------`------`------`------`-----------|
 * |         |         |         |                |                |         |         |  Reset  |
 *  `--------+---------+---------+------^^^-------+-----^^^--------+---------+---------+---------'
 */
    [_ADJUST] = LAYOUT_arrow(
        /*,--------+-------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------.*/
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
        /*|--------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`-----------------|*/
        _______, _______, _______, _______, _______, AG_NORM, AG_SWAP, QWERTY, _______, _______, _______, _______,
        /*|---------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`----------------|*/
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        /*|----------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`---------------|*/
        _______, _______, _______, _______, _______, _______, _______, _______,                             RESET)
    /*`-----------+---------------+---------+-------^^^------+-------^^^-------+---------+-----------------+--------------'*/
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

int backlightOn = 0;
int RGB_current_mode;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // Backlight.
  if (record->event.pressed && keycode == BL_TOGG)
  {
    // Set B2 to output.
    DDRB |= (1 << 2);

    // Toggle backlight variable.
    if (backlightOn == !backlightOn){
      // Turn backlight on.
      PORTB |= (1 << 2);
    } else {
      // Turn backlight off.
      PORTB &= ~(1 << 2);
    }

    // Disable the actual keycode.
    return false;
  }
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
      #ifdef RGBLIGHT_ENABLE
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
      case RGB_MOD:
          if (record->event.pressed) {
            rgblight_mode(RGB_current_mode);
            rgblight_step();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
      case RGBRST:
          if (record->event.pressed) {
            eeconfig_update_rgblight_default();
            rgblight_enable();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
    #endif
  }
  return true;
}




void matrix_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
  #endif
}

/*
 * Macro definition
 */
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    if (!eeconfig_is_enabled()) {
      eeconfig_init();
    }

    bool use_cmd = true;    // Use, for example, Cmd-Tab, Cmd-C, Cmd-V, etc.
    // Compare to MAGIC_SWAP_ALT_GUI and MAGIC_UNSWAP_ALT_GUI configs, set in:
    // quantum/quantum.c
    if(keymap_config.swap_lalt_lgui == 1 && keymap_config.swap_ralt_rgui == 1) {
      use_cmd = false;      // ... or, Alt-Tab, Ctrl-C, Ctrl-V, etc.
    }

    switch (id) {
      case KC_ALT_TAB:
        if(use_cmd) { return (record->event.pressed ? MACRO( D(LALT),  D(TAB), END ) : MACRO( U(TAB), END )); }
        else        { return (record->event.pressed ? MACRO( D(LGUI),  D(TAB), END ) : MACRO( U(TAB), END )); }
      case KC_CMD_TAB:
        if(use_cmd) { return (record->event.pressed ? MACRO( D(LGUI),  D(TAB), END ) : MACRO( U(TAB), END )); }
        else        { return (record->event.pressed ? MACRO( D(LALT),  D(TAB), END ) : MACRO( U(TAB), END )); }

      case KC_CTL_TAB:
        return (record->event.pressed ? MACRO( D(LCTRL), D(TAB), END ) : MACRO( U(TAB), END ));
      case KC_CMD_SLSH:
        return (record->event.pressed ? MACRO( D(LGUI),  D(SLSH),END ) : MACRO( U(SLSH),END ));

      case KC_AG_FIND:
        return use_cmd ? MACRODOWN( D(LGUI), T(F), END ) : MACRODOWN( D(LCTRL), T(F), END );
      case KC_AG_AGAIN:
        return use_cmd ? MACRODOWN( D(LGUI), T(G), END ) : MACRODOWN( D(LCTRL), T(G), END );
      case KC_AG_UNDO:
        return use_cmd ? MACRODOWN( D(LGUI), T(Z), END ) : MACRODOWN( D(LCTRL), T(Z), END );
      case KC_AG_CUT:
        return use_cmd ? MACRODOWN( D(LGUI), T(X), END ) : MACRODOWN( D(LCTRL), T(X), END );
      case KC_AG_COPY:
        return use_cmd ? MACRODOWN( D(LGUI), T(C), END ) : MACRODOWN( D(LCTRL), T(C), END );
      case KC_AG_PASTE:
        return use_cmd ? MACRODOWN( D(LGUI), T(V), END ) : MACRODOWN( D(LCTRL), T(V), END );

      case KC_AG_DESK_L:
        return use_cmd ? MACRODOWN( D(LGUI), D(LCTRL), T(SCLN), END ) : MACRODOWN( D(LALT), D(LCTRL), T(SCLN), END );
      case KC_AG_DESK_R:
        return use_cmd ? MACRODOWN( D(LGUI), D(LCTRL), T(QUOT), END ) : MACRODOWN( D(LALT), D(LCTRL), T(QUOT), END );

      case KC_AG_TAB_C:
        return use_cmd ? MACRODOWN( D(LGUI),            T(W), END ) : MACRODOWN( D(LCTRL),            T(W), END );
      case KC_AG_TAB_N:
        return use_cmd ? MACRODOWN( D(LGUI),            T(T), END ) : MACRODOWN( D(LCTRL),            T(T), END );
      case KC_AG_TAB_R:
        return use_cmd ? MACRODOWN( D(LGUI), D(LSHIFT), T(T), END ) : MACRODOWN( D(LCTRL), D(LSHIFT), T(T), END );
    }

    return MACRO_NONE;
}

