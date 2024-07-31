#pragma once
#include "yaskk.h"
#include "dict.h"
#include "line.h"
#include <sys/types.h>

/* struct for skk */
struct skk_t {
  int fd;   /* master of pseudo terminal */
  int mode; /* skk mode */
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
};

/* skk init/die functions */
void skk_init(struct skk_t *skk);
void skk_die(struct skk_t *skk);
/* parse functions */
bool skk_preedit(struct skk_t *skk, uint8_t ch);
void skk_select(struct skk_t *skk, uint8_t ch);
/* mode helper function */
void change_mode(struct skk_t *skk, enum skk_mode_t next);
void clear_select_status(struct skk_t *skk);
/* prototype */
void mode_ascii(struct skk_t *skk, uint8_t ch);
void mode_cursive_square(struct skk_t *skk, uint8_t ch);
void mode_cook(struct skk_t *skk, uint8_t ch);
void mode_select(struct skk_t *skk, uint8_t ch);
void mode_append(struct skk_t *skk, uint8_t ch);
extern void (*mode_func[])(struct skk_t *skk, uint8_t ch);
/* mode functions */
void mode_ascii(struct skk_t *skk, uint8_t ch);
void mode_cook(struct skk_t *skk, uint8_t ch);
void mode_cursive_square(struct skk_t *skk, uint8_t ch);
void mode_select(struct skk_t *skk, uint8_t ch);
void mode_append(struct skk_t *skk, uint8_t ch);
void parse(struct skk_t *skk, uint8_t *buf, ssize_t size);
