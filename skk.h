#pragma once
#include "dict.h"
#include "line.h"
#include <stdbool.h>
#include <unistd.h>

enum skk_mode_t {
  MODE_ASCII = 0,
  MODE_CURSIVE,
  MODE_SQUARE,
  MODE_COOK,
  MODE_APPEND,
  MODE_SELECT,
};

/* struct for skk */
struct skk_t {
  int fd;               /* master of pseudo terminal */
  enum skk_mode_t mode; /* skk mode */
  /* for line edit */
  struct line_t current; /* current line status */
  struct line_t next;    /* next line status */
  bool need_flush;       /* output all characters and clear line buffer */
  /* for candidate */
  struct dict_t dict;
  struct parse_t *select;
  int index;
  /* saved string */
  /*
   * in select mode:
   *   cook: keyword of dict/hash lookup and restored string after select mode
   */
  char restore[LINE_LEN_MAX - 1];
  /*
   * in append mode:
   *   cook + append[0]              : keyword of dict/hash lookup
   *   cook + append[1] ... append[n]: restored string after append -> cook mode
   */
  struct append_t {
    int pos;                /* position of MARK_APPEND */
    char ch;                /* cook + append.ch : keyword of dict/hash lookup */
    char str[LINE_LEN_MAX]; /* cook + append.str: restored string after append
                               -> cook mode */
  } append;

  skk_t();
  skk_t(const skk_t &) = delete;
  skk_t &operator=(const skk_t &) = delete;
  ~skk_t();
  void mainloop();
  void parse(uint8_t *buf, ssize_t size);
  void fork(const char *cmd, char *const argv[]);
};
