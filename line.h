/* line edit functions
 *
 * struct line_t {
 *     uint32_t cells[MAX_CELLS]; // UCS2 codepoint
 *     struct cursor_t {
 *         int insert;
 *         int preedit;
 *     };
 * };
 *
 * cells[MAX_CELLS]: line buffer of editable character
 *                   each cell stands for UCS2 codepoint
 * +----------+----------+----------+   +----------------------+
 * | cells[0] | cells[1] | cells[2] |...| cells[MAX_CELLS - 1] |
 * +----------+----------+----------+   +----------------------+
 *
 * struct corsor_t:
 * - insert : instert position of next character
 * - preedit: first position of preedit character
 *
 * MODE_ASCII:
 *
 * +---+--------+                     +--------+
 * | a | (null) |  -- after update -> | (null) |
 * +---+--------+                     +--------+
 *         ^                              ^
 *         | insert                       | insert
 *
 * after line update, line buffer is immediately flushed (set need_flash flag)
 * insert and preedit are always "0"
 *
 * MODE_CURSIVE or MODE_SQUARE:
 *
 * +---+---+--------+
 * | s | h | (null) |
 * +---+---+--------+
 *   ^         ^
 *   |         | cursor.insert
 *   | cursor.preedit
 *
 * preedit is always "0"
 *
 * MODE_COOK:
 *
 * +---+----+---+--------+
 * | ▽ | あ | c | (null) |
 * +---+----+---+--------+
 *            ^     ^
 *            |     | insert
 *            | preedit
 */
#pragma once
#include "yaskk.h"

/* struct for line edit */
struct line_t {
  uint32_t cells[MAX_CELLS]; /* UCS2 codepoint */
  struct cursor_t {
    int insert;  /* character insert position */
    int preedit; /* position of first preedit character */
  } cursor;
};

/* utility functions */
void line_init(struct line_t *line);

int line_length(struct line_t *line);

int preedit_length(struct line_t *line);

int cook_length(struct line_t *line);

void line_show(struct line_t *line);

void move_cursor(struct cursor_t *cursor, int offset, uint32_t ucs);

/* remove functions */
void remove_ucs_char(struct line_t *line, int index);

void remove_chars(struct line_t *line, int from, int to);

void remove_all_chars(struct line_t *line);

/* append functions */
void append_ucs_char(struct line_t *line, int index, uint32_t ucs);

int append_utf8_str(struct line_t *line, int index, const char *utf8_str);

/* swap functions */
void swap_ucs_char(struct line_t *line, int index, uint32_t ucs);

/* get string functions */
uint32_t get_ucs_char(struct line_t *line, int index);

int get_utf8_str(struct line_t *line, int from, int to, char *utf8_buf);

/* update function */
void send_backspace(int fd, int count);

void line_update(struct line_t *current, struct line_t *next, bool *need_flush,
                 int fd);
