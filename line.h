#pragma once
#include "utf8.h"
#include <stdint.h>

enum {
  MAX_CELLS = 1024,
  LINE_LEN_MAX = UTF8_LEN_MAX * MAX_CELLS + 1,
};

enum mark {
  MARK_COOK = 0x25BD,   /* ▽ */
  MARK_SELECT = 0x25BC, /* ▼ */
  MARK_APPEND = 0x2A,   /* * */
};

/* struct for line edit */
struct cursor_t {
  int insert;  /* character insert position */
  int preedit; /* position of first preedit character */
};
struct line_t {
  uint32_t cells[MAX_CELLS]; /* UCS2 codepoint */
  cursor_t cursor;
};

void line_init(struct line_t *line);
void toggle_cursive_square(struct line_t *line);
void append_ucs_char(struct line_t *line, int index, uint32_t ucs);
int preedit_length(struct line_t *line);
int get_utf8_str(struct line_t *line, int from, int to, char *utf8_buf);
void remove_chars(struct line_t *line, int from, int to);

int append_utf8_str(struct line_t *line, int index, const char *utf8_str);
void swap_ucs_char(struct line_t *line, int index, uint32_t ucs);
void remove_ucs_char(struct line_t *line, int index);
int line_length(struct line_t *line);
void send_backspace(int fd, int count);
int cook_length(struct line_t *line);
void remove_all_chars(struct line_t *line);
uint32_t get_ucs_char(struct line_t *line, int index);
void line_update(struct line_t *current, struct line_t *next, bool *need_flush,
                 int fd);
void line_show(struct line_t *line);
