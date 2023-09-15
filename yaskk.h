#pragma once
#define _XOPEN_SOURCE 600
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
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>

#define SIGWINCH 28

enum {
  INPUT_THRESHLD = 6,
  SELECT_TIMEOUT = 15000,
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

// void tty_init(struct termios *save_tm);
// void tty_die(struct termios *save_tm);
void fork_and_exec(int *master, const char *cmd, char *const argv[]);
void check_fds(fd_set *fds, int stdin, int master);

void mainloop(struct skk_t *skk);
