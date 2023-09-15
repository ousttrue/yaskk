#pragma once
#include <string>
#include <vector>

enum {
  COMPARE_ALL_STRING = 0,
  BUFSIZE = 1024,
};

/* struct for parse_arg() */
struct parse_t {
  std::vector<std::string> argv;
  void reset();
  void parse_arg(char *buf, int delim, int(is_valid)(int c));
};

/* struct for dictionary */
struct dict_entry_t {
  // std::string lbuf;
  std::string keyword;
  parse_t candidate;

  bool parse(char *lbuf, int length);
};

struct dict_t {
  std::vector<dict_entry_t> table; /* dynamic array */

  dict_t();
  ~dict_t();
  dict_t(const dict_t &) = delete;
  dict_t &operator=(const dict_t &) = delete;
  void load(const char *file);
};

struct dict_entry_t *dict_search(dict_t *dict, const char *keyword, int length);
