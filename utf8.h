/* functions for wide char (UCS2), multibyte char (UTF-8) conversion */
/* ref:
 *	-	http://ja.m.wikipedia.org/wiki/UTF-8
 *	-	http://en.m.wikipedia.org/wiki/UTF-8
 *	-	http://www.azillionmonkeys.com/qed/unicode.html
 */
#pragma once
#include "yaskk.h"
#include "line.h"
#include <stdint.h>
enum {
  // UTF8_LEN_MAX          = 4,
  MALFORMED_CHARACTER = 0xFFFD,
  CURSIVE_SQUARE_OFFSET = 0x60,
};

/*
 * from UCS2 to UTF-8
 * return length of UTF-8 sequence
 */
int utf8_encode(uint32_t ucs, char utf8_buf[UTF8_LEN_MAX + 1]);
/*
 * from UTF-8 to UCS2
 * return length of read sequence
 */
int utf8_decode(const char *utf8_str, uint32_t *ucs);
void toggle_cursive_square(struct line_t *line);
