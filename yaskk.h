#pragma once
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <limits.h>
#include <locale.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIGWINCH 28

enum {
  NHASH = 512,
  KEYSIZE = 64,
  LBUFSIZE = 1024,
};

class Tty {
  struct TtyImpl *m_impl;

public:
  Tty();
  Tty(const Tty &) = delete;
  Tty &operator=(const Tty &) = delete;
  ~Tty();
};


