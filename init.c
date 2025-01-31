#include "init.h"
#include "externs.h"
#include <signal.h>
#include <stdio.h>
#include <string.h>

void sigint_handler(int sig)
{
  printf("\n[bugshell]$ ");
  fflush(stdout);
}

void setup(void)
{
  signal(SIGINT, sigint_handler);
  signal(SIGQUIT, SIG_IGN);
}

void init(void)
{
  memset(cmd, 0, sizeof(cmd));
  memset(cmdline, 0, sizeof(cmdline));
  lineptr = cmdline;
  avptr = avline;
  memset(infile, 0, sizeof(infile));
  memset(outfile, 0, sizeof(outfile));
  cmd_count = 0;
  backgnd = 0;
  append = 0;
}
