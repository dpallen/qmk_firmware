#include "preonic.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "led.h"

#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _GAME 1
#define _ARROW 2
#define _NUMPAD 3
#define _LOWER 4
#define _RAISE 5
#define _ADJUST 6

enum preonic_keycodes {
  QWERTY = SAFE_RANGE, 
  GAME,
  ARROW,
  NUMPAD,
  LOWER,
  RAISE
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |  Esc |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    | Raise|   -  |  =  |   [   |   ]  |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                KC_6,    KC_7,    KC_8,     KC_9,     KC_0,     KC_BSPC},
  {KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,     KC_DEL},
  {RAISE, KC_A,    KC_S,    KC_D,    KC_F,                KC_G,    KC_H,    KC_J,     KC_K,     KC_L,     KC_SCLN, KC_QUOT},
  {KC_LCTL,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  SFT_T(KC_ENT)},
  {KC_LSFT,  XXXXXXX, KC_LGUI, KC_LALT, LOWER,   KC_SPC, KC_SPC, RAISE,   KC_MINUS, KC_EQUAL, KC_LBRC,  KC_RBRC}
},
/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    | Raise|   -  |  =  |   [   |   ]  |
 * `-----------------------------------------------------------------------------------'
 */
[_GAME] = {
  {KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,     KC_9,     KC_0,     KC_BSPC},
  {KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,     _______},
  {KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOT},
  {KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  _______},
  {_______, XXXXXXX, XXXXXXX, _______, _______, KC_SPC,  _______, _______, _______, _______, _______,   _______}
},

/* NUMPAD
 * ,-----------------------------------------------------------------------------------.
 * |  Esc |   /  |   *  |   -  |   4  |   5  |   6  |   7  |   8  |   9  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   7  |   8  |   9  |   +  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   4  |   5  |   6  |   +  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   1  |   2  |   3  | Enter|   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   0  |   0  |  .   | Enter| Lower|    Space    | Raise|   -  |  =   |   [  |   ]  |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = {
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_ESC, KC_PSLS, KC_PAST, KC_PMNS},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_P7,  KC_P8,   KC_P9,   KC_PPLS},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_P4,  KC_P5,   KC_P6,   KC_PPLS},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_P1,  KC_P2,   KC_P3,   KC_PENT},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_P0,  KC_P0,   KC_PDOT, KC_PENT},
},
/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   F1 |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Mute | BkSpc|   Up |  Del | Forwd| MBtn1|   MUp| MBtn2|   /  |   7  |   8  |  9   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Left | Down | Right| Refr  MLeft|  MDn  |MRight|   *  |   4  |   5  |  6   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  Vol+| Prev | Play | Next | Back |  MWDn| MBtn3| MWUp |  -   |   1  |  2   |  3   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Vol- |      |      |      |      |             |      |   +  | Enter|  0   |  .   |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_GRV,  KC_F1,    KC_F2,   KC_F3,    KC_F4,          KC_F5,   KC_F6,   KC_F7,   KC_F8,    KC_F9,   KC_F10, KC_DEL},
  {KC_MUTE, KC_BSPC,  KC_UP,   KC_DEL,   KC_WWW_FORWARD, _______, _______, _______, _______,  _______,   _______,  _______},
  {_______, KC_LEFT,  KC_DOWN, KC_RIGHT, KC_WWW_REFRESH, _______, _______, _______, _______,  _______,   _______,  _______},
  {KC_VOLU, KC_MPRV,  KC_MPLY, KC_MNXT,  KC_WWW_BACK,    _______, _______, _______, _______,  _______,   _______,  _______},
  {KC_VOLD, M(0),  _______, _______,  _______,        _______, _______, _______, _______,  _______, _______,  _______}
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Bksp | PgUp |  Del |      |      |      | PgUp |  Up  | PgDn |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Home | PgDn |  End |      |      | Home | Left | Down | Right|   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Pause| Ins  |      |      | Print|Screen| End  |      |      |      |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {KC_GRV, KC_EXLM, KC_AT,    KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN,  KC_RPRN, KC_BSPC},
  {_______, KC_PGDN, KC_UP, KC_PGUP,  _______, _______, _______, KC_PGUP, KC_UP,   _______,  _______, KC_BSLASH},
  {_______, KC_LEFT, KC_DOWN, KC_RIGHT,  _______, _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______},
  {_______, KC_PAUSE, KC_HOME, KC_END, KC_INS, KC_PSCR, _______, KC_END,  _______, _______,  _______, _______},
  {_______, M(1), _______, _______, _______, _______, _______, _______, KC_QUES, KC_COLN, _______,  KC_CAPS}
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |qwerty|ColMak|Dvorak|      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |AGNorm|AGSwap|      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |Aud On|AudOff|MidiOn|MdiOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus On|MusOff| Sleep| Wake | Arrow| Game |NUMPAD|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |     Reset   |      |      |      |      |      |
 * `---------------------------------------------------------------------------------aa--'
 */
[_ADJUST] = {
  {_______, _______,  QWERTY, _______,  _______, _______,          _______,        _______, _______, _______, _______, _______},
  {_______, RESET,   _______, AG_NORM, AG_SWAP, _______,          _______,        _______, _______, _______, _______, KC_DEL},
  {_______, _______, _______, AU_ON,   AU_OFF,  MI_ON,            MI_OFF,         QWERTY, _______, _______, _______, _______},
  {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  KC_SYSTEM_SLEEP,  KC_SYSTEM_WAKE, ARROW,      GAME,  NUMPAD, _______, _______},
  {_______, _______, _______, _______, _______, RESET,   _______,   _______, QWERTY, GAME, MU_ON, MU_OFF}
}


};

#ifdef AUDIO_ENABLE
float tone_startup[][2] = SONG(VILLIAN_SOUND);
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_dvorak[][2]    = SONG(DVORAK_SOUND);

float tone_caps_on[][2]    = SONG(CAPS_LOCK_ON_SOUND);
float tone_caps_off[][2]   = SONG(CAPS_LOCK_OFF_SOUND);

float tone_goodbye[][2] = SONG(GOODBYE_SOUND);

float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);

#endif

// //Tap Dance Declarations
// enum {
//   TD_ESC_CAPS = 0
// };

// //Tap Dance Definitions
// qk_tap_dance_action_t tap_dance_actions[] = {
//   //Tap once for Esc, twice for Caps Lock
//   [TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS)
// // Other declarations would go here, separated by commas, if you have them
// };

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) // this is the function signature -- just copy/paste it into your keymap file as it is.
{
  switch(id) {
    case 0: // this would trigger when you hit a key mapped as M(0) davidallen417@gmail.com
      if (record->event.pressed) {
        return MACRO( I(8), T(D), T(A), T(V), T(I), T(D), T(A), T(L), T(L), T(E), T(N), T(4), T(1), T(7), D(LSFT), T(AT), U(LSFT), T(G), T(M), T(A), T(I), T(L), T(DOT), T(C), T(O), T(M), END  ); 
      }
      break;

    case 1: // this would trigger when you hit a key mapped as M(1)  dpallen@wpi.edu
      if (record->event.pressed) {
        return MACRO( I(8), T(D), T(P), T(A), T(L), T(L), T(E), T(N), D(LSFT), T(AT), U(LSFT), T(W), T(P), T(I), T(DOT), T(E), T(D), T(U), END  );
      }
      break;
  }
  return MACRO_NONE;
};




bool process_record_user(uint16_t keycode, keyrecord_t *record) {
      switch(keycode) {
        case QWERTY:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
            #endif
            persistant_default_layer_set(1UL<<_QWERTY);
          }
          return false;
          break;
        case GAME:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_NOTE_ARRAY(tone_colemak, false, 0);
            #endif
            persistant_default_layer_set(1UL<<_GAME);
          }
          return false;
          break;
        case NUMPAD:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_NOTE_ARRAY(tone_dvorak, false, 0);
            #endif
            persistant_default_layer_set(1UL<<_NUMPAD);
          }
          return false;
          break;
        case ARROW:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_NOTE_ARRAY(tone_colemak, false, 0);
            #endif
            persistant_default_layer_set(1UL<<_LOWER);
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
      }
      return true;
};

#ifdef AUDIO_ENABLE

  void matrix_init_user(void){
      _delay_ms(20); // gets rid of tick
      startup_user();
  }

  void led_set_user(uint8_t usb_led)
  {
      static uint8_t old_usb_led = 0;

      _delay_ms(10); // gets rid of tick

      if (!is_playing_notes())
      {
          if ((usb_led & (1<<USB_LED_CAPS_LOCK)) && !(old_usb_led & (1<<USB_LED_CAPS_LOCK)))
          {
                  // If CAPS LK LED is turning on...
                  PLAY_NOTE_ARRAY(tone_caps_on,  false, LEGATO);
          }
          else if (!(usb_led & (1<<USB_LED_CAPS_LOCK)) && (old_usb_led & (1<<USB_LED_CAPS_LOCK)))
          {
                  // If CAPS LK LED is turning off...
                  PLAY_NOTE_ARRAY(tone_caps_off, false, LEGATO);
          }
      }
      old_usb_led = usb_led;

  }
    

  void startup_user()
  {
      _delay_ms(20); // gets rid of tick
      PLAY_NOTE_ARRAY(tone_startup, false, 0);
  }

  void shutdown_user()
  {
      PLAY_NOTE_ARRAY(tone_goodbye, false, 0);
      _delay_ms(150);
      stop_all_notes();
  }

  void music_on_user(void)
  {
      PLAY_NOTE_ARRAY(music_scale, false, 0);
  }

#endif
