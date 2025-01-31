#include "parse.h"
#include "externs.h"
#include "init.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void get_command(int i);
int check(const char *str);
void getname(char *name);
void print_command();

void shell_loop(void)
{
	while (1)
	{
		printf("[bugshell]$ ");
		fflush(stdout);
		init();
		if (read_command() == -1)
			break;
		parse_command();
		print_command();
		execute_command();
	}
	printf("\nexit\n");
}
/**
 * on success return 0. on failure or eof return -1
 */
int read_command(void)
{
	if (fgets(cmdline, MAXLINE, stdin) == NULL)
		return -1;
	
	return 0;
}
/**
 * on failure return -1
 */
int parse_command(void)
{
	/* cat < test.txt | grep -n public > text2.txt & */
	if (check("\n"))
		return 0;
	// 1. determine the first simple command
	get_command(0);
	// 2. determine if it is a input redirection symbol
	if (check("<"))
		getname(infile);
	// 3. determine if there is a pipe
	int i;
	for (i = 1; i < PIPELINE; ++i)
	{
		if (check("|"))
			get_command(i);
		else
			break;
	}
	// 4. determine if there is a output redirection symbol
	if (check(">"))
	{
		if (check(">"))
			append = 1;
		getname(outfile);
	}
	if (check("&"))
		backgnd = 1;
	if (check("\n"))
	{
		cmd_count = i;
		return cmd_count;
	}
	else
	{
		fprintf(stderr, "Command line has syntax error\n");
		return -1;
	}
	return 0;
}
/**
 * on success return 0. on failure return -1.
 */
int execute_command(void)
{
	return 0;
}

void print_command(void)
{
	int i;
	int j;
	printf("cmd_count = %d\n", cmd_count);
	if (infile[0] != '\0')
		printf("infile = [%s]\n", infile);
	if (outfile[0] != '\0')
		printf("outfile = [%s]\n", outfile);
	for (i = 0; i < cmd_count; ++i)
	{
		j = 0;
		while (cmd[i].args[j] != NULL)
		{
			printf("[%s] ", cmd[i].args[j]);
			j++;
		}
		printf("\n");
	}
}

/**
 * read simple commands to cmd[i]
 * retrieve cmdline's command arguments to avline's array
 * point 
 */
void get_command(int i)
{
	int j = 0;
	int inword;
	while (*lineptr != '\0')
	{
		// get rid of space and tabs
		while (*lineptr == ' ' || *lineptr == '\t')
			lineptr++;
		// 
		cmd[i].args[j] = avptr; // which is equal to avline, see init();
		while (*lineptr != '\0' 
				&& *lineptr != ' ' 
				&& *lineptr != '\t' 
				&& *lineptr != '>'
				&& *lineptr != '<'
				&& *lineptr != '|'
				&& *lineptr != '&'
				&& *lineptr != '\n')
		{
			*avptr++ = *lineptr++;
			inword = 1;
		}
		*avptr++ = '\0';
		switch (*lineptr)
		{
		case ' ': 
		case '\t':
			inword = 0;
			j++;
			break;
		case '<':
		case '>':
		case '|':
		case '&':
		case '\n':
			if (inword == 0)
				cmd[i].args[j] = NULL;
			return;
		default: /* for '\0' */
			return;
		}
	}
}
int check(const char *str)
{
	char *p;
	while (*lineptr == ' ' || *lineptr == '\t')
		lineptr++;
	p = lineptr;
	while (*str != '\0' && *str == *p)
	{
		str++;
		p++;
	}
	if (*str == '\0')
	{
		lineptr = p;
		return 1;
	}
	/* lineptr did not change */
	return 0;
}
void getname(char *name)
{
	while (*lineptr == ' ' || *lineptr == '\t')
		lineptr++;
	while (*lineptr != '\0' 
				&& *lineptr != ' ' 
				&& *lineptr != '\t' 
				&& *lineptr != '>'
				&& *lineptr != '<'
				&& *lineptr != '|'
				&& *lineptr != '&'
				&& *lineptr != '\n')
	{
		*name++ = *lineptr++;
	}
	*name = '\0';
}