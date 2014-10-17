#include "shell.h"

#define TRUE 1 

void loop(void)
{
	char *command = NULL;
	char **parameters = malloc(sizeof(char *) * ARG_MAX);
	char *buf = malloc(sizeof(char) * MAXARG);
	if (buf == NULL || parameters == NULL) {
		printf("malloc error\n");
		return;
	}

	if (signal(SIGCHLD, sig_handler) == SIG_ERR)
		printf("signal error");	
	while(TRUE) {
		prompt(prompt);
		int paranum = read_command(&command, parameters, prompt);
		if (paranum < 0) {
			printf("read_command error");
			continue;
		}
		paranum--;
		parase(parameters, paranum, &cmd_info);

		if (builtin_commadn(command, parameters))
			continue;
		if ()
			
	}



}
