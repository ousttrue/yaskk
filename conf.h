#pragma once
#include "yaskk.h"

/* misc */
#define shell_cmd "/bin/bash"

/* load files */
#define skkdict_file "SKK-JISYO.M"

/* mark: these strings must be ONE character and non ascii */
/*
const char *mark_cook   = "▽";
const char *mark_select = "▼";
const char *mark_append = "*";
*/

/* escape sequence */
#define backspace "\010"

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

enum mark {
  MARK_COOK = 0x25BD,   /* ▽ */
  MARK_SELECT = 0x25BC, /* ▼ */
  MARK_APPEND = 0x2A,   /* * */
};

enum {
  VERBOSE = false,
};
