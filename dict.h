#pragma once

enum {
  MAX_ARGS = 256,
  COMPARE_ALL_STRING = 0,
  BUFSIZE = 1024,
};

/* struct for parse_arg() */
struct parse_t {
  int argc;
  char *argv[MAX_ARGS];
};

/* struct for dictionary */
struct dict_entry_t {
  char *lbuf;
  char *keyword;
  struct parse_t candidate;
};

struct dict_t {
  struct dict_entry_t *table; /* dynamic array */
  int entry_count;            /* num of real entry size */
  int table_size;             /* num of allocated entry size */
};

struct dict_entry_t *dict_load(const char *file, int *table_size,
                               int *entry_count);

struct dict_entry_t *dict_search(struct dict_t *dict, const char *keyword,
                                 int length);
