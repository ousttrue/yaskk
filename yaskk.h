#pragma once
#include <signal.h>
#include <stdint.h>

#define SIGWINCH 28

enum {
  BUFSIZE = 1024,
  MAX_ARGS = 256,
  INPUT_THRESHLD = 6,
  SELECT_TIMEOUT = 15000,
  SLEEP_TIME = 30000,
  NHASH = 512,
  INIT_ENTRY = 8,
  KEYSIZE = 64,
  LBUFSIZE = 1024,
  MAX_CELLS = 1024,
  UTF8_LEN_MAX = 3,
  LINE_LEN_MAX = UTF8_LEN_MAX * MAX_CELLS + 1,
};

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

enum skk_mode_t {
  MODE_ASCII = 0,
  MODE_CURSIVE,
  MODE_SQUARE,
  MODE_COOK,
  MODE_APPEND,
  MODE_SELECT,
};

extern const char *mode2str[];

/* global */
extern volatile sig_atomic_t LoopFlag;
extern volatile sig_atomic_t WindowResized;
