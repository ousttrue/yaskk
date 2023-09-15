#include "skk.h"
#include "yaskk.h"

auto shell_cmd = "/bin/bash";

int main(int argc, char *const argv[]) {
  setlocale(LC_ALL, "");

  Tty tty;

  skk_t skk;
  if (argc < 2) {
    skk.fork(shell_cmd, argv + 1);
  } else {
    skk.fork(argv[1], argv + 2);
  }
  skk.mainloop();

  return EXIT_SUCCESS;
}
