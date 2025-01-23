#include "parse.h"
#include <stdio.h>
#include "externs.h"

void shell_loop(void)
{
  while (1)
  {
    printf("[bugshell]$ ");
    fflush(stdout);
    if (read_command() == -1)
      break;
    parse_command();
    execute_command();
  }
  printf("\nexit\n");
}
/**
 * on success return 0. on failure or eof return -1
 */
int read_command(void)
{
  char buf[1024+1];
  if (fgets(buf, 1024, stdin) == NULL)
    return -1;
  
  return 0;
}
/**
 * on failure return -1
 */
int parse_command(void)
{
  return 0;
}
/**
 * on success return 0. on failure return -1.
 */
int execute_command(void)
{
  return 0;
}
