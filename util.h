#pragma once
#include <signal.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <termios.h>
#include "dict.h"

/* See LICENSE for licence details. */
/* error functions */
enum loglevel_t {
  DEBUG = 0,
  WARN,
  ERROR,
  FATAL,
};

void logging(enum loglevel_t loglevel, char *format, ...);
/* wrapper of C functions */
int eopen(const char *path, int flag);
int eclose(int fd);
FILE *efopen(const char *path, char *mode);
int efclose(FILE *fp);
void *ecalloc(size_t nmemb, size_t size);
void *erealloc(void *ptr, size_t size);
int eselect(int maxfd, fd_set *readfds, fd_set *writefds, fd_set *errorfds,
            struct timeval *tv);
ssize_t ewrite(int fd, const void *buf, size_t size);
int esigaction(int signo, struct sigaction *act, struct sigaction *oact);
int etcgetattr(int fd, struct termios *tm);
int etcsetattr(int fd, int action, const struct termios *tm);
int eopenpty(int *amaster, int *aslave, char *aname,
             const struct termios *termp, const struct winsize *winsize);
pid_t eforkpty(int *amaster, char *name, const struct termios *termp,
               const struct winsize *winsize);
int esetenv(const char *name, const char *value, int overwrite);
int eexecvp(const char *file, char *const argv[]);
/*
int eexecl(const char *path)
;
*/
/* parse_arg functions */
void parse_reset(struct parse_t *pt);
void parse_add(struct parse_t *pt, char *cp);
void parse_arg(char *buf, struct parse_t *pt, int delim, int(is_valid)(int c));
void print_arg(struct parse_t *pt);
