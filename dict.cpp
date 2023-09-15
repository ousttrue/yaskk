#include "dict.h"
#include "util.h"
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const auto skkdict_file = "~/.skk/SKK-JISYO.L";

enum {
  INIT_ENTRY = 8,
};

/* load functions */
static int not_tab(int c) { return (c != '\t') ? true : false; }

/* parse_arg functions */
void parse_t::reset() {
  this->argc = 0;
  for (int i = 0; i < MAX_ARGS; i++) {
    this->argv[i] = NULL;
  }
}

bool dict_entry_t::parse(char *lbuf, int length) {
  if (length == 0) {
    return false;
  }

  // format: keyword TAB candidate1 TAB candidate2 TAB candidate3... TAB
  char *cp = strchr(lbuf, '\t');
  if (cp == NULL) {
    return false;
  }
  *cp = '\0';
  this->keyword = lbuf;
  this->candidate.reset();
  this->candidate.parse_arg(cp + 1, '\t', not_tab);
  // illegal entry
  if (this->candidate.argc <= 0) {
    return false;
  }

  return true;
}

/* parse_arg functions */
void parse_t::add(char *cp) {
  if (this->argc >= MAX_ARGS) {
    return;
  }

  // logging(DEBUG, "argv[%d]: %s\n", pt->argc, (cp == NULL) ? "NULL": cp);
  this->argv[this->argc] = cp;
  this->argc++;
}

void parse_t::parse_arg(char *buf, int delim, int(is_valid)(int c)) {
  /*
          v..........v d           v.....v d v.....v ... d
          (valid char) (delimiter)
          argv[0]                  argv[1]   argv[2] ...   argv[argc - 1]
  */
  if (buf == NULL)
    return;

  int length = strlen(buf);
  // logging(DEBUG, "parse_arg() length:%u\n", (unsigned) length);

  char *vp = NULL;
  for (int i = 0; i < length; i++) {
    auto cp = buf + i;

    if (vp == NULL && is_valid(*cp))
      vp = cp;

    if (*cp == delim) {
      *cp = '\0';
      add(vp);
      vp = NULL;
    }

    if (i == (length - 1) && (vp != NULL || *cp == '\0')) {
      add(vp);
    }
  }

  // logging(DEBUG, "argc:%d\n", pt->argc);
}
static FILE *efopen(const char *path, const char *mode) {
  errno = 0;
  FILE *fp = fopen(path, mode);
  if (fp == NULL) {
    logging(ERROR, "couldn't open \"%s\"\n", path);
    logging(ERROR, "fopen: %s\n", strerror(errno));
  }
  return fp;
}

static int efclose(FILE *fp) {
  errno = 0;
  int ret = fclose(fp);
  if (ret < 0) {
    logging(ERROR, "fclose: %s\n", strerror(errno));
  }
  return ret;
}

dict_t::dict_t() { load(skkdict_file); }

void dict_t::load(const char *file) {
  // at first, allocate INIT_ENTRY size
  table.resize(INIT_ENTRY);

  if (auto fp = efopen(file, "r")) {
    char lbuf[BUFSIZE];
    while (fgets(lbuf, BUFSIZE, fp) != NULL) {
      // remove newline at eol
      char *cp = strchr(lbuf, '\n');
      if (cp != NULL) {
        *cp = '\0';
      }

      table.push_back({});
      if (!table.back().parse(lbuf, strlen(lbuf))) {
        table.pop_back();
      }
    }
    efclose(fp);
  }
}

dict_t::~dict_t() {}

/* sort functions (merge sort) */
static inline void merge(struct dict_entry_t *table1, int size1,
                         struct dict_entry_t *table2, int size2) {
  int i, j, count;
  struct dict_entry_t *merged;

  merged = (struct dict_entry_t *)ecalloc(size1 + size2,
                                          sizeof(struct dict_entry_t));
  count = i = j = 0;

  while (i < size1 || j < size2) {
    if (j == size2)
      merged[count++] = table1[i++];
    else if (i == size1)
      merged[count++] = table2[j++];
    else if (strcmp(table1[i].keyword.c_str(), table2[j].keyword.c_str()) < 0)
      merged[count++] = table1[i++];
    else
      merged[count++] = table2[j++];
  }

  memcpy(table1, merged, sizeof(struct dict_entry_t) * (size1 + size2));
  free(merged);
}

void dict_sort(struct dict_entry_t *table, int size) {
  struct dict_entry_t tmp;
  int median;

  if (size <= 1) {
    return;
  } else if (size == 2) {
    if (strcmp(table[0].keyword.c_str(), table[1].keyword.c_str()) > 0) {
      tmp = table[0];
      table[0] = table[1];
      table[1] = tmp;
    }
  } else {
    median = size / 2;
    dict_sort(table, median);
    dict_sort(table + median, size - median);
    merge(table, median, table + median, size - median);
  }
}

struct dict_entry_t *dict_search(struct dict_t *dict, const char *keyword,
                                 int length) {
  assert(keyword);
  // logging(DEBUG, "dict_search() keyword:%s length:%d\n", keyword, length);

  int lower = 0;
  int upper = dict->table.size() - 1;

  while (lower <= upper) {
    int median = (lower + upper) / 2;
    // logging(DEBUG, "lower:%u upper:%u median:%u\n", lower, upper, median);

    assert(0 <= median && median < dict->table.size());
    assert(dict->table[median].keyword.size());

    int ret =
        (length <= COMPARE_ALL_STRING)
            ? strcmp(keyword, dict->table[median].keyword.c_str())
            : strncmp(keyword, dict->table[median].keyword.c_str(), length);
    // logging(DEBUG, "strncmp() compare:%s ret:%d\n",
    // dict->table[median].keyword, ret);

    if (ret == 0)
      return &dict->table[median];
    else if (ret < 0)
      upper = median - 1;
    else
      lower = median + 1;
  }
  return NULL;
}
