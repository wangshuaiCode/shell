#include "shell.h"
/*
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<pwd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
*/

const int name_len = 256;
const int path_len = 1024;

void prompt(char *prompt)
{
	char path_name[path_len];
	char host_name[name_len];
	int length;
	passwd = getpwuid(getuid());

	getcwd(path_name, path_len);
	gethostname(host_name, name_len);
	sprintf(prompt, "[shell]%s@%s:", passwd->pw_name, host_name);
	length = strlen(prompt);
	if (strlen(passwd->pw_dir) > strlen(path_name) ||
	    strncmp(passwd->pw_dir, path_name, strlen(passwd->pw_dir))!= 0)
	    sprintf(prompt + length, "%s", path_name);
	else
	    printf(prompt + length, "~%s", path_name + strlen(passwd->pw_dir));


	length = strlen(prompt);
	if(getuid() == 0)
	    sprintf(prompt + length, "#");
	else
	    sprintf(prompt + length"$");
	return;
}
/*
 *	int main() 
 *     {
 *	    prompt();
 *	    return 0;
 *     }
 *
 *
 */
