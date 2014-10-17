#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<pwd.h>
#include<errno.>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>


#define ARG_MAX		    256
#define MAXARG		    1024 

#define BACKGROUND	    1
#define PIPED		    2
#define OUT_REDIRECT	    4
#define OUT_REDIRECT	    8
#define IN_REDIRECT	    16

char *buf;
struct passwd *pwd;
struct parse_info;
int read_command(char **, char **);
void loop(void);
void prompt(char *);


struct parse_info {
	char **parameters;
	char *cmd;
	char *out_file;
	char *in_file;
	int flag;
};
