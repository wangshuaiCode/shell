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
const int name_len = 256;
const int path_len = 1024;

void prompt()
{
	 struct passwd *passwd;
	char path_name[path_len];
	char host_name[name_len];
	passwd = getpwuid(getuid());

	getcwd(path_name, path_len);
	gethostname(host_name, name_len);
	printf("[shell]%s@%s:", passwd->pw_name, host_name);
	if (strlen(passwd->pw_dir) > strlen(path_name) ||
	    strncmp(passwd->pw_dir, path_name, strlen(passwd->pw_dir))!= 0)
	    printf("%s", path_name);
	else
	    printf("~%s", path_name + strlen(passwd->pw_dir));


	if(getuid() == 0)
	    printf("#\n");
	else
	    printf("$\n");
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
