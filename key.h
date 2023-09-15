#pragma once

enum ctrl_code {
  /* 7 bit */
  BEL = 0x07,
  BS = 0x08,
  HT = 0x09,
  LF = 0x0A,
  VT = 0x0B,
  FF = 0x0C,
  CR = 0x0D,
  ESC = 0x1B,
  DEL = 0x7F,
  /* others */
  SPACE = 0x20,
  BACKSLASH = 0x5C,
};

enum key_name_t {
  CTRL_AT = 0,
  CTRL_A,
  CTRL_B,
  CTRL_C,
  CTRL_D,
  CTRL_E,
  CTRL_F,
  CTRL_G,
  CTRL_H,
  CTRL_I,
  CTRL_J,
  CTRL_K,
  CTRL_L,
  CTRL_M,
  CTRL_N,
  CTRL_O,
  CTRL_P,
  CTRL_Q,
  CTRL_R,
  CTRL_S,
  CTRL_T,
  CTRL_U,
  CTRL_V,
  CTRL_W,
  CTRL_X,
  CTRL_Y,
  CTRL_Z,
  CTRL_BRACE_L,
  CTRL_BACKSLASH,
  CTRL_BRACE_R,
  CTRL_HAT,
  CTRL_UNDERBAR,
};

/* key */
enum key {
  KEY_ASCII = 'l',
  KEY_CURSIVE = CTRL_J,
  KEY_TOGGLE = 'q',
  KEY_SELECT = SPACE,
  // KEY_BACKSPACE = CTRL_H,
  KEY_NEXT = SPACE,
  KEY_PREV = 'x',
};
