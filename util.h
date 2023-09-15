#pragma once
#include "dict.h"
#include <signal.h>
#include <stdio.h>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>

/* See LICENSE for licence details. */
/* error functions */
enum loglevel_t {
  DEBUG = 0,
  WARN,
  ERROR,
  FATAL,
};

void logging(enum loglevel_t loglevel, const char *format, ...);
ssize_t ewrite(int fd, const void *buf, size_t size);
void *ecalloc(size_t nmemb, size_t size);
int etcsetattr(int fd, int action, const struct termios *tm);
int esigaction(int signo, struct sigaction *act, struct sigaction *oact);
int etcgetattr(int fd, struct termios *tm);
pid_t eforkpty(int *amaster, char *name, const struct termios *termp,
               const struct winsize *winsize);
int eexecvp(const char *file, char *const argv[]);
int eselect(int maxfd, fd_set *readfds, fd_set *writefds, fd_set *errorfds,
            struct timeval *tv);
void print_arg(struct parse_t *pt);
