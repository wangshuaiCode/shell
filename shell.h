#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<pwd.h>
#include<errno.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>


#define ARG_MAX			    256
#define MAXARG			    1024 
				
#define BACKGROUND		    1
#define PIPED			    2
#define OUT_REDIRECT		    4
#define OUT_REDIRECT_APPEND	    8
#define IN_REDIRECT		    16

char *buf;
struct passwd *pwd;
int read_command(char **command, char **parameters, char *prompt);
int builtin_command(char *command, char **parameters);
void loop(void);
void sig_handler();
void prompt(char *);
void par_info_init(struct parse_info *info);
int parsing(char **parameters, int paranum, struct parse_info *info);
#ifndef STRUCT_PARSE_INFO
#define STRUCT_PARSE_INFO 

struct parse_info {
	char **parameters2;
	char *cmd2;
	char *out_file;
	char *in_file;
	int flags;
};
#endif
