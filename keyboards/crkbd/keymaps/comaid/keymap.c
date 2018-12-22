#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
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
#define _QWERTY 0
#define _LOWER 3
#define _RAISE 4
#define _PAD   5
#define _FNC   6
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST
};


// b

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_RAISE RAISE
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LSMOD RGB_SMOD
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_ALTKN ALT_T(KC_LANG1)

#define KC_PAD_F  LT(_PAD,KC_F)
#define KC_FNC_J  LT(_FNC,KC_J)
#define KC_C_ENT

#define KC_C_BS   LCTL_T(KC_BSPC)
#define KC_S_SPC  LSFT_T(KC_SPC)
#define KC_G_LEFT LGUI(KC_LEFT)
#define KC_G_RGHT LGUI(KC_RIGHT)
#define KC_A_TAB  LALT(KC_TAB)
#define KC_G_F13  LGUI_T(KC_F13)
#define KC_A_F14  LALT_T(KC_F14)

#define KC_LW_ENT LT(_LOWER,KC_ENT)
#define KC_LW_BS LT(_LOWER,KC_BSPC)
#define KC_RS_SPC LT(_RAISE,KC_SPC)

#define KC_c(x) LCTL_T(KC_##x)
#define KC_s(x) LSFT_T(KC_##x)
#define KC_a(x) LALT_T(KC_##x)

#define KC_lc(x) LCTL(KC_##X)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------------.                  ,-----------------------------------------------.
         TAB,      Q,      W,      E,      R,      T,                         Y,      U,      I,      O,      P,   MINS,\
  //|-------+-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------+-------|
        LCTL,   c(A),   a(S),   s(D),  PAD_F,      G,                         H,  FNC_J,   s(K),   a(L),c(SCLN),   QUOT,\
  //|-------+-------+-------+-------+-------+-------|                  |-------+-------+-------+-------+-------+-------|
        LSFT,      Z,      X,      C,      V,      B,                         N,      M,   COMM,    DOT,   SLSH,   RSFT,\
  //|-------+-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-------+-------|
                                     a(BSPC), LW_ENT, c(F14),   s(F13), RS_SPC,  G_F13 \
                                   //`----------------------'  `-----------------------'
   ),

   [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,   DEL,  PGDN,    UP,  PGUP, XXXXX,                  XXXXX,  PGDN,    UP,  PGUP,   DEL,   INS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,c(BSPC),a(LEFT),s(DOWN), RIGHT,  HOME,                HOME,  LEFT,  DOWN, RIGHT,  BSPC, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, lc(Z), lc(X), lc(C), lc(V),   END,                    END,   ENT, XXXXX,  SLCK,  PAUS, CAPS,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,   _____, _____, _____ \
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        TAB,  EXLM,    AT,  LCBR,  RCBR,  AMPR,                   CIRC,  AMPR,  ASTR, XXXXX, XXXXX,  XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  HASH,   DLR,  LPRN,  RPRN,  ASTR,                  XXXXX,   EQL,  PLUS,  UNDS,  PIPE,   GRV,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  PERC,  CIRC,  LBRC,  RBRC, XXXXX,                  XXXXX, XXXXX, LANG1, LANG2,  BSLS,  TILD,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,    _____, _____, _____ \
                              //`--------------------'  `--------------------'
  ),

  [_PAD  ] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX,     7,     8,     9,   EQL, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX,     4,     5,     6,     0,  PLUS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX,     1,     2,     3,  ASTR, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,    _____, _____, _____ \
                              //`--------------------'  `--------------------'
  ),

  [_FNC  ] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____,    F1,    F2,    F3,    F4, XXXXX,                  XXXXX,     7,     8,     9,   EQL, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,    F5,    F6,    F7,    F8, XXXXX,                  XXXXX, XXXXX,     5,     6,     0,  PLUS,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,    F9,    F10,  F11,   F12, XXXXX,                  XXXXX,     1,     2,     3,  ASTR, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,    _____, _____, _____ \
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        RST,  LRST, XXXXX, XXXXX, XXXXX, XXXXX,                  XXXXX, XXXXX,  PSCR, XXXXX, XXXXX, XXXXX,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI, XXXXX, XXXXX,                  XXXXX,G_LEFT, XXXXX,G_RGHT, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      LSMOD,  LHUD,  LSAD,  LVAD, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,   _____, _____, _____ \
                              //`--------------------'  `--------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

const char *read_mode_icon(bool swap);
const char *read_host_led_state(void);
void set_timelog(void);
const char *read_timelog(void);
bool iota_gfx_on(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

bool kanji_enabled = false;

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
    //matrix_write_ln(matrix, read_timelog());
    matrix_write(matrix,kanji_enabled?"kk1":"kk0");
  } else {
//	if(kanji_enabled==1){
//    	matrix_write(matrix, read_logo());
//    }else{
    matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
//    matrix_write_ln(matrix, read_host_led_state());
    matrix_write_ln(matrix, read_timelog());
//	}
  }
}

//bool force_dirty = false;

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))/*||force_dirty*/) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}

// from https://github.com/msandiford/qmk_firmware/commit/de5b55a6c5e14bf54d77db6ac5a7d8c5cb2c9d7c#diff-013b1ab0d16580ef9aaf2259776a78cd
#define LOWER_AND_RAISE ((1UL << _LOWER) | (1UL << _RAISE))
uint32_t layer_state_set_kb(uint32_t state) {
  if ((state & LOWER_AND_RAISE) == LOWER_AND_RAISE) {
    state |= 1UL << _ADJUST;
  } else {
    state &= ~(1UL << _ADJUST);
  }
  return state;
}
// end

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
    set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
//    case LOWER:
//      if (record->event.pressed) {
//        layer_on(_LOWER);
//        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
//      } else {
//        layer_off(_LOWER);
//        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
//      }
//      return false;
//      break;
//    case RAISE:
//      if (record->event.pressed) {
//        layer_on(_RAISE);
//        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
//      } else {
//        layer_off(_RAISE);
//        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
//      }
//      return false;
//      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
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
  }
  return true;
}

#endif
