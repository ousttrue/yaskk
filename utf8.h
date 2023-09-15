#pragma once
#include <stdint.h>

enum {
  // UTF8_LEN_MAX          = 4,
  MALFORMED_CHARACTER = 0xFFFD,
  CURSIVE_SQUARE_OFFSET = 0x60,
  UTF8_LEN_MAX = 3,
};

int utf8_encode(uint32_t ucs, char utf8_buf[UTF8_LEN_MAX + 1]);
int utf8_decode(const char *utf8_str, uint32_t *ucs);
