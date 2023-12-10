#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

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
enum layer_number {
    _QWERTY_MAIN  = 0,
    _QWERTY,
    _QWERTY_MIN,
    _LOWER,
    _RAISE,
    _ADJUST,
    _ARROW
};

enum custom_keycodes {
  QWERTY_MAIN = SAFE_RANGE,
  QWERTY,
  LOWER,
  RAISE,
  ADJUST,
  ARROW,
  BACKLIT,
  RGBRST,
  XCODEBUILD,
  QWERTY_MIN,
  BSP_DEL
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Modifiers keys
#define RCTL_BR RCTL_T(KC_RBRACKET)
#define LCTL_BR LCTL_T(KC_LBRACKET)

#define SFT_SPC LSFT_T(KC_SPACE)
#define SFT_ENT RSFT_T(KC_ENTER)
#define GUI_NUBS LGUI_T(KC_NUBS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  
  [_QWERTY_MAIN] = LAYOUT( \
      KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, \
      KC_LSFT , KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT, \
      KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  LOWER  ,   RAISE ,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SC_SENT, \
      ARROW, KC_NUBS, SC_LAPO, KC_LGUI, KC_LBRC,   LOWER, KC_BSPC, KC_SPC,RAISE,  KC_RBRC, KC_RGUI,  SC_RAPC, KC_NUHS , KC_RCTL \
      ),
  [_QWERTY] = LAYOUT( \
      KC_NUBS,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, \
      KC_QUOT , KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_EQL, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  LOWER  ,   RAISE ,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SC_SENT, \
      KC_LCTL, ARROW, SC_LAPO, KC_LGUI, KC_LBRC,   LOWER, KC_BSPC,   KC_SPC,RAISE,  KC_RBRC, KC_RGUI,  SC_RAPC, KC_NUHS , KC_RCTL \
      ),
 [_QWERTY_MIN] = LAYOUT( \
      XXXXXXX,  XXXXXXX,    XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,                    XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_TAB,      KC_Q,       KC_W,    KC_E,     KC_R,    KC_T,                       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    BSP_DEL, \
      KC_LSFT ,    KC_A,       KC_S,    KC_D,     KC_F,    KC_G,                       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT, \
      LCTL_BR ,    KC_Z,       KC_X,    KC_C,     KC_V,    KC_B,  XXXXXXX, XXXXXXX ,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RCTL_BR, \
      XXXXXXX,  XXXXXXX,    XXXXXXX, XXXXXXX, GUI_NUBS,   RAISE,  SFT_SPC, SFT_ENT ,  LOWER,   RAISE, XXXXXXX,  XXXXXXX, XXXXXXX , XXXXXXX \
      ),
  [_LOWER] = LAYOUT( \
      XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_TAB ,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_F12, \
      _______,  _______, _______, _______, _______, _______,                    _______, _______, _______, _______, KC_NUHS,  KC_MINS, \
      _______,  KC_BSPC, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, QWERTY_MAIN,KC_ESC,KC_NUBS, KC_QUOT, KC_LBRC, KC_RBRC, KC_BSLS, KC_EQL, \
      XXXXXXX,  XXXXXXX, XXXXXXX, _______, _______, _______, _______,    KC_DEL,  _______, _______, _______, XXXXXXX,   XXXXXXX, XXXXXXX \
      ),
  [_RAISE] = LAYOUT( \
      XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, \
      KC_F1, KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                       KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,    KC_F12, \
      _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU,                   KC_HOME, KC_PGUP, KC_UP,   _______, KC_PAUS, _______, \
      KC_CAPS, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC, _______, \
      XXXXXXX,  XXXXXXX,    XXXXXXX, _______, _______, _______, _______, KC_END,  KC_PGDN, KC_DEL,  KC_INS,  XXXXXXX,  XXXXXXX,    XXXXXXX \
      ),
  [_ADJUST] =  LAYOUT( \
      XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, \
      KC_NUBS, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,  XXXXXXX,                 XXXXXXX, QWERTY,  QWERTY_MAIN, _______,  _______, _______, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, QWERTY_MAIN, QWERTY_MIN, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD \
      ),
  [_ARROW] =  LAYOUT( \
      _______, _______, _______, _______, _______, _______,                                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      _______, _______, _______, _______, _______, _______,                                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PWR, \
      _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU,                                       XXXXXXX, XXXXXXX,  KC_UP , XXXXXXX, XXXXXXX, XXXXXXX, \
      _______, _______, _______, _______, _______, _______, QK_AUTO_SHIFT_UP, QK_AUTO_SHIFT_DOWN, XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, XCODEBUILD, \
      _______, _______, _______, _______, _______, _______, _______         , QK_AUTO_SHIFT_TOGGLE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
      )
};

#ifdef AUDIO_ENABLE

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

static void render_layer_state(int layer) {
    switch (get_highest_layer(layer)) {
        case _QWERTY_MAIN: oled_write("Main ", false); break;
        case _QWERTY:      oled_write("DFLT ", true); break;
        case _QWERTY_MIN:  oled_write("Min  " ,true); break;
        case _RAISE:       oled_write("Rai  ", true); break;
        case _LOWER:       oled_write("Low  ", true); break;
        case _ADJUST:      oled_write("Adj  ", true); break;
        case _ARROW:       oled_write("Arr  ", true); break;
        default: oled_write(("UNDEF"), true); break;
    }
}

void render_status(void) {
  // Host Keyboard Layer Status    
  render_layer_state(layer_state | default_layer_state);
}

static void render_anuan(void) {
    render_layer_state(default_layer_state);
}

void oled_render_kapi_logo(void) {
    static const char PROGMEM font_kapi_logo[2][16] = {
        {0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0},
        {0x85, 0x86, 0x87, 0x88, 0x89, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0}
    };
    oled_write_P(font_kapi_logo[get_current_wpm() % 2], false);
};

static void render_rgbled_status(bool full) {
#ifdef RGBLIGHT_ENABLE
  char buf[30];
  if (RGBLIGHT_MODES > 1 && rgblight_is_enabled()) {
      if (full) {
          snprintf(buf, sizeof(buf), " LED %2d: %d,%d,%d ",
                   rgblight_get_mode(),
                   rgblight_get_hue()/RGBLIGHT_HUE_STEP,
                   rgblight_get_sat()/RGBLIGHT_SAT_STEP,
                   rgblight_get_val()/RGBLIGHT_VAL_STEP);
      } else {
          snprintf(buf, sizeof(buf), "[%2d] ", rgblight_get_mode());
      }
      oled_write(buf, false);
  }
#endif
}

char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%c", name);
}

void oled_render_keylog(void) {
    oled_write_P(PSTR("\n"), false);
    oled_write_ln(keylog_str, false);
}

void oled_render_separator(void) {
    oled_write_ln("_____", false);
}

void oled_render_wpm(void) {
    oled_write("WPM: ", false);
    oled_write(get_u8_str(get_current_wpm(), ' '), false);
}

bool oled_task_user(void) {
  if(is_keyboard_master()){
    render_status();
    oled_render_separator();
    render_anuan();
    oled_render_separator();
    oled_render_keylog();
    oled_render_separator();
    oled_render_kapi_logo();
    oled_render_separator();
  }else{
    oled_render_wpm();
    oled_render_separator();
    oled_render_kapi_logo(); 
    oled_render_separator();  
    render_rgbled_status(true);
  }
  return false;   
}

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case QWERTY_MAIN:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY_MAIN);
      }
      return false;
    case QWERTY_MIN:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY_MIN);
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE + 1);
          #endif
        }
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
        #endif
        TOG_STATUS = false;
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE);
          #endif
        }
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_RAISE);
        TOG_STATUS = false;
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
    case ARROW:
        if (record->event.pressed) {
          layer_on(_ARROW);
        } else {
          layer_off(_ARROW);
        }
        return false;
        break;
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    case XCODEBUILD:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL)SS_DOWN(X_LGUI)SS_DOWN(X_G)SS_UP(X_LSFT)SS_UP(X_LCTL)SS_UP(X_LGUI)SS_UP(X_G));
        }
        return false;
        break;
    case BSP_DEL:
        if (record->event.pressed) {
             saved_mods = get_mods() & MOD_MASK_SHIFT;

            if (saved_mods == MOD_MASK_SHIFT) {  // Both shifts pressed
                register_code(KC_DEL);
            } else if (saved_mods) {   // One shift pressed
                del_mods(saved_mods);  // Remove any Shifts present
                register_code(KC_DEL);
                add_mods(saved_mods);  // Add shifts again
            } else {
                register_code(KC_BSPC);
            }
        } else {
            unregister_code(KC_DEL);
            unregister_code(KC_BSPC);
        }
        return false;
        break;
  }
  return true;
}

