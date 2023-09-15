#include "yaskk.h"
#include "conf.h"
#include "dict.h"
#include "line.h"
#include "skk.h"
#include "utf8.h"
#include "util.h"

static void set_rawmode(int fd, struct termios *save_tm) {
  struct termios tm;
  tm = *save_tm;
  tm.c_iflag = tm.c_oflag = 0;
  tm.c_cflag &= ~CSIZE;
  tm.c_cflag |= CS8;
  tm.c_lflag &= ~(ECHO | ISIG | ICANON);
  tm.c_cc[VMIN] = 1;  /* min data size (byte) */
  tm.c_cc[VTIME] = 0; /* time out */
  etcsetattr(fd, TCSAFLUSH, &tm);
}

struct TtyImpl {
  struct termios save_tm;

  TtyImpl() {
    etcgetattr(STDIN_FILENO, &save_tm);
    set_rawmode(STDIN_FILENO, &save_tm);
  }

  ~TtyImpl() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &save_tm);
    fflush(stdout);
  }
};

Tty::Tty() : m_impl(new TtyImpl) {}

Tty::~Tty() { delete m_impl; }
