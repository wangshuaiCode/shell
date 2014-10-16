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


#define ARG_MAX 1024


int read_command(char **, char **);
char *buf;
