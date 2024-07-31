#pragma once
#include "yaskk.h"

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

bool add_entry(char *lbuf, int length, struct dict_entry_t *entry);
void load_file(const char *file, struct dict_entry_t **table, int *table_size,
               int *entry_count);
struct dict_entry_t *dict_load(const char *file, int *table_size,
                               int *entry_count);
/* sort functions (merge sort) */
static inline void merge(struct dict_entry_t *table1, int size1,
                         struct dict_entry_t *table2, int size2);
void dict_sort(struct dict_entry_t *table, int size);
/* search functions (binary search)  */
enum {
  COMPARE_ALL_STRING = 0,
};
struct dict_entry_t *dict_search(struct dict_t *dict, const char *keyword,
                                 int length);
