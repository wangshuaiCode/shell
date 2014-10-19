#include "shell.h"



int builtin_command(char *command, char **parameters)
{
	extern struct passwd *pwd;

	if ((strcmp(command, "quit") == 0) || strcmp(command, "exit") == 0) 
		exit(0);
	else if (strcmp(command, "cd") == 0) {
		char *cd_path = NULL;
		if (parameters[1][0] == '~') {
			cd_path = malloc(sizeof(char) * (strlen(pwd->pw_dir) + strlen(parameters[1])));
			if (cd_path == NULL) {
				printf(" cd_path malloc error");
			}               
			strcpy(cd_path, pwd->pw_dir);
			strncpy(cd_path + strlen(pwd->pw_dir), parameters[1] + 1, strlen(parameters[1]));
		} else {
			cd_path = malloc(sizeof(char) * strlen(parameters[1]));
			if (cd_path == NULL) {
				printf(" cd_path malloc error");
			}
			strcpy(cd_path, strlen(parameters[1]));
		}
		if (chdir(cd_path) != 0) 
			printf("chdir error");
		free(cd_path);
		
	}

	return 0;
}

