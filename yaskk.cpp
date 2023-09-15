#include "yaskk.h"
#include "conf.h"
#include "dict.h"
#include "line.h"
#include "skk.h"
#include "utf8.h"
#include "util.h"
#include <signal.h>

/* global */
volatile sig_atomic_t LoopFlag = true;
volatile sig_atomic_t WindowResized = false;

static void sig_handler(int signo) {
  if (signo == SIGCHLD) {
    wait(NULL);
    LoopFlag = false;
  } else if (signo == SIGWINCH) {
    WindowResized = true;
  }
}

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
    struct sigaction sigact;
    memset(&sigact, 0, sizeof(struct sigaction));

    sigact.sa_handler = sig_handler;
    sigact.sa_flags = SA_RESTART;
    esigaction(SIGCHLD, &sigact, NULL);
    esigaction(SIGWINCH, &sigact, NULL);

    etcgetattr(STDIN_FILENO, &save_tm);
    set_rawmode(STDIN_FILENO, &save_tm);
  }

  ~TtyImpl() {
    struct sigaction sigact;
    memset(&sigact, 0, sizeof(struct sigaction));
    sigact.sa_handler = SIG_DFL;
    sigaction(SIGCHLD, &sigact, NULL);
    sigaction(SIGWINCH, &sigact, NULL);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &save_tm);
    fflush(stdout);
  }
};

Tty::Tty() : m_impl(new TtyImpl) {}

Tty::~Tty() { delete m_impl; }

void fork_and_exec(int *master, const char *cmd, char *const argv[]) {
  struct winsize wsize;
  if (ioctl(STDIN_FILENO, TIOCGWINSZ, &wsize) < 0)
    logging(ERROR, "ioctl: TIOCWINSZ failed\n");

  auto pid = eforkpty(master, NULL, NULL, &wsize);
  if (pid == 0) /* child */
    eexecvp(cmd, argv);
  // eexecvp(exec_cmd, (const char *[]){exec_cmd, NULL});
}

void check_fds(fd_set *fds, int stdin, int master) {
  struct timeval tv;

  FD_ZERO(fds);
  FD_SET(stdin, fds);
  FD_SET(master, fds);
  tv.tv_sec = 0;
  tv.tv_usec = SELECT_TIMEOUT;
  eselect(master + 1, fds, NULL, NULL, &tv);
}

void mainloop(struct skk_t *skk) {
  /* main loop */
  uint8_t buf[1024];
  fd_set fds;
  while (LoopFlag) {
    check_fds(&fds, STDIN_FILENO, skk->fd);

    /* data arrived from stdin */
    if (FD_ISSET(STDIN_FILENO, &fds)) {
      ssize_t size = read(STDIN_FILENO, buf, BUFSIZE);

      if (size < INPUT_THRESHLD)
        parse(skk, buf, size);
      else /* large data: maybe not manual input */
        ewrite(skk->fd, buf, size);
    }

    /* data arrived from pseudo terminal */
    if (FD_ISSET(skk->fd, &fds)) {
      ssize_t size = read(skk->fd, buf, BUFSIZE);
      if (size > 0)
        ewrite(STDOUT_FILENO, buf, size);
    }

    /* if receive SIGWINCH, reach here */
    if (WindowResized) {
      WindowResized = false;
      struct winsize wsize;
      ioctl(STDIN_FILENO, TIOCGWINSZ, &wsize);
      ioctl(skk->fd, TIOCSWINSZ, &wsize);
    }
  }
}
