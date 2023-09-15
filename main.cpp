#include "skk.h"
#include "util.h"
#include "yaskk.h"
#include <fcntl.h>
#include <locale.h>
#include <stdint.h>
#include <sys/ioctl.h>

const char *const shell_cmd = "/bin/bash";

int main(int argc, char *const argv[]) {
  setlocale(LC_ALL, "");

  struct termios save_tm;
  tty_init(&save_tm);

  skk_t skk;
  skk_init(&skk);

  /*
  int i;
  struct dict_entry_t *entry;
  for (i = 0; i < skk.dict.entry_count; i++) {
          entry = &skk.dict.table[i];
          if (dict_search(&skk.dict, entry->keyword, strlen(entry->keyword)) !=
  NULL) fprintf(stderr, "keyword:%s found\n", entry->keyword); else
                  fprintf(stderr, "keyword:%s not found\n", entry->keyword);
  }
  */

  /* fork */
  // argv[0] = (argc < 2) ? shell_cmd: argv[1];
  const char *cmd = (argc < 2) ? shell_cmd : argv[1];
  fork_and_exec(&skk.fd, cmd, argv + 1);

  mainloop(&skk);

  /* normal exit */
  skk_die(&skk);
  tty_die(&save_tm);

  return EXIT_SUCCESS;
}
