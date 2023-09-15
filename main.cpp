#include "skk.h"
#include "util.h"
#include "yaskk.h"
#include <fcntl.h>
#include <locale.h>
#include <stdint.h>
#include <sys/ioctl.h>

auto shell_cmd = "/bin/bash";

int main(int argc, char *const argv[]) {
  setlocale(LC_ALL, "");

  Tty tty;

  skk_t skk;
  skk_init(&skk);

  /* fork */
  const char *cmd = (argc < 2) ? shell_cmd : argv[1];
  fork_and_exec(&skk.fd, cmd, argv + 1);

  mainloop(&skk);

  /* normal exit */
  skk_die(&skk);

  return EXIT_SUCCESS;
}
