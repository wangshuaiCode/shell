#include "shell.h"

const int name_len = 256;
const int path_len = 1024;

void prompt(char *prompt)
{
	extern struct passwd *pwd;
	char path_name[path_len];
	char host_name[name_len];
	int length;
	pwd = getpwuid(getuid());

	getcwd(path_name, path_len);
	gethostname(host_name, name_len);
	sprintf(prompt, "[shell]%s@%s:", pwd->pw_name, host_name);
	length = strlen(prompt);
	if (strlen(pwd->pw_dir) > strlen(path_name) ||
	    strncmp(pwd->pw_dir, path_name, strlen(pwd->pw_dir))!= 0)
	    sprintf(prompt + length, "%s", path_name);
	else
	    sprintf(prompt + length, "~%s", path_name + strlen(pwd->pw_dir));


	length = strlen(prompt);
	if(getuid() == 0)
	    sprintf(prompt + length, "#");
	else
	    sprintf(prompt + length,"$");
	
	return;
}

 
 
