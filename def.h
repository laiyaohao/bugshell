#ifndef _DEF_H_
#define _DEF_H_

#define MAXLINE 1024 // most characters in a line
#define MAXARG 20 // maximum argumens in a command
#define PIPELINE 5 //maximum pipes
#define MAXNAME 100 // most characters in a file name

typedef struct command
{
  char *args[MAXARG + 1];
  int infd;
  int outfd;
} COMMAND;

#endif
