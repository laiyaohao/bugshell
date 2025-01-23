#include "init.h"
#include <signal.h>
#include <stdio.h>

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
