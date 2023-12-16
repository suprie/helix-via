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
    _QWERTY = 0,
    _COLEMAK,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  XCODEBUILD = SAFE_RANGE,
  BSP_DEL,
  TAB_ESC
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Modifiers keys
#define RCTL_BR  RCTL_T(KC_RCBR)
#define LCTL_BR  LCTL_T(KC_LCBR)

#define LCTL_Z  LCTL_T(KC_Z)

#define LSFT_BR  SFT_T(KC_LCBR)
#define RSFT_BR  SFT_T(KC_RCBR)

#define SFT_SPC  LSFT_T(KC_SPACE)
#define HYP_ENT  HYPR(KC_ENTER)
#define GUI_NUBS LGUI_T(KC_NUHS)

#define BKSP_LOW LT(_LOWER, KC_BSPC)
#define ENTRAI LT(_RAISE, KC_ENT)

#define LOWER TL_LOWR
#define RAISE TL_UPPR

#define COLEMAK DF(_COLEMAK)
#define QWERTY DF(_QWERTY)

#define  ADJ MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_QWERTY] = LAYOUT( \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      TAB_ESC,    KC_Q,    KC_W,    KC_E,     KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_QUOT, \
      RAISE ,     KC_A,    KC_S,    KC_D,     KC_F,    KC_G,                      KC_H,   KC_J,   KC_K,    KC_L, KC_SCLN,     LOWER, \
      LSFT_BR ,   KC_Z,    KC_X,    KC_C,     KC_V,    KC_B, XXXXXXX, XXXXXXX ,   KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, RSFT_BR, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, GUI_NUBS, BKSP_LOW, SFT_SPC, SFT_SPC ,ENTRAI, KC_TILD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
      ),
[_COLEMAK] = LAYOUT( \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      TAB_ESC,    KC_Q,    KC_W,    KC_F,     KC_P,    KC_B,                      KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_QUOT, \
      RAISE ,   KC_A,    KC_R,    KC_S,     KC_T,      KC_G,                      KC_M,    KC_N,    KC_E,    KC_I,    KC_O, LOWER, \
      LSFT_BR,   KC_X,    KC_C,    KC_D,     KC_V,    KC_Z, XXXXXXX, XXXXXXX ,   KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH, RSFT_BR, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, GUI_NUBS, BKSP_LOW, SFT_SPC, SFT_SPC ,ENTRAI,  KC_TILD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
      ),
  [_LOWER] = LAYOUT( \
      XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      TAB_ESC ,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_F12, \
      _______,  KC_MINS, KC_QUOT, KC_NUHS, KC_NUBS, _______,                    _______, KC_NUBS, KC_NUHS, KC_QUOT, KC_MINS, _______, \
      _______,   KC_EQL, KC_LBRC, KC_RBRC, KC_TILD, _______, XXXXXXX, XXXXXXX,  KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC,  KC_EQL, _______, \
      XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, KC_UNDS, BSP_DEL, SFT_SPC, SFT_SPC,  HYP_ENT, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX \
      ),
  [_RAISE] = LAYOUT( \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_F1  ,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, \
      _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU,                   KC_HOME, KC_PGUP,   KC_UP, _______, KC_PAUS, _______, \
      KC_CAPS, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC, _______, \
      XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______, KC_END,  KC_PGDN, KC_DEL,   KC_INS, XXXXXXX, XXXXXXX, XXXXXXX \
      ),
  [_ADJUST] =  LAYOUT( \
      XXXXXXX,  XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_NUBS, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  KC_DEL, \
      _______, QWERTY, _______, _______, _______, _______,                    COLEMAK, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD \
      ),
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
        case _QWERTY:      oled_write("DFLT ", true); break;
        case _RAISE:       oled_write("Rai  ", true); break;
        case _LOWER:       oled_write("Low  ", true); break;
        case _ADJUST:      oled_write("Adj  ", true); break;
        case _COLEMAK:    oled_write("COL  ", true); break;
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

// void oled_render_kapi_logo(void) {
//     static const char PROGMEM font_kapi_logo[2][16] = {
//         {0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0},
//         {0x85, 0x86, 0x87, 0x88, 0x89, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0}
//     };
//     oled_write_P(font_kapi_logo[get_current_wpm() % 2], false);
// };

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
  }
  return false;   
}

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint8_t saved_mods   = 0;

  if (record->event.pressed) {
    set_keylog(keycode, record);
  }

  switch (keycode) {
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
    case TAB_ESC:
        if (record->event.pressed) {
             saved_mods = get_mods() & MOD_MASK_SHIFT;

            if (saved_mods) {   // One shift pressed
                del_mods(saved_mods);  // Remove any Shifts present
                register_code(KC_ESC);
                add_mods(saved_mods);  // Add shifts again
            } else {
                register_code(KC_TAB);
            }
        } else {
            unregister_code(KC_ESC);
            unregister_code(KC_TAB);
        }
        return false;
        break;
  }
  return true;
}

